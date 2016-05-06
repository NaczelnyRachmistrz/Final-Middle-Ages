/**
 * @file engine.h
 * Implements available commands
 * @see Command
 */
#ifndef MIDDLE_AGES_ENGINE_H
#define MIDDLE_AGES_ENGINE_H

/**
 * @brief Possible output codes
 */
enum ActionResult {
    // OK
    ACTION_OK,
    ACTION_OK_NO_DISPLAY,
    //GAME FINISHED
    ACTION_DRAW,
    ACTION_DRAW_NO_DISPLAY,
    ACTION_PLAYER1_WIN,
    ACTION_PLAYER2_WIN,
    //ERROR
    ACTION_ERROR
};

/**
 * @brief Starts the game
 *
 * Initializes structures and allocates required memory
 */
void startGame();

/**
 * @brief Ends the game
 *
 * Removes remaining structures and frees memory
 */
void endGame();

/**
 * @brief Initializes game
 *
 * If the game has already been initialized for one of the players,
 * checks if given parameters matches the one supplied in previous initialization.
 * @param mapSize size of the game map
 * @param maxMoves turns after which the game ends with DRAW
 * @param player player id
 * @param firstKingX x coordinate of the player1 king
 * @param firstKingY y coordinate of the player1 king
 * @param secondKingX x coordinate of the player2 king
 * @param secondKingY y coordinate of the player2 king
 * @return status of init action
 * @see ActionResult
 */
enum ActionResult init(long mapSize, long maxMoves, int player, long firstKingX, long firstKingY, long secondKingX, long secondKingY);

/**
 * @brief Moves unit at given position to new position
 *
 * @param unitX x coordinate of the unit
 * @param unitY y coordinate of the unit
 * @param moveX x coordinate of position to move to
 * @param moveY y coordinate of position to move to
 * @return status of move action
 * @see ActionResult
 */
enum ActionResult move(long unitX, long unitY, long moveX, long moveY);

/**
 * @brief Produces knight
 *
 * @param peasantX x coordinate of the peasant
 * @param peasantY y coordinate of the peasant
 * @param knightX x coordinate of the new knight
 * @param knightY y coordinate of the new knight
 * @return status of produceKnight action
 * @see ActionResult
 */
enum ActionResult produceKnight(long peasantX, long peasantY, long knightX, long knightY);

/**
 * @brief Produces peasant
 *
 * @param peasantX x coordinate of the peasant
 * @param peasantY y coordinate of the peasant
 * @param newPeasantX x coordinate of the new peasant
 * @param newPeasantY y coordinate of the new peasant
 * @return status of produceKnight action
 * @see ActionResult
 */
enum ActionResult producePeasant(long peasantX, long peasantY, long newPeasantX, long newPeasantY);

/**
 * @brief Ends player turn
 * @return status of endTurn action
 */
enum ActionResult endTurn();

/**
 * @brief Prints top left corner of the game map
 *
 * Prints up to 10x10 square of the map to stdout
 */
void printTopLeft();

#endif /* ENGINE_H */
