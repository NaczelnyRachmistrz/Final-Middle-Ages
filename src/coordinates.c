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

static long max(long a, long b) {
    return a > b ? a : b;
}

static long abs(long a) {
    return a >= 0 ? a : -a;
}

long coordinatesDistance(Coordinates a, Coordinates b) {
    return max(abs(a.x - b.x), abs(a.y - b.y));
}