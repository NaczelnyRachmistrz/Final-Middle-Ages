#ifndef MIDDLE_AGES_MAP_H
#define MIDDLE_AGES_MAP_H

#include "coordinates.h"
#include "unit.h"
#include "unitlist.h"

void mapInitialize();
void mapRemove();

void mapAddUnit(Unit * unit);
Unit * mapGetUnit(Coordinates position);
void mapRemoveUnit(Coordinates position);

#endif

