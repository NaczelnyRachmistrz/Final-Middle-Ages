#ifndef MIDDLE_AGES_UNITS_H
#define MIDDLE_AGES_UNITS_H

#include "coordinates.h"

enum UnitType {
    PEASANT = 1,
    KING = 2,
    KNIGHT = 3
};

typedef struct  {
    enum UnitType type;
    int player;

    Coordinates position;
    int lastMove;
} Unit;

Unit * newUnit(enum UnitType type, int player, Coordinates position, int turn);
void removeUnit(Unit * unit);

#endif //MIDDLE_AGES_UNITS_H