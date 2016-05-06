#include "map.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 1000003
#define HASH_INT 25013

static UnitList map[HASH_SIZE];
static long mapSize = -1;

static int indexFromCoordinates(Coordinates coordinates) {
    unsigned long long int dividend = (unsigned long long int)coordinates.x * HASH_INT + coordinates.y;
    return (int) (dividend % HASH_SIZE);
}

void mapInitialize(long size) {
    mapSize = size;
    for (int i = 0; i < HASH_SIZE; i++) {
        map[i] = unitListNew();
    }
}

void mapDestroy() {
    for (int i = 0; i < HASH_SIZE; i++) {
        unitListRemove(map[i]);
    }
}

void mapPrintFragment(Coordinates from, Coordinates to) {
    assert(from.x <= to.x && from.y <= to.y);
    for (long y = from.y; y <= to.y; y++) {
        for (long x = from.x; x <= to.x; x++) {
            Coordinates position = { x, y };
            Unit * unit = mapGetUnit(position);
            char unitRepresentation = unitGetRepresentation(unit);
            printf("%c", unitRepresentation);
        }
        printf("\n");
    }
    printf("\n");
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

long mapGetSize() {
    return mapSize;
}