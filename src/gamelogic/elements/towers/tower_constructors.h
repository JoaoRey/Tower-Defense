/**
 * @file tower_constructors.h
 * @brief Header file for tower constructor functions.
 */

#ifndef TOWER_CONSTRUCTORS_H_
#define TOWER_CONSTRUCTORS_H_

#include "gamelogic/elements/towers/tower.h"

#include <stdlib.h>

/**
 * @brief Get the symbol representing a cannon tower.
 * 
 * @return The symbol representing a cannon tower.
 */
char canon_tower_symbol();

/**
 * @brief Get the symbol representing an archer tower.
 * 
 * @return The symbol representing an archer tower.
 */
char archer_tower_symbol();

/**
 * @brief Get the symbol representing a mage tower.
 * 
 * @return The symbol representing a mage tower.
 */
char mage_tower_symbol();

/**
 * @brief Create a cannon tower.
 * 
 * @param tower Pointer to the tower to be created.
 * @param x The x-coordinate of the tower's position.
 * @param y The y-coordinate of the tower's position.
 */
void create_canon_tower(Tower *tower, float x, float y);

/**
 * @brief Create an archer tower.
 * 
 * @param tower Pointer to the tower to be created.
 * @param x The x-coordinate of the tower's position.
 * @param y The y-coordinate of the tower's position.
 */
void create_archer_tower(Tower *tower, float x, float y);

/**
 * @brief Create a mage tower.
 * 
 * @param tower Pointer to the tower to be created.
 * @param x The x-coordinate of the tower's position.
 * @param y The y-coordinate of the tower's position.
 */
void create_mage_tower(Tower *tower, float x, float y);

#endif
