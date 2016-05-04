#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "engine.h"
#include "map.h"
#include "unit.h"

#define PLAYERS_COUNT 2

static int engineMapSize;
static int engineMovesLeft;
static int enginePlayerTurn;

static bool initializedPlayers[PLAYERS_COUNT + 1];
static Unit * enginePlayerKings[PLAYERS_COUNT + 1];

void startGame() {
    mapInitialize();
    engineMapSize = -1;
    engineMovesLeft = -1;
    enginePlayerTurn = 1;
}

void endGame() {
    mapRemove();
}

void printTopLeft() {
    int mapSize =  10;
    for (int y = 1; y <= mapSize; y++) {
        for (int x = 1; x <= mapSize; x++) {
            Coordinates position = {x, y};
            Unit * unit = mapGetUnit(position);
            char unitRepresentation = unitGetRepresentation(unit);
            printf("%c", unitRepresentation);
        }
        printf("\n");
    }
    printf("\n");
}

static bool isPlayerInitialized(int playerID) {
    if (playerID < 1 || playerID > PLAYERS_COUNT) {
        return true;
    }
    return initializedPlayers[playerID];
}

static bool isGameInitialized() {
    for (int i = 1; i <= PLAYERS_COUNT; i++) {
        if (!isPlayerInitialized(i)) {
            return false;
        }
    }
    return true;
}

static int getAliveKingsCount() {
    int aliveKingsCount = PLAYERS_COUNT;
    for (int i = 1; i <= PLAYERS_COUNT; i++) {
        if (enginePlayerKings[i] == NULL) {
            aliveKingsCount--;
        }
    }
    return aliveKingsCount;
}

static bool isGameFinished() {
    return getAliveKingsCount() <= 1;
}

static int getWinnerID() {
    if (!isGameFinished()) {
        return -1;
    } else if (getAliveKingsCount() == 0) {
        return 0;
    }

    for (int i = 1; i <= PLAYERS_COUNT; i++) {
        if (enginePlayerKings[i] != NULL) {
            return i;
        }
    }
    return -1;
}

static enum ActionResult getGameState() {
    int winnerId = getWinnerID();
    switch (winnerId) {
        case -1: return ACTION_OK;
        case 0: return ACTION_DRAW;
        case 1: return ACTION_PLAYER1_WIN;
        case 2: return ACTION_PLAYER2_WIN;
        default: return ACTION_INVALID_ARGUMENTS;
    }
}

static bool isProperKingPosition(Coordinates position) {
    return position.x >= 1 && position.x <= engineMapSize - 3 && position.y >= 1 && position.y <= engineMapSize;
}

static void spawnInitialUnits(int playerID, Coordinates position) {
    enginePlayerKings[playerID] = unitNew(KING, playerID, position, engineMovesLeft);
    mapAddUnit(enginePlayerKings[playerID]);
    position.x++;
    mapAddUnit(unitNew(PEASANT, playerID, position, engineMovesLeft));
    position.x++;
    mapAddUnit(unitNew(KNIGHT, playerID, position, engineMovesLeft));
    position.x++;
    mapAddUnit(unitNew(KNIGHT, playerID, position, engineMovesLeft));
}

enum ActionResult initializeFirst(int mapSize, int maxMoves, int playerID, Coordinates firstKingPosition, Coordinates secondKingPosition) {
    if (mapSize < 8) {
        return ACTION_INVALID_ARGUMENTS;
    } else {
        engineMapSize = mapSize;
    }

    if (maxMoves < 1) {
        return ACTION_INVALID_ARGUMENTS;
    } else {
        engineMovesLeft = maxMoves;
    }

    if (!isProperKingPosition(firstKingPosition) || !isProperKingPosition(secondKingPosition)) {
        return ACTION_INVALID_COORDINATES;
    } else if (coordinatesDistance(firstKingPosition, secondKingPosition) < 8) {
        return ACTION_INVALID_COORDINATES;
    } else {
        initializedPlayers[playerID] = true;
        spawnInitialUnits(1, firstKingPosition);
        spawnInitialUnits(2, secondKingPosition);
        return ACTION_OK;
    }
}

enum ActionResult initializeSecond(int mapSize, int maxMoves, int playerID, Coordinates firstKingPosition, Coordinates secondKingPosition) {
    if (mapSize != engineMapSize || maxMoves != engineMovesLeft) {
        return ACTION_INVALID_ARGUMENTS;
    }

    Unit * firstKing = mapGetUnit(firstKingPosition);
    Unit * secondKing = mapGetUnit(secondKingPosition);

    if (firstKing == NULL || secondKing == NULL) {
        return ACTION_INVALID_COORDINATES;
    } else if (coordinatesCompare(firstKing->position, firstKingPosition) != 0
    || coordinatesCompare(secondKing->position, secondKingPosition) != 0) {
        return ACTION_INVALID_COORDINATES;
    } else {
        initializedPlayers[playerID] = true;
        return ACTION_OK;
    }
}

enum ActionResult init(int mapSize, int maxMoves, int playerID, int firstKingX, int firstKingY, int secondKingX, int secondKingY) {
    Coordinates firstKingPosition = {firstKingX, firstKingY};
    Coordinates secondKingPosition = {secondKingX, secondKingY};

    if (isPlayerInitialized(playerID)) {
        return ACTION_GAME_ALREADY_INITIALIZED;
    } else if (engineMapSize == -1) {
        return initializeFirst(mapSize, maxMoves, playerID, firstKingPosition, secondKingPosition);
    } else {
        return initializeSecond(mapSize, maxMoves, playerID, firstKingPosition, secondKingPosition);
    }
}

static bool isProperPosition(Coordinates position) {
    return position.x >= 1 && position.x <= engineMapSize && position.y >= 1 && position.y <= engineMapSize;
}

static enum ActionResult canUnitPerformAction(Unit *unit) {
    if (unit == NULL) {
        return ACTION_UNIT_DOES_NOT_EXIST;
    } else if (unit->player != enginePlayerTurn) {
        return ACTION_PERMISSION_DENIED;
    } else if (unit->lastMove < engineMovesLeft) {
        return ACTION_UNIT_CANNOT_PERFORM_ACTION;
    }
    return ACTION_OK;
}

static enum ActionResult canPerformActionAtPositions(Coordinates unitPosition, Coordinates actionPosition) {
    if (!isProperPosition(unitPosition)
        || !isProperPosition(actionPosition)
        || coordinatesDistance(unitPosition, actionPosition) != 1) {
        return ACTION_INVALID_COORDINATES;
    }
    return ACTION_OK;
}

static void removeUnitBeforeBattle(Unit * unit) {
    if (unit == NULL) {
        return;
    }
    if (unit->type == KING) {
        enginePlayerKings[unit->player] = NULL;
    }
    mapRemoveUnit(unit->position);
}

static void addUnitAfterBattle(Unit * unit) {
    if (unit == NULL) {
        return;
    }
    if (unit->type == KING) {
        enginePlayerKings[unit->player] = unit;
    }
    mapAddUnit(unit);
}

static void makeMove(Unit * unit, Unit * field, Coordinates movePosition) {
    assert(unit != NULL);

    removeUnitBeforeBattle(unit);
    removeUnitBeforeBattle(field);

    unit->position = movePosition;
    unit->lastMove = engineMovesLeft - 1;

    addUnitAfterBattle(unitFight(unit, field));
}

enum ActionResult move(int unitX, int unitY, int moveX, int moveY) {
    Coordinates unitPosition = { unitX, unitY };
    Coordinates movePosition = { moveX, moveY };

    if (!isGameInitialized()) {
        return ACTION_GAME_NOT_INITIALIZED;
    } else if (canPerformActionAtPositions(unitPosition, movePosition) != ACTION_OK) {
        return canPerformActionAtPositions(unitPosition, movePosition);
    }

    Unit * unit = mapGetUnit(unitPosition);
    if (canUnitPerformAction(unit) != ACTION_OK) {
        return canUnitPerformAction(unit);
    }

    Unit * field = mapGetUnit(movePosition);
    if (field != NULL && field->player == enginePlayerTurn) {
        return ACTION_FIELD_ALREADY_OCCUPIED;
    }

    makeMove(unit, field, movePosition);
    return getGameState();
}

static enum ActionResult canProduceUnit(Unit * peasant) {
    if (canUnitPerformAction(peasant) != ACTION_OK) {
        return canUnitPerformAction(peasant);
    } if (peasant->type != PEASANT || peasant->lastMove - 2 < engineMovesLeft) {
        return ACTION_UNIT_CANNOT_PERFORM_ACTION;
    }
    return ACTION_OK;
}

static enum ActionResult produceUnit(enum UnitType unitType, Coordinates peasantPosition, Coordinates unitPosition) {
    if (!isGameInitialized()) {
        return ACTION_GAME_NOT_INITIALIZED;
    } else if (canPerformActionAtPositions(peasantPosition, unitPosition) != ACTION_OK) {
        return canPerformActionAtPositions(peasantPosition, unitPosition);
    }

    Unit * peasant = mapGetUnit(peasantPosition);
    if (canProduceUnit(peasant) != ACTION_OK) {
        return canProduceUnit(peasant);
    }

    Unit * unit = mapGetUnit(unitPosition);
    if (unit != NULL) {
        return ACTION_FIELD_ALREADY_OCCUPIED;
    }

    mapAddUnit(unitNew(unitType, enginePlayerTurn, unitPosition, engineMovesLeft));
    peasant->lastMove = engineMovesLeft - 1;
    return  ACTION_OK;
}

enum ActionResult produceKnight(int peasantX, int peasantY, int knightX, int knightY) {
    Coordinates peasantPosition = { peasantX, peasantY };
    Coordinates knightPosition = { knightX, knightY };

    return produceUnit(KNIGHT, peasantPosition, knightPosition);
}

enum ActionResult producePeasant(int peasantX, int peasantY, int newPeasantX, int newPeasantY) {
    Coordinates peasantPosition = { peasantX, peasantY };
    Coordinates newPeasantPosition = { newPeasantX, newPeasantY };

    return produceUnit(PEASANT, peasantPosition, newPeasantPosition);
}

enum ActionResult endTurn() {
    if (enginePlayerTurn == PLAYERS_COUNT) {
        engineMovesLeft--;
    }
    if (engineMovesLeft < 0) {
        return ACTION_DRAW;
    }
    enginePlayerTurn = enginePlayerTurn % PLAYERS_COUNT + 1;
    return ACTION_OK_NO_DISPLAY;
}
