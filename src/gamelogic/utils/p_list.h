#ifndef P_LIST_H
#define P_LIST_H

#include "sprites/sprite.h"
//#include "gamelogic/elements/towers/projectile.h"
#include "gamelogic/elements/enemies/enemy.h"

/**
 * @brief Structure representing a projectile.
 */
typedef struct {
    int damage;                 /**< Damage dealt by the projectile. */
    float speed;                /**< Speed of the projectile. */
    int x;                      /**< X-coordinate of the projectile. */
    int y;                      /**< Y-coordinate of the projectile. */
    float xVelocity;            /**< X velocity of the projectile. */
    float yVelocity;            /**< Y velocity of the projectile. */
    int active;                 /**< Whether the projectile is active. */
    int target_id;              /**< ID of the target. */
    int alive;                  /**< Whether the projectile is alive. */
    long pastTime;              /**< Past time since creation. */
    long creationTime;          /**< Creation time of the projectile. */
    const long MAX_LIFETIME;    /**< Maximum lifetime of the projectile. */
} Projectile;

/**
 * @brief Structure representing a node in the list.
 */
typedef struct ListNode {
    Sprite* sprite;               /**< Pointer to the sprite. */
    Projectile* projectile;       /**< Pointer to the projectile. */
    struct ListNode *next;        /**< Pointer to the next node in the list. */
} ListNode;

/**
 * @brief Structure representing a list of projectiles.
 */
typedef struct {
    ListNode *head;    /**< Pointer to the head of the list. */
} List;

/**
 * @brief Creates a new list of projectiles.
 * 
 * @return Pointer to the newly created list.
 */
List *list_createee();

/**
 * @brief Destroys a list of projectiles, freeing all associated memory.
 * 
 * @param list Pointer to the list to destroy.
 */
void list_destroyyy(List *list);

/**
 * @brief Appends a new projectile to the given list.
 * 
 * @param list Pointer to the list.
 * @param projectile Pointer to the projectile.
 * @param sprite Pointer to the sprite associated with the projectile.
 */
void list_appenddd(List *list, Projectile *projectile, Sprite *sprite);

/**
 * @brief Prints the contents of the given list.
 * 
 * @param list Pointer to the list to print.
 */
void list_printtt(List *list);

/**
 * @brief Removes a projectile from the given list.
 * 
 * @param list Pointer to the list.
 * @param projectile Pointer to the projectile to remove.
 */
void list_removeee(List* list, Projectile* projectile);

#endif
