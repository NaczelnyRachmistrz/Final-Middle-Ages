/**
 * @file unitlist.h
 * UnitList structure and functions to operate on it
 * @see Unit
 */
#ifndef MIDDLE_AGES_UNITLIST_H
#define MIDDLE_AGES_UNITLIST_H

#include "coordinates.h"
#include "unit.h"

struct UnitListNode;
/**
 * @brief Shortcut for UnitListNode *
 */
typedef struct UnitListNode * UnitList;

/**
 * Single element of UnitList
 */
struct UnitListNode {
    Unit * unit; /**< unit in current node*/
    UnitList next; /**< next element of the list*/
};

/**
 * @brief Constructor for the UnitList structure
 * @returns new UnitList
 */
UnitList unitListNew();

/**
 * @brief Destructor for the UnitList structure.
 * Removes every unit in unitList and the unitList itself.
 * @param unitList UnitList to be removed
 */
void unitListRemove(UnitList unitList);

/**
 * @brief Adds unit to the list.
 * @param unit pointer to the unit to be added
 * @param unitList list to add unit to
 */
void unitListAddUnit(Unit *unit, UnitList *unitList);

/**
 * @brief Gets the unit from the list
 * @param position position of the Unit to be get from the list
 * @param unitList pointer to the UnitList to get unit from
 * @returns pointer to unit or NULL if it hasn't been found
 */
Unit * unitListGetUnit(Coordinates position, UnitList unitList);

/**
 * @brief Removes unit from the list.
 * unit removed from the list is not destroyed.
 * @param position position of the Unit to be removed from the list
 * @param unitList pointer to the UnitList to remove unit from
 * @see Unit
 */
void unitListRemoveUnit(Coordinates position, UnitList *unitList);

#endif
