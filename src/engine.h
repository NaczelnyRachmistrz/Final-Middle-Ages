/** @file
    Interface of game engine.

 */
#include <stdbool.h>
#ifndef ENGINE_H
#define ENGINE_H

/**
 * Initializes a game. Needed before first INIT.
 */
void startGame();

/**
 * Frees memory. Needed after finishing game.
 */
void endGame();

/**
 * Initializes a game with size of a board, number of rounds and positions of kings.
 */
bool init(int n, int k, int p, int x1, int y1, int x2, int y2);

/**
 * Makes a move.
 * @param[in] x1 Column number before a move.
 * @param[in] y1 Row number before a move.
 * @param[in] x2 Column number after a move.
 * @param[in] y2 Row number before a move.
 * @return 0.
 */
bool move(int x1, int y1, int x2, int y2);

int produceKnight(int x1, int y1, int x2, int y2);

int producePeasant(int x1, int y1, int x2, int y2);

bool endTurn();

/**
 * Prints (into stdout) top-left corner of the board of size m x m where m = min(n,10).
 */
void printTopleft();

void clearAll();

bool checkWinner();

#endif /* ENGINE_H */
