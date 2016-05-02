#include <stdlib.h>
#include "unit.h"

Unit * newUnit(enum UnitType type, int player, Coordinates position, int turn) {
    Unit * unit =  (Unit *) malloc(sizeof(Unit));
    unit->type = type;
    unit->player = player;
    unit->position = position;
    unit->lastMove = turn;
    return unit;
}

void removeUnit(Unit * unit) {
    free(unit);
}