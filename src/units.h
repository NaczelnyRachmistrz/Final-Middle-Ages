#ifndef MIDDLE_AGES_UNITS_H
#define MIDDLE_AGES_UNITS_H

enum UnitType {
    UNDEFINED = 0,
    PEASANT = 1,
    KING = 2,
    KNIGHT = 3
};

typedef struct {
    int x;
    int y;
} Coordinates;

typedef struct  {
    enum UnitType type;
    int player;

    Coordinates position;
    int lastMove;
} Unit;

struct UnitListNode;
typedef struct UnitListNode UnitList;

typedef struct UnitListNode {
    Unit * unit;
    UnitList * next;
};

Unit * newUnit(enum UnitType type, int player, Coordinates position, int turn);
void removeUnit(Unit * unit);

Unit * newUnitList();
void removeUnitList(UnitList * unitList);
void addUnitToList(Unit * unit, UnitList * unitList);

#endif //MIDDLE_AGES_UNITS_H
