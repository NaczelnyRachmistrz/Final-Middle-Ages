#include "coordinates.h"

int coordinatesCompare(Coordinates a, Coordinates b) {
    if (a.x == b.x) {
        if (a.y == b.y) {
            return 0;
        } else {
            return a.y > b.y ? 1 : -1;
        }
    } else {
        return a.x > b.x ? 1 : -1;
    }
}