#include "map.h"

#define HASHTABLE_SIZE 1000003

static UnitListNode* map[HASHTABLE_SIZE];

static int indexFromCoordinates(Coordinates coordinates) {
    unsigned long long int dividend = (unsigned long long int)coordinates.x * HASHTABLE_SIZE + coordinates.y;
    return (int) (dividend % HASHTABLE_SIZE);
}

void initializeMap() {
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        map[i] = unitListNew();
    }
}

void removeMap() {
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        unitListRemove(map[i]);
    }
}

Unit * getUnitAtPosition(Coordinates position) {
    int index = indexFromCoordinates(position);
    return unitListFindUnit(position, map[index]);
}

void removeUnitAtPosition(Coordinates position) {
    int index = indexFromCoordinates(position);
    unitListRemoveUnit(position, map[index]);
}