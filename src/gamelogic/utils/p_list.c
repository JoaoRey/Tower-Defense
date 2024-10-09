#include "gamelogic/utils/p_list.h"
#include <stdio.h>
#include <stdlib.h>

List *list_createee() {
  List *list = (List *) malloc(sizeof(List));
  if (list != NULL) {
    list->head = NULL;
  }
  return list;
}

void list_destroyyy(List *list) {
  if (list == NULL) {
    return;
  }
  ListNode *current = list->head;
  while (current != NULL) {
    ListNode *next = current->next;
    destroy_sprite(current->sprite);
    free(current->projectile);
    free(current);
    current = next;
  }
  free(list);
}

void list_appenddd(List *list, Projectile *projectile, Sprite *sprite) {
  if (list == NULL) {
    return;
  }
  ListNode *new_node = (ListNode *) malloc(sizeof(ListNode));
  if (new_node == NULL) {
    return;
  }
  new_node->sprite = sprite;
  new_node->projectile = projectile;
  new_node->next = NULL;
  if (list->head == NULL) {
    list->head = new_node;
  }
  else {
    ListNode *current = list->head;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = new_node;
  }
}

void list_printtt(List *list) {
  if (list == NULL) {
    return;
  }
  ListNode *current = list->head;
  while (current != NULL) {
    printf("Sprite: %p, Enemy: %p\n", (void *) current->sprite, (void *) current->projectile);
    current = current->next;
  }
}

void list_removeee(List *list, Projectile *projectile) {
  if (list == NULL || projectile == NULL) {
    return;
  }
  ListNode *current = list->head;
  ListNode *previous = NULL;

  while (current != NULL) {
    if (current->projectile == projectile) {
      if (previous == NULL) {
        list->head = current->next;
      }
      else {
        previous->next = current->next;
      }
      destroy_sprite(current->sprite);
      free(current->projectile);
      free(current);
      return;
    }
    previous = current;
    current = current->next;
  }
}
