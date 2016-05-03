#include "map.h"
#include <assert.h>
#include <stdlib.h>

#define HASHTABLE_SIZE 1000003
#define HASHING_INT 500009

static UnitListNode map[HASHTABLE_SIZE];

static int indexFromCoordinates(Coordinates coordinates) {
    unsigned long long int dividend = (unsigned long long int)coordinates.x * HASHING_INT + coordinates.y;
    return (int) (dividend % HASHTABLE_SIZE);
}

void mapInitialize() {
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        map[i] = unitListNew();
    }
}

void mapRemove() {
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        unitListRemove(map[i]);
    }
}

void mapAddUnit(Unit * unit) {
    assert(unit != NULL);
    int index = indexFromCoordinates(unit->position);
    assert(unitListGetUnit(unit->position, map[index]) == NULL);
    unitListAddUnit(unit, &map[index]);
}

Unit * mapGetUnit(Coordinates position) {
    int index = indexFromCoordinates(position);
    return unitListGetUnit(position, map[index]);
}

void mapRemoveUnit(Coordinates position) {
    int index = indexFromCoordinates(position);
    unitListRemoveUnit(position, &map[index]);
}