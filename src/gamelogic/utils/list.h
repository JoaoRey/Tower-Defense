#ifndef LIST_H
#define LIST_H

#include "sprites/sprite.h"
#include "gamelogic/elements/enemies/enemy.h"
#include "gamelogic/elements/towers/tower.h"

/**
 * @brief Structure representing a tower with its associated sprite.
 */
typedef struct SpriteTower {
    Sprite* sprite;              /**< Pointer to the sprite. */
    Tower* tower;                /**< Pointer to the tower. */
    struct SpriteTower* next;    /**< Pointer to the next SpriteTower in the list. */
} SpriteTower;

/**
 * @brief Structure representing a list of towers.
 */
typedef struct {
    SpriteTower* head;    /**< Pointer to the head of the tower list. */
} TowerList;

/**
 * @brief Structure representing an enemy with its associated sprite.
 */
typedef struct SpriteEnemy {
    Sprite* sprite;              /**< Pointer to the sprite. */
    Enemy* enemy;                /**< Pointer to the enemy. */
    struct SpriteEnemy* next;    /**< Pointer to the next SpriteEnemy in the list. */
} SpriteEnemy;

/**
 * @brief Structure representing a list of enemies.
 */
typedef struct {
    SpriteEnemy* head;    /**< Pointer to the head of the enemy list. */
} EnemyList;

/**
 * @brief Creates a new EnemyList.
 * 
 * @return Pointer to the newly created EnemyList.
 */
EnemyList* list_create();

/**
 * @brief Destroys an EnemyList, freeing all associated memory.
 * 
 * @param list Pointer to the EnemyList to destroy.
 */
void list_destroy(EnemyList* list);

/**
 * @brief Appends a new SpriteEnemy to the given EnemyList.
 * 
 * @param list Pointer to the EnemyList.
 * @param sprite Pointer to the sprite associated with the enemy.
 * @param enemy Pointer to the enemy.
 */
void list_append(EnemyList* list, Sprite* sprite, Enemy* enemy);

/**
 * @brief Prints the contents of the given EnemyList.
 * 
 * @param list Pointer to the EnemyList to print.
 */
void list_print(EnemyList* list);

/**
 * @brief Removes an enemy from the given EnemyList.
 * 
 * @param list Pointer to the EnemyList.
 * @param enemy Pointer to the enemy to remove.
 */
void list_remove(EnemyList* list, Enemy* enemy);

/**
 * @brief Creates a new TowerList.
 * 
 * @return Pointer to the newly created TowerList.
 */
TowerList* list_createe();

/**
 * @brief Destroys a TowerList, freeing all associated memory.
 * 
 * @param list Pointer to the TowerList to destroy.
 */
void list_destroyy(TowerList* list);

/**
 * @brief Appends a new SpriteTower to the given TowerList.
 * 
 * @param list Pointer to the TowerList.
 * @param sprite Pointer to the sprite associated with the tower.
 * @param tower Pointer to the tower.
 */
void list_appendd(TowerList* list, Sprite* sprite, Tower* tower);

/**
 * @brief Prints the contents of the given TowerList.
 * 
 * @param list Pointer to the TowerList to print.
 */
void list_printt(TowerList* list);

#endif
