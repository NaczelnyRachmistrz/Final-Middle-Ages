/**
 * @file coordinates.h
 * Library implementing coordinates structure and functions on them
 */
#ifndef MIDDLE_AGES_COORDINATES_H
#define MIDDLE_AGES_COORDINATES_H

/**
 * @struct Coordinates
 * @brief Represents pair of long int
 */
typedef struct {
    long x; /**< abscissa */
    long y; /**< ordinate */
} Coordinates;

/**
 * @brief Compares coordinates
 * Lexicographically compares given coordinates
 * @param a coordinates against which comparison is done
 * @param b coordinates to compare with
 * @return result of comparison
 */
int coordinatesCompare(Coordinates a, Coordinates b);

/**
 * @brief Measures the distance between given coordinates
 * Measure is done in the maximum norm
 * @param a
 * @param b
 * @returns distance between given coordinates
 */
long coordinatesDistance(Coordinates a, Coordinates b);

#endif
