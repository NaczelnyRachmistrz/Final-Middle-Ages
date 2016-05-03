#ifndef MIDDLE_AGES_ENGINE_H
#define MIDDLE_AGES_ENGINE_H

enum ActionResult {
    ACTION_OK,
    ACTION_GAME_NOT_INITIALIZED,
    ACTION_GAME_ALREADY_INITIALIZED,
    ACTION_INVALID_COORDINATES,
    ACTION_INVALID_ARGUMENTS,
    ACTION_PERMISSION_DENIED
};

void startGame();

void endGame();

enum ActionResult init(int mapSize, int maxMoves, int playerID, int firstKingX, int firstKingY, int secondKingX, int secondKingY);

int move(int x1, int y1, int x2, int y2);

int produce_knight(int x1, int y1, int x2, int y2);

int produce_peasant(int x1, int y1, int x2, int y2);

int end_turn();

void printTopLeft();

#endif /* ENGINE_H */
