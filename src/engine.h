#ifndef MIDDLE_AGES_ENGINE_H
#define MIDDLE_AGES_ENGINE_H

enum ActionResult {
    // OK
    ACTION_OK,
    ACTION_OK_NO_DISPLAY,
    //GAME FINISHED
    ACTION_DRAW,
    ACTION_PLAYER1_WIN,
    ACTION_PLAYER2_WIN,
    //ERRORS
    ACTION_INVALID_ARGUMENTS,
    ACTION_GAME_NOT_INITIALIZED,
    ACTION_GAME_ALREADY_INITIALIZED,
    ACTION_INVALID_COORDINATES,
    ACTION_UNIT_DOES_NOT_EXIST,
    ACTION_UNIT_CANNOT_PERFORM_ACTION,
    ACTION_FIELD_ALREADY_OCCUPIED,
    ACTION_PERMISSION_DENIED
};

void startGame();

void endGame();

enum ActionResult init(int mapSize, int maxMoves, int playerID, int firstKingX, int firstKingY, int secondKingX, int secondKingY);

enum ActionResult move(int unitX, int unitY, int moveX, int moveY);

enum ActionResult produceKnight(int peasantX, int peasantY, int knightX, int knightY);

enum ActionResult producePeasant(int peasantX, int peasantY, int newPeasantX, int newPeasantY);

enum ActionResult endTurn();

void printTopLeft();

#endif /* ENGINE_H */
