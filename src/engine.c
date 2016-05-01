#include "engine.h"
#include "units.h"

#define HASHTABLE_SIZE 1000003
static UnitList* map[HASHTABLE_SIZE];

Unit * getUnit(int x, int y) {
    int cell = ((unsigned long long int)x * HASHTABLE_SIZE + y) % HASHTABLE_SIZE;
}

void startGame() {
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        map[i] = newUnitList();
    }
}

void endGame() {
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        removeUnitList(map[i]);
    }
}

void print_topleft() {

}

int init(int mapSize, int maxMoves, int player, int king1x, int king1y, int king2x, int king2y) {

}

int move(int x1, int y1, int x2, int y2) {

}

int produce_knight(int x1, int y1, int x2, int y2) {

}

int produce_peasant(int x1, int y1, int x2, int y2) {

}

int end_turn() {

}
