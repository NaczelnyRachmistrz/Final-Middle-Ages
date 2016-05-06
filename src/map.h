/**
 * @file map.h
 * Hashtable of units
 */
#ifndef MIDDLE_AGES_MAP_H
#define MIDDLE_AGES_MAP_H

#include "coordinates.h"
#include "unit.h"
#include "unitlist.h"

/**
 * @brief Initializes map
 *
 * Allocates memory for hashtable
 * and sets size of the game map
 * @param size size of the game map
 */
void mapInitialize(long size);

/**
 * Gets size of the game map
 * @return returns size of the game map
 */
long mapGetSize();

/**
 * @brief Removes map
 *
 * Frees memory of hashtable, removes all lists and units on the map
 */
void mapDestroy();

/**
 * @brief Prints fragment of the map to stdout
 * @param from top left corner of the fragment
 * @param to bottom right corner of the fragment
 */
void mapPrintFragment(Coordinates from, Coordinates to);

/**
 * Adds unit to the map
 * @param unit unit to be added
 */
void mapAddUnit(Unit * unit);

/**
 * Gets unit from the map
 * @param position coordinates to get unit from
 * @return returns unit from position
 */
Unit * mapGetUnit(Coordinates position);

/**
 * @brief Removes unit from the map
 * 
 * Unit removed from the map is not destroyed
 * @param position coordinates to remove unit from
 */
void mapRemoveUnit(Coordinates position);

#endif

