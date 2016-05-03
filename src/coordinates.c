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

static int max(int a, int b) {
    return a > b ? a : b;
}

static int abs(int a) {
    return a >= 0 ? a : -a;
}

int coordinatesDistance(Coordinates a, Coordinates b) {
    return max(abs(a.x - b.x), abs(a.y - b.y));
}