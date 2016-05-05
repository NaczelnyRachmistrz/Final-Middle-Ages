#include <stdio.h>
#include <assert.h>

#include "engine.h"
#include "coordinates.h"
#include "unit.h"
#include "map.h"
#include "action.h"

#define PLAYERS_COUNT 2

static long engineMovesLeft;
static int engineActivePlayer;
static bool enginePlayerKingOnMap[PLAYERS_COUNT + 1];

void startGame() {
    engineMovesLeft = -1;
    engineActivePlayer = 1;
}

void endGame() {
    mapDestroy();
}

void printTopLeft() {
    long mapSize = mapGetSize() > 10 ? 10 : mapGetSize();
    Coordinates from = {1, 1};
    Coordinates to = { mapSize, mapSize };
    mapPrintFragment(from, to);
}

static enum ActionResult getGameState(){
    if (enginePlayerKingOnMap[1] == true && enginePlayerKingOnMap[2] == true) {
        return ACTION_OK;
    } else if (enginePlayerKingOnMap[1] == false && enginePlayerKingOnMap[2] == false) {
        return ACTION_DRAW;
    } else if (enginePlayerKingOnMap[1] == true) {
        return ACTION_PLAYER1_WIN;
    } else {
        return ACTION_PLAYER2_WIN;
    }
}

static void spawnInitialUnits(int playerID, Coordinates position) {
    enginePlayerKingOnMap[playerID] = true;
    mapAddUnit(unitNew(KING, playerID, position, engineMovesLeft));

    position.x++;
    mapAddUnit(unitNew(PEASANT, playerID, position, engineMovesLeft));

    position.x++;
    mapAddUnit(unitNew(KNIGHT, playerID, position, engineMovesLeft));

    position.x++;
    mapAddUnit(unitNew(KNIGHT, playerID, position, engineMovesLeft));
}

enum ActionResult init(long mapSize, long maxMoves, int player, long firstKingX, long firstKingY, long secondKingX, long secondKingY) {
    Coordinates firstKingPosition = {firstKingX, firstKingY};
    Coordinates secondKingPosition = {secondKingX, secondKingY};

    if (verifyInitArguments(mapSize, maxMoves, player, firstKingPosition, secondKingPosition)) {
        if (engineMovesLeft == -1) {
            mapInitialize(mapSize);
            engineMovesLeft = maxMoves;
            spawnInitialUnits(1, firstKingPosition);
            spawnInitialUnits(2, secondKingPosition);
        }
        return ACTION_OK;
    } else {
        return ACTION_ERROR;
    }
}

static void removeUnitBeforeBattle(Unit * unit) {
    if (unit == NULL) {
        return;
    } else if (unit->type == KING) {
        enginePlayerKingOnMap[unit->player] = false;
    }
    mapRemoveUnit(unit->position);
}

static void addUnitAfterBattle(Unit * unit) {
    if (unit == NULL) {
        return;
    } else if (unit->type == KING) {
        enginePlayerKingOnMap[unit->player] = true;
    }
    mapAddUnit(unit);
}

static void makeMove(Coordinates unitPosition, Coordinates movePosition) {
    Unit * unit = mapGetUnit(unitPosition);
    assert(unit != NULL);
    Unit * moveFieldUnit = mapGetUnit(movePosition);
    removeUnitBeforeBattle(unit);
    removeUnitBeforeBattle(moveFieldUnit);
    unit->position = movePosition;
    unit->lastMove = engineMovesLeft - 1;
    addUnitAfterBattle(unitFight(unit, moveFieldUnit));
}

enum ActionResult move(long unitX, long unitY, long moveX, long moveY) {
    Coordinates unitPosition = { unitX, unitY };
    Coordinates movePosition = { moveX, moveY };

    if (verifyMoveArguments(unitPosition, movePosition, engineActivePlayer, engineMovesLeft)) {
        makeMove(unitPosition, movePosition);
        return getGameState();
    } else {
        return ACTION_ERROR;
    }
}

static enum ActionResult produceUnit(enum UnitType unitType, Coordinates peasantPosition, Coordinates unitPosition) {
    if (verifyProduceArguments(peasantPosition, unitPosition, engineActivePlayer, engineMovesLeft)) {
        mapAddUnit(unitNew(unitType, engineActivePlayer, unitPosition, engineMovesLeft));
        mapGetUnit(peasantPosition)->lastMove = engineMovesLeft - 1;
        return  ACTION_OK;
    } else {
        return ACTION_ERROR;
    }
}

enum ActionResult produceKnight(long peasantX, long peasantY, long knightX, long knightY) {
    Coordinates peasantPosition = { peasantX, peasantY };
    Coordinates knightPosition = { knightX, knightY };

    return produceUnit(KNIGHT, peasantPosition, knightPosition);
}

enum ActionResult producePeasant(long peasantX, long peasantY, long newPeasantX, long newPeasantY) {
    Coordinates peasantPosition = { peasantX, peasantY };
    Coordinates newPeasantPosition = { newPeasantX, newPeasantY };

    return produceUnit(PEASANT, peasantPosition, newPeasantPosition);
}

enum ActionResult endTurn() {
    if (!isGameInitialized()) {
        return ACTION_ERROR;
    }
    
    if (engineActivePlayer == PLAYERS_COUNT) {
        engineMovesLeft--;
    }
    if (engineMovesLeft <= 0) {
        return ACTION_DRAW_NO_DISPLAY;
    }
    engineActivePlayer = engineActivePlayer % PLAYERS_COUNT + 1;
    return ACTION_OK_NO_DISPLAY;
}
