#ifndef MIDDLE_AGES_UNITLIST_H
#define MIDDLE_AGES_UNITLIST_H

#include "coordinates.h"
#include "unit.h"

struct UnitListNode;
typedef struct UnitList * UnitListNode;

struct UnitList {
    Unit * unit;
    UnitListNode next;
};

UnitListNode unitListNew();
void unitListRemove(UnitListNode unitList);

void unitListAddUnit(Unit *unit, UnitListNode *unitList);
Unit * unitListGetUnit(Coordinates position, UnitListNode unitList);
void unitListRemoveUnit(Coordinates position, UnitListNode *unitList);

#endif
