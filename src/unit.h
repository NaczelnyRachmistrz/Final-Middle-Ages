/**
 * @file unit.h
 * Unit
 */
#ifndef MIDDLE_AGES_UNITS_H
#define MIDDLE_AGES_UNITS_H

#include "coordinates.h"

/**
 * Unit types found in the game
 * @see Unit
 */
enum UnitType {
    PEASANT = 1,
    KING = 2,
    KNIGHT = 3
};

/**
 * @struct Unit
 * @brief Represents one unit in game
 */
typedef struct  {
    enum UnitType type; /**< Type of the unit */
    int player; /**< Owner of the unit */

    Coordinates position; /**< Position of the map */
    long lastMove; /**< Last turn in which unit performed action */
} Unit;

/**
 * @brief Constructor for Unit structure
 * @param type type of unit to be created
 * @param player owner of the unit
 * @param position position of the unit
 * @param turn current game turn
 * @return pointer to newly created unit
 */
Unit * unitNew(enum UnitType type, int player, Coordinates position, long turn);

/**
 * @brief Destructor for Unit structure
 * Removes unit and frees memory
 * @param unit pointer to the unit to be destroyed
 */
void unitRemove(Unit * unit);

/**
 * @brief Gets graphical representation of the unit
 * @param unit pointer to the unit
 * @return char representation og the unit
 */
char unitGetRepresentation(Unit * unit);

/**
 * @brief Simulates battle between units
 * @param firstUnit pointer to one of the units
 * @param secondUnit pointer to the other unit
 * @return winning unit or NULL in case of draw
 */
Unit * unitFight(Unit * firstUnit, Unit * secondUnit);

#endif //MIDDLE_AGES_UNITS_H
