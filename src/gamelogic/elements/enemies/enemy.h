/**
 * @file enemy.h
 * @brief Header file for enemy-related functions and structures.
 */

#ifndef ENEMY_H
#define ENEMY_H

#include "gamelogic/utils/position.h"

/**
 * @brief Function pointer type for getting the symbol of an enemy.
 */
typedef char (*EnemySymbolFunction)(void);

/**
 * @brief Structure representing the type of an enemy.
 */
typedef struct {
  EnemySymbolFunction get_symbol; /**< Pointer to the function for getting the enemy's symbol. */
  int speed; /**< The speed of the enemy. */
  int totHP; /**< The total health points of the enemy. */
} EnemyType;

/**
 * @brief Structure representing an enemy.
 */
typedef struct {
  int id; /**< The ID of the enemy. */
  int isDead; /**< Flag indicating if the enemy is dead (1) or alive (0). */
  int actHP; /**< The current health points of the enemy. */
  int hiddenHP; /**< The hidden health points of the enemy. */
  Position position; /**< The position of the enemy. */
  Position deathPosition; /**< The position where the enemy died. */
  const EnemyType *type; /**< Pointer to the type of the enemy. */
} Enemy;

/**
 * @brief Set the position of an enemy.
 * 
 * @param enemy Pointer to the enemy whose position is to be set.
 * @param x The x-coordinate of the new position.
 * @param y The y-coordinate of the new position.
 */
void enemy_set_position(Enemy *enemy, int x, int y);

/**
 * @brief Initialize an enemy.
 * 
 * @param enemy Pointer to the enemy to be initialized.
 * @param type Pointer to the type of the enemy.
 * @param x The initial x-coordinate of the enemy's position.
 * @param y The initial y-coordinate of the enemy's position.
 * @param id The ID of the enemy.
 */
void enemy_init(Enemy *enemy, const EnemyType *type, int x, int y, int id);

/**
 * @brief Get the ID of an enemy.
 * 
 * @param enemy Pointer to the enemy.
 * @return The ID of the enemy.
 */
int enemy_get_id(Enemy *enemy);

/**
 * @brief Get the position of an enemy.
 * 
 * @param enemy Pointer to the enemy.
 * @return Pointer to the position of the enemy.
 */
Position *enemy_get_position(Enemy *enemy);

/**
 * @brief Get the symbol representing an enemy.
 * 
 * @param enemy Pointer to the enemy.
 * @return The symbol representing the enemy.
 */
char enemy_get_symbol(Enemy *enemy);

/**
 * @brief Get the current health points of an enemy.
 * 
 * @param enemy Pointer to the enemy.
 * @return The current health points of the enemy.
 */
int enemy_get_actHP(Enemy *enemy);

/**
 * @brief Get the hidden health points of an enemy.
 * 
 * @param enemy Pointer to the enemy.
 * @return The hidden health points of the enemy.
 */
int enemy_get_hiddenHealth(Enemy *enemy);

/**
 * @brief Make an enemy die.
 * 
 * @param enemy Pointer to the enemy.
 */
void enemy_die(Enemy *enemy);

/**
 * @brief Damage an enemy by a specified amount.
 * 
 * @param enemy Pointer to the enemy.
 * @param amount The amount of damage.
 */
void enemy_damage(Enemy *enemy, int amount);

/**
 * @brief Check if an enemy is dead.
 * 
 * @param enemy Pointer to the enemy.
 * @return 1 if the enemy is dead, 0 otherwise.
 */
int enemy_isDead(Enemy *enemy);

/**
 * @brief Move an enemy in the positive x direction.
 * 
 * @param enemy Pointer to the enemy.
 */
void enemy_move_x(Enemy *enemy);

/**
 * @brief Move an enemy in the positive y direction.
 * 
 * @param enemy Pointer to the enemy.
 */
void enemy_move_y(Enemy *enemy);

/**
 * @brief Move an enemy in the negative x direction.
 * 
 * @param enemy Pointer to the enemy.
 */
void enemy_move_neg_x(Enemy *enemy);

/**
 * @brief Move an enemy in the negative y direction.
 * 
 * @param enemy Pointer to the enemy.
 */
void enemy_move_neg_y(Enemy *enemy);

#endif
