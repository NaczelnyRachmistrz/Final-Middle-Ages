#ifndef MIDDLE_AGES_ENGINE_H
#define MIDDLE_AGES_ENGINE_H

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

void startGame();

void endGame();

enum ActionResult init(long mapSize, long maxMoves, int playerID, long firstKingX, long firstKingY, long secondKingX, long secondKingY);

enum ActionResult move(long unitX, long unitY, long moveX, long moveY);

enum ActionResult produceKnight(long peasantX, long peasantY, long knightX, long knightY);

enum ActionResult producePeasant(long peasantX, long peasantY, long newPeasantX, long newPeasantY);

enum ActionResult endTurn();

void printTopLeft();

#endif /* ENGINE_H */
