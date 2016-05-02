#include <stdio.h>

#include "engine.h"
#include "map.h"
#include "unit.h"

void startGame() {
    mapInitialize();
}

void endGame() {
    removeMap();
}

static char lowercase(char c) {
    return (char)(c + ('a' - 'A'));
}

static char getUnitRepresentation(Unit * unit) {
    if (unit == NULL) {
        return '.';
    }
    char representation = 'A';
    switch (unit->type) {
        case KNIGHT: representation = 'R'; break;
        case KING: representation = 'K'; break;
        case PEASANT: representation = 'C'; break;
    }
    return unit->player == 1 ? representation : lowercase(representation);
}

void printTopLeft() {
    int mapSize =  10;
    for (int x = 1; x <= mapSize; x++) {
        for (int y = 1; y <= mapSize; y++) {
            Unit * unit = mapGetUnit({x, y});
            char unitRepresentation = getUnitRepresentation(unit);
            printf("%c", unitRepresentation);
        }
        printf("\n");
    }

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
