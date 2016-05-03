#include <stdio.h>
#include <stdbool.h>

#include "engine.h"
#include "map.h"
#include "unit.h"

#define MAX_PLAYERS_COUNT 2

static int engineMapSize;
static int engineMaxMoves;
static int enginePlayerTurn;

static bool initializedPlayers[MAX_PLAYERS_COUNT + 1];
static Unit * enginePlayerKings[MAX_PLAYERS_COUNT + 1];

void startGame() {
    mapInitialize();
    engineMapSize = -1;
    engineMaxMoves = -1;
    enginePlayerTurn = 1;
}

void endGame() {
    mapRemove();
}

static char toLowercase(char c) {
    return (char)(c + ('a' - 'A'));
}

static char getUnitRepresentation(Unit * unit) {
    if (unit == NULL) {
        return '.';
    }
    char representation = 'A';
    switch (unit->type) {
        case KNIGHT: representation = 'R'; break;
        case KING: representation = 'K'; break;
        case PEASANT: representation = 'C'; break;
    }
    return unit->player == 1 ? representation : toLowercase(representation);
}

void printTopLeft() {
    int mapSize =  10;
    for (int y = 1; y <= mapSize; y++) {
        for (int x = 1; x <= mapSize; x++) {
            Coordinates position = {x, y};
            Unit * unit = mapGetUnit(position);
            char unitRepresentation = getUnitRepresentation(unit);
            printf("%c", unitRepresentation);
        }
        printf("\n");
    }

}


static bool isPlayerInitialized(int playerID) {
    if (playerID < 1 || playerID > MAX_PLAYERS_COUNT) {
        return true;
    }
    return initializedPlayers[playerID];
}

static bool isGameInitialized() {
    for (int i = 1; i <= MAX_PLAYERS_COUNT; i++) {
        if (!isPlayerInitialized(i)) {
            return false;
        }
    }
    return true;
}

static bool isProperKingPosition(Coordinates position) {
    return position.x >= 1 && position.x <= engineMapSize - 3 && position.y >= 1 && position.y <= engineMapSize;
}

static void spawnInitialUnits(int playerID, Coordinates position) {
    enginePlayerKings[playerID] = newUnit(KING, playerID, position, 1);
    mapAddUnit(enginePlayerKings[playerID]);
    position.x++;
    mapAddUnit(newUnit(PEASANT, playerID, position, 1));
    position.x++;
    mapAddUnit(newUnit(KNIGHT, playerID, position, 1));
    position.x++;
    mapAddUnit(newUnit(KNIGHT, playerID, position, 1));
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
        engineMaxMoves = maxMoves;
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
    if (mapSize != engineMapSize || maxMoves != engineMaxMoves) {
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

int move(int fromX, int fromY, int toX, int toY) {

}

int produceKnight(int peasantX, int peasantY, int knightX, int knightY) {

}

int producePeasant(int x1, int y1, int x2, int y2) {

}

int endTurn() {

}
