#include <stdlib.h>
#include "units.h"

unit new_unit(enum unit_type type, int x, int y) {
    unit u =  (unit) malloc(sizeof(struct def_unit));
    u->type = type;
    u->x = x;
    u->y = y;
    return u;
}