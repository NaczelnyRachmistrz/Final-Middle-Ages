#include <stdlib.h>
#include "unit.h"

Unit * unitNew(enum UnitType type, int player, Coordinates position, long turn) {
    Unit * unit =  (Unit *) malloc(sizeof(Unit));
    unit->type = type;
    unit->player = player;
    unit->position = position;
    unit->lastMove = turn;
    return unit;
}

void unitRemove(Unit *unit) {
    free(unit);
}

static char toLowercase(char c) {
    return (char)(c + ('a' - 'A'));
}

char unitGetRepresentation(Unit * unit) {
    if (unit == NULL) {
        return '.';
    }
    char representation = 'U';
    switch (unit->type) {
        case KNIGHT:
            representation = 'R';
            break;
        case KING:
            representation = 'K';
            break;
        case PEASANT:
            representation = 'C';
            break;
    }
    return unit->player == 1 ? representation : toLowercase(representation);
}

Unit * unitFight(Unit * firstUnit, Unit * secondUnit) {
    if (firstUnit == NULL) {
        return secondUnit;
    } else if (secondUnit == NULL) {
        return firstUnit;
    } else if (firstUnit->type == secondUnit->type) {
        unitRemove(firstUnit);
        unitRemove(secondUnit);
        return NULL;
    } else if (firstUnit->type > secondUnit->type) {
        unitRemove(secondUnit);
        return firstUnit;
    } else {
        unitRemove(firstUnit);
        return secondUnit;
    }
}