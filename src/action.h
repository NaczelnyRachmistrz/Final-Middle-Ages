#ifndef MIDDLE_AGES_ACTION_H
#define MIDDLE_AGES_ACTION_H

#include <stdbool.h>
#include "coordinates.h"

bool isGameInitialized();
bool verifyInitArguments(long mapSize, long maxMoves, int playerID, Coordinates firstKingPosition, Coordinates secondKingPosition);
bool verifyMoveArguments(Coordinates unitPosition, Coordinates movePosition, int player, long gameTurn);
bool verifyProduceArguments(Coordinates unitPosition, Coordinates productPosition, int player, long gameTurn);

#endif
