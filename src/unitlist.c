#include "unitlist.h"
#include <stdlib.h>

UnitListNode * unitListNew() {
    return NULL;
}

static void unitListRemoveNode(UnitListNode unitListNode) {
    free(unitListNode->unit);
    free(unitListNode);
}

void unitListRemove(UnitListNode unitList) {
    UnitListNode currentUnitListNode = unitList;
    while (unitList != NULL) {
        currentUnitListNode = unitList;
        unitList = unitList->next;
        unitListRemoveNode(currentUnitListNode);
    }
}

void unitListAddUnit(Unit *unit, UnitListNode * unitList) {
    UnitListNode unitListNode = (UnitListNode) malloc(sizeof(struct UnitList));
    unitListNode->unit = unit;
    unitListNode->next = *unitList;
    *unitList = unitListNode;
}

Unit * unitListFindUnit(Coordinates position, UnitListNode unitList) {
    while (unitList != NULL) {
        if (coordinatesCompare(unitList->unit->position, position) == 0) {
            return unitList->unit;
        }
        unitList = unitList->next;
    }
    return NULL;
}

Unit * unitListFetchUnit(Coordinates position, UnitListNode * unitList) {
    Unit * unit = unitListFindUnit(position, *unitList);
    unitListRemoveUnit(position, unitList);
    return unit;
}

void unitListRemoveUnit(Coordinates position, UnitListNode *unitList) {
    UnitListNode * lastUnitListNode = unitList;
    UnitListNode currentListNode = *unitList;
    while (currentListNode != NULL) {
        if (coordinatesCompare(currentListNode->unit->position, position) == 0) {
            *lastUnitListNode = currentListNode->next;
            unitListRemoveNode(currentListNode);
        }
        lastUnitListNode = &(currentListNode->next);
    }
}