#ifndef MIDDLE_AGES_COORDINATES_H
#define MIDDLE_AGES_COORDINATES_H

typedef struct {
    long x;
    long y;
} Coordinates;

int coordinatesCompare(Coordinates a, Coordinates b);
long coordinatesDistance(Coordinates a, Coordinates b);

#endif
