#ifndef POSITION_H
#define POSITION_H

/**
 * @brief Structure representing a position with x and y coordinates.
 */
typedef struct {
    float x; /**< X-coordinate of the position. */
    float y; /**< Y-coordinate of the position. */
} Position;

/**
 * @brief Initializes a Position structure with the given x and y coordinates.
 * 
 * @param position Pointer to the Position structure to initialize.
 * @param x X-coordinate to set.
 * @param y Y-coordinate to set.
 */
void position_init(Position *position, float x, float y);

/**
 * @brief Sets the x-coordinate of the given Position.
 * 
 * @param position Pointer to the Position structure.
 * @param x X-coordinate to set.
 */
void position_setX(Position *position, float x);

/**
 * @brief Sets the y-coordinate of the given Position.
 * 
 * @param position Pointer to the Position structure.
 * @param y Y-coordinate to set.
 */
void position_setY(Position *position, float y);

/**
 * @brief Gets the x-coordinate of the given Position.
 * 
 * @param position Pointer to the Position structure.
 * @return The x-coordinate of the position.
 */
float position_getX(Position *position);

/**
 * @brief Gets the y-coordinate of the given Position.
 * 
 * @param position Pointer to the Position structure.
 * @return The y-coordinate of the position.
 */
float position_getY(Position *position);

/**
 * @brief Compares two Position structures for equality.
 * 
 * @param position1 Pointer to the first Position structure.
 * @param position2 Pointer to the second Position structure.
 * @return 1 if the positions are equal, 0 otherwise.
 */
int position_equals(Position *position1, Position *position2);

/**
 * @brief Computes a hash code for the given Position.
 * 
 * @param position Pointer to the Position structure.
 * @return The hash code for the position.
 */
int position_hashCode(Position *position);

#endif
