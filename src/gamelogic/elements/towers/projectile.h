/**
 * @file projectile.h
 * @brief Header file for projectile-related functions and structures.
 */

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "gamelogic/elements/enemies/enemy.h"
#include "gamelogic/elements/towers/tower_constructors.h"
#include "gamelogic/utils/p_list.h"

/**
 * @brief Initialize a projectile.
 * 
 * @param projectile Pointer to the projectile to be initialized.
 * @param x1 The initial x-coordinate of the projectile's starting position.
 * @param x2 The initial x-coordinate of the projectile's target position.
 * @param x The initial x-coordinate of the projectile's position.
 * @param y The initial y-coordinate of the projectile's position.
 * @param target_id The ID of the target enemy.
 * @param speed The speed of the projectile.
 * @param damage The damage inflicted by the projectile.
 */
void projectile_init(Projectile *projectile, int x1, int x2, float x, float y, int target_id, float speed, int damage);

/**
 * @brief Check if a projectile is alive.
 * 
 * @param projectile Pointer to the projectile.
 * @return 1 if the projectile is alive, 0 otherwise.
 */
int projectile_is_alive(Projectile *projectile);

/**
 * @brief Check if a projectile collides with a specified area.
 * 
 * @param projectile Pointer to the projectile.
 * @param x The x-coordinate of the area to check.
 * @param y The y-coordinate of the area to check.
 * @param x2 The x-coordinate of the opposite corner of the area to check.
 * @param y2 The y-coordinate of the opposite corner of the area to check.
 * @return 1 if the projectile collides with the area, 0 otherwise.
 */
int projectile_check_collision(Projectile *projectile, float x, float y, float x2, float y2);

/**
 * @brief Check if a projectile is active.
 * 
 * @param projectile Pointer to the projectile.
 * @return 1 if the projectile is active, 0 otherwise.
 */
int projectile_is_active(Projectile *projectile);

/**
 * @brief Set the activity status of a projectile.
 * 
 * @param projectile Pointer to the projectile.
 * @param active The activity status to set (1 for active, 0 for inactive).
 */
void projectile_set_active(Projectile *projectile, int active);

/**
 * @brief Get the damage inflicted by a projectile.
 * 
 * @param projectile Pointer to the projectile.
 * @return The damage inflicted by the projectile.
 */
int projectile_get_damage(Projectile *projectile);

/**
 * @brief Create a projectile.
 * 
 * @param x1 The initial x-coordinate of the projectile's starting position.
 * @param x2 The initial x-coordinate of the projectile's target position.
 * @param x The initial x-coordinate of the projectile's position.
 * @param y The initial y-coordinate of the projectile's position.
 * @param target_id The ID of the target enemy.
 * @param speed The speed of the projectile.
 * @param damage The damage inflicted by the projectile.
 * @return Pointer to the created projectile.
 */
Projectile *create_projectile(int x1, int x2, float x, float y, int target_id, float speed, int damage);

/**
 * @brief Get the ID of the target enemy of a projectile.
 * 
 * @param projectile Pointer to the projectile.
 * @return The ID of the target enemy.
 */
int get_target(Projectile *projectile);

#endif
