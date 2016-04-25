#ifndef MIDDLE_AGES_UNITS_H
#define MIDDLE_AGES_UNITS_H

enum unit_type {
    UNDEFINED = 0,
    PEASANT = 1,
    KING = 2,
    KNIGHT = 3
};

typedef struct def_unit* unit;

struct def_unit {
    enum unit_type type;
    int x;
    int y;
    int last_move;
};

unit new_unit(enum unit_type type, int x, int y);

#endif //MIDDLE_AGES_UNITS_H
