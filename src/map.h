#ifndef MIDDLE_AGES_MAP_H
#define MIDDLE_AGES_MAP_H

#include "coordinates.h"
#include "unit.h"
#include "unitlist.h"

void initializeMap();
void removeMap();

Unit * getUnitAtPosition(Coordinates position);
void removeUnitAtPosition(Coordinates position);

#endif
