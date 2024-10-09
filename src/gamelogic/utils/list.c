#include "list.h"

EnemyList *list_create() {
  EnemyList *list = (EnemyList *) malloc(sizeof(EnemyList));
  if (list != NULL) {
    list->head = NULL;
  }
  return list;
}

void list_destroy(EnemyList *list) {
  if (list == NULL) {
    return;
  }
  SpriteEnemy *current = list->head;
  while (current != NULL) {
    SpriteEnemy *next = current->next;
    destroy_sprite(current->sprite);
    free(current->enemy);
    free(current);
    current = next;
  }
  free(list);
}

void list_append(EnemyList *list, Sprite *sprite, Enemy *enemy) {
  if (list == NULL) {
    return;
  }
  SpriteEnemy *new_node = (SpriteEnemy *) malloc(sizeof(SpriteEnemy));
  if (new_node == NULL) {
    return;
  }
  new_node->sprite = sprite;
  new_node->enemy = enemy;
  new_node->next = NULL;
  if (list->head == NULL) {
    list->head = new_node;
  }
  else {
    SpriteEnemy *current = list->head;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = new_node;
  }
}

void list_print(EnemyList *list) {
  if (list == NULL) {
    return;
  }
  SpriteEnemy *current = list->head;
  while (current != NULL) {
    printf("Sprite: %p, Enemy: %p\n", (void *) current->sprite, (void *) current->enemy);
    current = current->next;
  }
}

void list_remove(EnemyList *list, Enemy *enemy) {
  if (list == NULL || enemy == NULL) {
    return;
  }
  SpriteEnemy *current = list->head;
  SpriteEnemy *previous = NULL;

  while (current != NULL) {
    if (current->enemy == enemy) {
      if (previous == NULL) {
        list->head = current->next;
      }
      else {
        previous->next = current->next;
      }
      destroy_sprite(current->sprite);
      free(current->enemy);
      free(current);
      return;
    }
    previous = current;
    current = current->next;
  }
}

TowerList *list_createe() {
  TowerList *list = (TowerList *) malloc(sizeof(TowerList));
  if (list == NULL) {
  }

  if (list != NULL) {
    list->head = NULL;
  }
  return list;
}

void list_destroyy(TowerList *list) {
  if (list == NULL) {
    return;
  }
  SpriteTower *current = list->head;
  while (current != NULL) {
    SpriteTower *next = current->next;
    destroy_sprite(current->sprite);
    free(current->tower);
    free(current);
    current = next;
  }
  free(list);
}

void list_appendd(TowerList *list, Sprite *sprite, Tower *enemy) {
  if (list == NULL) {
    return;
  }
  SpriteTower *new_node = (SpriteTower *) malloc(sizeof(SpriteTower));
  if (new_node == NULL) {
    return;
  }
  new_node->sprite = sprite;
  new_node->tower = enemy;
  new_node->next = NULL;
  if (list->head == NULL) {
    list->head = new_node;
  }
  else {
    SpriteTower *current = list->head;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = new_node;
  }
}

void list_printt(TowerList *list) {
  if (list == NULL) {
    return;
  }
  SpriteTower *current = list->head;
  while (current != NULL) {
    printf("Sprite: %p, Enemy: %p\n", (void *) current->sprite, (void *) current->tower);
    current = current->next;
  }
}
