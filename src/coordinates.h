#ifndef MIDDLE_AGES_COORDINATES_H
#define MIDDLE_AGES_COORDINATES_H

typedef struct {
    int x;
    int y;
} Coordinates;

int coordinatesCompare(Coordinates a, Coordinates b);
int coordinatesDistance(Coordinates a, Coordinates b);

#endif
