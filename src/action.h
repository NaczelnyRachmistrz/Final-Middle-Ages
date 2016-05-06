/**
 * @file action.h
 * Verifies command parameters
 *
 * @see Command
 */
#ifndef MIDDLE_AGES_ACTION_H
#define MIDDLE_AGES_ACTION_H

#include <stdbool.h>
#include "coordinates.h"

/**
 * @brief Checks if the game has been initialized
 *
 * @return if init has been invoked by both players
 */
bool isGameInitialized();

/**
 * @brief Verifies arguments supplied to init command
 *
 * If the game has already been initialized for one of the players,
 * checks if given parameters matches the one supplied in previous initialization.
 * @param mapSize size of the game map
 * @param maxMoves turns after which the game ends with DRAW
 * @param player player id
 * @param firstKingPosition position of player1 king
 * @param secondKingPosition position of player2 king
 * @returns if arguments are valid
 */
bool verifyInitArguments(long mapSize, long maxMoves, int player, Coordinates firstKingPosition, Coordinates secondKingPosition);

/**
 * @brief Verifies arguments supplied to move command
 *
 * @param unitPosition position of the unit
 * @param movePosition position to move to
 * @param player player id
 * @param gameTurn current game turn
 * @return if arguments are valid
 */
bool verifyMoveArguments(Coordinates unitPosition, Coordinates movePosition, int player, long gameTurn);

/**
 * @brief Verifies arguments supplied to produceKnight or producePeasant command
 *
 * @param unitPosition position of the peasant
 * @param productPosition position of unit to be created
 * @param player player id
 * @param gameTurn current game turn
 * @return if arguments are valid
 */
bool verifyProduceArguments(Coordinates unitPosition, Coordinates productPosition, int player, long gameTurn);

#endif
