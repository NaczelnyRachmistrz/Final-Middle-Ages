#include <stdlib.h>
#include "units.h"

unit new_unit(enum unit_type type, int x, int y) {
    return & {type, x, y };
}