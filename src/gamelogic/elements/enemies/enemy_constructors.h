/**
 * @file enemy_constructors.h
 * @brief Header file for enemy constructors.
 */

#ifndef _ENEMY_CONSTRUCTORS_H_
#define _ENEMY_CONSTRUCTORS_H_

#include "enemy.h"

/**
 * @brief Get the symbol representing an orc enemy.
 * 
 * @return The symbol representing an orc enemy.
 */
char orc_symbol();

/**
 * @brief Get the symbol representing a skeleton enemy.
 * 
 * @return The symbol representing a skeleton enemy.
 */
char skeleton_symbol();

/**
 * @brief Get the symbol representing a golem enemy.
 * 
 * @return The symbol representing a golem enemy.
 */
char golem_symbol();

/**
 * @brief Create an orc enemy with the specified parameters.
 * 
 * @param enemy Pointer to the Enemy structure to be initialized.
 * @param x The x-coordinate of the orc enemy.
 * @param y The y-coordinate of the orc enemy.
 * @param id The ID of the orc enemy.
 */
void create_orc(Enemy *enemy, int x, int y, int id);

/**
 * @brief Create a skeleton enemy with the specified parameters.
 * 
 * @param enemy Pointer to the Enemy structure to be initialized.
 * @param x The x-coordinate of the skeleton enemy.
 * @param y The y-coordinate of the skeleton enemy.
 * @param id The ID of the skeleton enemy.
 */
void create_skeleton(Enemy *enemy, int x, int y, int id);

/**
 * @brief Create a golem enemy with the specified parameters.
 * 
 * @param enemy Pointer to the Enemy structure to be initialized.
 * @param x The x-coordinate of the golem enemy.
 * @param y The y-coordinate of the golem enemy.
 * @param id The ID of the golem enemy.
 */
void create_golem(Enemy *enemy, int x, int y, int id);

#endif
