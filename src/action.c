#include "action.h"

#include <stdlib.h>

#include "unit.h"
#include "map.h"

static long initializedMapSize = -1;
static long initializedMaxMoves = -1;
static Coordinates initializedFirstKingPosition = { -1, -1 };
static Coordinates initializedSecondKingPosition = { -1, -1 };
static bool initializedPlayers[3];

bool isGameInitialized() {
    return initializedPlayers[1] && initializedPlayers[2];
}

static bool isProperMapSize(long mapSize) {
    if (initializedMapSize == -1) {
        return mapSize >= 8 && mapSize < (long long)2 << 30;
    } else {
        return mapSize == initializedMapSize;
    }
}

static bool isProperMaxMoves(long maxMoves) {
    if (initializedMaxMoves == -1) {
        return maxMoves >= 1 && maxMoves < (long long) 2 << 30;
    } else {
        return  maxMoves == initializedMaxMoves;
    }
}

static bool isProperPlayer(int player) {
    if (player != 1 && player != 2) {
        return false;
    } else {
        return !initializedPlayers[player];
    }
}

static bool isProperKingPosition(Coordinates position, Coordinates * initializedPosition, long mapSize) {
    Coordinates uninitializedPosition = { -1, -1 };
    if (coordinatesCompare(uninitializedPosition, *initializedPosition) == 0) {
        *initializedPosition = position;
        return (position.x >= 1 && position.x <= mapSize - 3)
            && (position.y >= 1 && position.y <= mapSize);
    } else {
        return coordinatesCompare(position, *initializedPosition) == 0;
    }
}

bool verifyInitArguments(long mapSize, long maxMoves, int player, Coordinates firstKingPosition, Coordinates secondKingPosition) {
    if (!isGameInitialized()
        && isProperMapSize(mapSize)
        && isProperMaxMoves(maxMoves)
        && isProperPlayer(player)
        && isProperKingPosition(firstKingPosition, &initializedFirstKingPosition, mapSize)
        && isProperKingPosition(secondKingPosition, &initializedSecondKingPosition, mapSize)
        && coordinatesDistance(firstKingPosition, secondKingPosition) >= 8) {
        initializedMapSize = mapSize;
        initializedMaxMoves = maxMoves;
        initializedPlayers[player] = true;
        initializedFirstKingPosition = firstKingPosition;
        initializedSecondKingPosition = secondKingPosition;
        return true;
    } else {
        return false;
    }
}

static bool isProperPosition(Coordinates position) {
    return (position.x >= 1 && position.x <= mapGetSize())
        && (position.y >= 1 && position.y <= mapGetSize());
}

static bool isProperActionPositions(Coordinates unitPosition, Coordinates actionPosition, long actionRange) {
    return (isProperPosition(unitPosition)
        && isProperPosition(actionPosition)
        && coordinatesDistance(unitPosition, actionPosition) == actionRange);
}

bool verifyMoveArguments(Coordinates unitPosition, Coordinates movePosition, int player, long gameTurn) {
    if (isGameInitialized()
        && isProperActionPositions(unitPosition, movePosition, 1)) {
        Unit * unit = mapGetUnit(unitPosition);
        Unit * moveFieldUnit = mapGetUnit(movePosition);
        return  (unit != NULL && unit->player == player && unit->lastMove >= gameTurn)
            &&  (moveFieldUnit == NULL || moveFieldUnit->player != player);
    } else {
        return false;
    }
}


bool verifyProduceArguments(Coordinates unitPosition, Coordinates productPosition, int player, long gameTurn) {
    if (isGameInitialized()
        && isProperActionPositions(unitPosition, productPosition, 1)) {
        Unit * unit = mapGetUnit(unitPosition);
        return  (unit != NULL && unit->type == PEASANT && unit->player == player && unit->lastMove - 2 >= gameTurn)
            &&  (mapGetUnit(productPosition) == NULL);
    } else {
        return false;
    }
}