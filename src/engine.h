#ifndef ENGINE_H
#define ENGINE_H

void startGame();

void endGame();

int init(int mapSize, int maxMoves, int player, int king1x, int king1y, int king2x, int king2y);

int move(int x1, int y1, int x2, int y2);

int produce_knight(int x1, int y1, int x2, int y2);

int produce_peasant(int x1, int y1, int x2, int y2);

int end_turn();

/**
 * Prints (into stdout) top-left corner of the board of size m x m where m = min(n,10).
 */
void print_topleft();

#endif /* ENGINE_H */
