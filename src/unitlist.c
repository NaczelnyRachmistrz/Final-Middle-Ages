#include "unitlist.h"
#include <stdlib.h>

UnitList unitListNew() {
    return NULL;
}

static void unitListRemoveNode(UnitList unitListNode) {
    free(unitListNode->unit);
    free(unitListNode);
}

void unitListRemove(UnitList unitList) {
    UnitList currentUnitListNode;
    while (unitList != NULL) {
        currentUnitListNode = unitList;
        unitList = unitList->next;
        unitListRemoveNode(currentUnitListNode);
    }
}

void unitListAddUnit(Unit *unit, UnitList * unitList) {
    UnitList unitListNode = (UnitList) malloc(sizeof(struct UnitListNode));
    unitListNode->unit = unit;
    unitListNode->next = *unitList;
    *unitList = unitListNode;
}

Unit * unitListGetUnit(Coordinates position, UnitList unitList) {
    while (unitList != NULL) {
        if (coordinatesCompare(unitList->unit->position, position) == 0) {
            return unitList->unit;
        }
        unitList = unitList->next;
    }
    return NULL;
}

void unitListRemoveUnit(Coordinates position, UnitList *unitList) {
    UnitList * lastUnitListNode = unitList;
    UnitList currentListNode = *unitList;
    while (currentListNode != NULL) {
        if (coordinatesCompare(currentListNode->unit->position, position) == 0) {
            *lastUnitListNode = currentListNode->next;
            free(currentListNode);
            return;
        }
        lastUnitListNode = &(currentListNode->next);
        currentListNode = currentListNode->next;
    }
}