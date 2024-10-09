/**
 * @file tower.h
 * @brief Header file for tower-related functions and structures.
 */

#ifndef TOWER_H
#define TOWER_H

#include "gamelogic/elements/enemies/enemy.h"
#include "gamelogic/utils/position.h"

/**
 * @brief Structure representing the type of a tower.
 */
typedef struct {
  char towerSymbol; /**< The symbol representing the tower. */
  int life; /**< The life of the tower. */
  int level; /**< The level of the tower. */
  int range; /**< The range of the tower. */
  int cost; /**< The cost of the tower. */
  int firingRate; /**< The firing rate of the tower. */
  int damage; /**< The damage of the tower. */
} TowerType;

/**
 * @brief Structure representing a tower.
 */
typedef struct {
  char towerSymbol; /**< The symbol representing the tower. */
  int damages; /**< The damage dealt by the tower. */
  int life; /**< The life of the tower. */
  int level; /**< The level of the tower. */
  int range; /**< The range of the tower. */
  int cost; /**< The cost of the tower. */
  int targeted; /**< Flag indicating if the tower is targeted (1) or not (0). */
  Position position; /**< The position of the tower. */
  int enemy_target_id; /**< The ID of the targeted enemy. */
  long lastFiredTime; /**< The time when the tower last fired. */
  long pastTime; /**< The time passed since the last action of the tower. */
  const TowerType *type; /**< Pointer to the type of the tower. */
} Tower;

/**
 * @brief Initialize a tower.
 * 
 * @param tower Pointer to the tower to be initialized.
 * @param type Pointer to the type of the tower.
 * @param x The x-coordinate of the tower's position.
 * @param y The y-coordinate of the tower's position.
 */
void tower_init(Tower *tower, const TowerType *type, float x, float y);

/**
 * @brief Get the position of a tower.
 * 
 * @param tower Pointer to the tower.
 * @return Pointer to the position of the tower.
 */
Position *tower_get_position(Tower *tower);

/**
 * @brief Get the symbol representing a tower.
 * 
 * @param tower Pointer to the tower.
 * @return The symbol representing the tower.
 */
char tower_get_symbol(Tower *tower);

/**
 * @brief Get the life of a tower.
 * 
 * @param tower Pointer to the tower.
 * @return The life of the tower.
 */
int tower_get_life(Tower *tower);

/**
 * @brief Get the level of a tower.
 * 
 * @param tower Pointer to the tower.
 * @return The level of the tower.
 */
int tower_get_level(Tower *tower);

/**
 * @brief Get the range of a tower.
 * 
 * @param tower Pointer to the tower.
 * @return The range of the tower.
 */
int tower_get_range(Tower *tower);

/**
 * @brief Get the cost of a tower.
 * 
 * @param tower Pointer to the tower.
 * @return The cost of the tower.
 */
int tower_get_cost(Tower *tower);

/**
 * @brief Upgrade a tower.
 * 
 * @param tower Pointer to the tower to be upgraded.
 */
void tower_upgrade(Tower *tower);

/**
 * @brief Check if a tower is targeted.
 * 
 * @param tower Pointer to the tower.
 * @return 1 if the tower is targeted, 0 otherwise.
 */
int tower_is_targeted(Tower *tower);

/**
 * @brief Set the targeted status of a tower.
 * 
 * @param tower Pointer to the tower.
 * @param targeted The targeted status to set (1 for targeted, 0 for not targeted).
 */
void tower_set_targeted(Tower *tower, int targeted);

/**
 * @brief Set the target of a tower to a specific enemy.
 * 
 * @param tower Pointer to the tower.
 * @param enemy_target_id The ID of the enemy to target.
 */
void set_target(Tower *tower, int enemy_target_id);

/**
 * @brief Upgrade a tower.
 * 
 * @param tower Pointer to the tower to be upgraded.
 */
void upgrade_tower(Tower *tower);

/**
 * @brief Calculate the distance between a tower and an enemy.
 * 
 * @param tower Pointer to the tower.
 * @param enemy Pointer to the enemy.
 * @return The distance between the tower and the enemy.
 */
int calculate_distance(Tower *tower, Enemy *enemy);

#endif
