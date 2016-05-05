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
    long lastMove;
} Unit;

Unit * unitNew(enum UnitType type, int player, Coordinates position, long turn);
void unitRemove(Unit * unit);

char unitGetRepresentation(Unit * unit);
Unit * unitFight(Unit * firstUnit, Unit * secondUnit);

#endif //MIDDLE_AGES_UNITS_H
