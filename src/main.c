#include "devices/graphic/graphics.h"
#include "devices/mouse/mouse.h"
#include "devices/rtc/rtc.h"
#include "devices/timer/timer.h"
#include "gamelogic/elements/enemies/enemy.h"
#include "gamelogic/elements/enemies/enemy_constructors.h"
#include "gamelogic/elements/towers/projectile.h"
#include "gamelogic/elements/towers/tower.h"
#include "gamelogic/elements/towers/tower_constructors.h"
#include "gamelogic/states/game.h"
#include "gamelogic/states/leaderboard.h"
#include "gamelogic/states/menu.h"
#include "gamelogic/utils/list.h"
#include "gamelogic/utils/position.h"
#include "macros/VBE.h"
#include "macros/game_modes.h"
#include "macros/i8042.h"
#include "macros/i8254.h"
#include "sprites/sprite.h"
#include <assert.h>
#include <lcom/lcf.h>
#include <lcom/xpm.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

extern uint8_t keyboard_scancode;
extern uint8_t *drawer_buffer;
extern uint8_t *image_loader;
extern uint8_t mouse_byte;
extern uint8_t mouse_bytes_array[3];
extern uint8_t mouse_bytes_index;
extern uint8_t byte_used;
extern int x;
extern int y;
extern struct packet mouse_packet_structure;
extern int counter;
extern unsigned int bytes_being_user_per_pixel;
extern uint16_t x_res;
extern uint16_t y_res;
List *projectile_list;
EnemyList *sprite_list;
TowerList *tower_list;
SpriteTower *tsp;
ListNode *listnode;
int mode_of_game;

char player_name[10] = {0};
int name_length = 0;
int coins = 300;
int score = 0;
int chest_life = 5000;
int selected = 0;
int select0 = 1;
int select1 = 1;
int select2 = 1;
int select3 = 1;
int select4 = 1;
int select5 = 1;
int count = 0;
int level = 1;
int num = 0;
bool q = FALSE;

int(main)(int argc, char *argv[]) {
  lcf_set_language("EN-US");
  if (lcf_start(argc, argv))
    return 1;
  lcf_cleanup();
  return 0;
}

int(game_loop)() {
  int ipc_status;
  message msg;
  uint8_t kbd_mask, mouse_mask, timer_mask;
  mode_of_game = MAIN_MENU;

  if (configure_timer_freq(0, 30) != 0) {
    return 1;
  }
  if (subscription_of_timer_interrupts(&timer_mask) != 0) {
    return 1;
  }
  if (subscription_of_keyboard_interrupts(&kbd_mask) != 0) {
    return 1;
  }
  if (subscription_of_mouse_interrupts(&mouse_mask) != 0) {
    return 1;
  }

  while (mode_of_game != QUIT) {
    if ((driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed\n");
      return 1;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & timer_mask) {
            counter++;
            if (mode_of_game == MAIN_MENU) {
              draw_menu(x, y);
              update_rtc_time();
              draw_rtc();
            }
            else if (mode_of_game == GAME) {
              draw_game();
              if (counter % 5 == 0) {
                score++;
              }
              if (chest_life <= 0) {
                mode_of_game = LEADERBOARD;
              }
              int padding = 225;
              Sprite *number;
              int scorezin = score;
              for (int i = 0; i < 5; i++) {
                if (scorezin % 10 == 0) {
                  number = sprite_init((xpm_map_t) draw_zero_xpm, x_res / 2 + padding, 15, 0, 0);
                  draw_sprite(number);
                }
                else if (scorezin % 10 == 1) {
                  number = sprite_init((xpm_map_t) draw_one_xpm, x_res / 2 + padding, 15, 0, 0);
                  draw_sprite(number);
                }
                else if (scorezin % 10 == 2) {
                  number = sprite_init((xpm_map_t) draw_two_xpm, x_res / 2 + padding, 15, 0, 0);
                  draw_sprite(number);
                }
                else if (scorezin % 10 == 3) {
                  number = sprite_init((xpm_map_t) draw_three_xpm, x_res / 2 + padding, 15, 0, 0);
                  draw_sprite(number);
                }
                else if (scorezin % 10 == 4) {
                  number = sprite_init((xpm_map_t) draw_four_xpm, x_res / 2 + padding, 15, 0, 0);
                  draw_sprite(number);
                }
                else if (scorezin % 10 == 5) {
                  number = sprite_init((xpm_map_t) draw_five_xpm, x_res / 2 + padding, 15, 0, 0);
                  draw_sprite(number);
                }
                else if (scorezin % 10 == 6) {
                  number = sprite_init((xpm_map_t) draw_six_xpm, x_res / 2 + padding, 15, 0, 0);
                  draw_sprite(number);
                }
                else if (scorezin % 10 == 7) {
                  number = sprite_init((xpm_map_t) draw_seven_xpm, x_res / 2 + padding, 15, 0, 0);
                  draw_sprite(number);
                }
                else if (scorezin % 10 == 8) {
                  number = sprite_init((xpm_map_t) draw_eight_xpm, x_res / 2 + padding, 15, 0, 0);
                  draw_sprite(number);
                }
                else if (scorezin % 10 == 9) {
                  number = sprite_init((xpm_map_t) draw_nine_xpm, x_res / 2 + padding, 15, 0, 0);
                  draw_sprite(number);
                }
                scorezin /= 10;
                padding -= 13;
              }
              int lifezin = chest_life;
              Sprite *numbers;
              int paddings = 10;
              for (int i = 0; i < 4; i++) {
                if (lifezin % 10 == 0) {
                  numbers = sprite_init((xpm_map_t) draw_zero_xpm, x_res / 2 + paddings, 15, 0, 0);
                  draw_sprite(numbers);
                }
                else if (lifezin % 10 == 1) {
                  numbers = sprite_init((xpm_map_t) draw_one_xpm, x_res / 2 + paddings, 15, 0, 0);
                  draw_sprite(numbers);
                }
                else if (lifezin % 10 == 2) {
                  numbers = sprite_init((xpm_map_t) draw_two_xpm, x_res / 2 + paddings, 15, 0, 0);
                  draw_sprite(numbers);
                }
                else if (lifezin % 10 == 3) {
                  numbers = sprite_init((xpm_map_t) draw_three_xpm, x_res / 2 + paddings, 15, 0, 0);
                  draw_sprite(numbers);
                }
                else if (lifezin % 10 == 4) {
                  numbers = sprite_init((xpm_map_t) draw_four_xpm, x_res / 2 + paddings, 15, 0, 0);
                  draw_sprite(numbers);
                }
                else if (lifezin % 10 == 5) {
                  numbers = sprite_init((xpm_map_t) draw_five_xpm, x_res / 2 + paddings, 15, 0, 0);
                  draw_sprite(numbers);
                }
                else if (lifezin % 10 == 6) {
                  numbers = sprite_init((xpm_map_t) draw_six_xpm, x_res / 2 + paddings, 15, 0, 0);
                  draw_sprite(numbers);
                }
                else if (lifezin % 10 == 7) {
                  numbers = sprite_init((xpm_map_t) draw_seven_xpm, x_res / 2 + paddings, 15, 0, 0);
                  draw_sprite(numbers);
                }
                else if (lifezin % 10 == 8) {
                  numbers = sprite_init((xpm_map_t) draw_eight_xpm, x_res / 2 + paddings, 15, 0, 0);
                  draw_sprite(numbers);
                }
                else if (lifezin % 10 == 9) {
                  numbers = sprite_init((xpm_map_t) draw_nine_xpm, x_res / 2 + paddings, 15, 0, 0);
                  draw_sprite(numbers);
                }
                lifezin /= 10;
                paddings -= 13;
              }

              int coinzin = coins;
              Sprite *numberss;
              int paddingss = 115;
              for (int i = 0; i < 4; i++) {
                if (coinzin % 10 == 0) {
                  numberss = sprite_init((xpm_map_t) draw_zero_xpm, x_res / 2 + paddingss, 15, 0, 0);
                  draw_sprite(numberss);
                }
                else if (coinzin % 10 == 1) {
                  numberss = sprite_init((xpm_map_t) draw_one_xpm, x_res / 2 + paddingss, 15, 0, 0);
                  draw_sprite(numberss);
                }
                else if (coinzin % 10 == 2) {
                  numberss = sprite_init((xpm_map_t) draw_two_xpm, x_res / 2 + paddingss, 15, 0, 0);
                  draw_sprite(numberss);
                }
                else if (coinzin % 10 == 3) {
                  numberss = sprite_init((xpm_map_t) draw_three_xpm, x_res / 2 + paddingss, 15, 0, 0);
                  draw_sprite(numberss);
                }
                else if (coinzin % 10 == 4) {
                  numberss = sprite_init((xpm_map_t) draw_four_xpm, x_res / 2 + paddingss, 15, 0, 0);
                  draw_sprite(numberss);
                }
                else if (coinzin % 10 == 5) {
                  numberss = sprite_init((xpm_map_t) draw_five_xpm, x_res / 2 + paddingss, 15, 0, 0);
                  draw_sprite(numberss);
                }
                else if (coinzin % 10 == 6) {
                  numberss = sprite_init((xpm_map_t) draw_six_xpm, x_res / 2 + paddingss, 15, 0, 0);
                  draw_sprite(numberss);
                }
                else if (coinzin % 10 == 7) {
                  numberss = sprite_init((xpm_map_t) draw_seven_xpm, x_res / 2 + paddingss, 15, 0, 0);
                  draw_sprite(numberss);
                }
                else if (coinzin % 10 == 8) {
                  numberss = sprite_init((xpm_map_t) draw_eight_xpm, x_res / 2 + paddingss, 15, 0, 0);
                  draw_sprite(numberss);
                }
                else if (coinzin % 10 == 9) {
                  numberss = sprite_init((xpm_map_t) draw_nine_xpm, x_res / 2 + paddingss, 15, 0, 0);
                  draw_sprite(numberss);
                }
                coinzin /= 10;
                paddingss -= 13;
              }
              draw_selected(&selected);

              if (num == 21 * level) {
                sprite_list = list_create();
                num = 1;
                level++;
                for (int i = 0; i < 7 * level; i++) {
                  Sprite *orc = sprite_init((xpm_map_t) draw_orc_xpm, 50, 0 - (50 * i), 3, 3);
                  Enemy *orc_enemy = (Enemy *) malloc(sizeof(Enemy));
                  create_orc(orc_enemy, 50, 0 - (50 * i) - 4, num);
                  num++;
                  list_append(sprite_list, orc, orc_enemy);
                }
                for (int i = 0; i < 10 * level; i++) {
                  Sprite *skeleton = sprite_init((xpm_map_t) draw_skeleton_xpm, 100, 0 - (50 * i) - 2, 2, 2);
                  Enemy *skeleton_enemy = (Enemy *) malloc(sizeof(Enemy));
                  create_skeleton(skeleton_enemy, 100, 0 - (50 * i) - 2, num);
                  num++;
                  list_append(sprite_list, skeleton, skeleton_enemy);
                }
                for (int i = 0; i < 4 * level; i++) {
                  Sprite *golem = sprite_init((xpm_map_t) draw_golem_xpm, 150, 0 - (50 * i) - 1, 1, 1);
                  Enemy *golem_enemy = (Enemy *) malloc(sizeof(Enemy));
                  create_golem(golem_enemy, 150, 0 - (50 * i) - 1, num);
                  num++;
                  list_append(sprite_list, golem, golem_enemy);
                }
                count = 0;
                num = 0;
                break;
              }
              SpriteEnemy *currentt = sprite_list->head;
              tsp = tower_list->head;
              currentt = sprite_list->head;
              if (tsp != NULL) {
                while (currentt != NULL && currentt->enemy->id != tsp->tower->enemy_target_id) {
                  currentt = currentt->next;
                }
                if (currentt != NULL && tsp->tower->targeted == 1) {
                  ListNode *listnode = projectile_list->head;
                  while (listnode != NULL) {
                    if (listnode->projectile->active == 1 || listnode->projectile->target_id != -1) {
                      float dx = currentt->sprite->x - listnode->sprite->x;
                      float dy = currentt->sprite->y - listnode->sprite->y;
                      float distance = sqrt(dx * dx + dy * dy);

                      if (distance != 0) {
                        dx /= distance;
                        dy /= distance;
                      }

                      listnode->sprite->x += dx * 10;
                      listnode->sprite->y += dy * 10;

                      draw_sprite(listnode->sprite);
                      listnode = listnode->next;
                    }
                    else {
                      listnode = listnode->next;
                      continue;
                    }
                  }
                }
              }
              currentt = sprite_list->head;
              SpriteEnemy *prev = NULL;
              while (currentt != NULL) {
                if (currentt->enemy->isDead == 1) {
                  if (prev == NULL) {
                    sprite_list->head = currentt->next;
                  }
                  else {
                    prev->next = currentt->next;
                  }
                  SpriteEnemy *temp = currentt;
                  currentt = currentt->next;
                  free(temp);
                  num++;
                  continue;
                }
                if (counter % 60) {
                  if (currentt->sprite->y < 499 && currentt->sprite->x == 50) {
                    move_sprite_y(currentt->sprite);
                    enemy_move_y(currentt->enemy);
                  }
                  else if (currentt->sprite->y < 449 && currentt->sprite->x == 100) {
                    move_sprite_y(currentt->sprite);
                    enemy_move_y(currentt->enemy);
                  }
                  else if (currentt->sprite->y < 400 && currentt->sprite->x == 150) {
                    move_sprite_y(currentt->sprite);
                    enemy_move_y(currentt->enemy);
                  }
                  else if ((currentt->sprite->y == 500 || currentt->sprite->y == 499 || currentt->sprite->y == 501) && currentt->sprite->x < 656) {
                    move_sprite_x(currentt->sprite);
                    enemy_move_x(currentt->enemy);
                  }
                  else if ((currentt->sprite->y == 452 || currentt->sprite->y == 450) && currentt->sprite->x < 603) {
                    move_sprite_x(currentt->sprite);
                    enemy_move_x(currentt->enemy);
                  }
                  else if (currentt->sprite->y == 400 && currentt->sprite->x < 551) {
                    move_sprite_x(currentt->sprite);
                    enemy_move_x(currentt->enemy);
                  }
                  else if (currentt->sprite->y > 221 && currentt->sprite->x == 656) {
                    currentt->sprite->y -= currentt->sprite->yspeed;
                    enemy_move_neg_y(currentt->enemy);
                  }
                  else if (currentt->sprite->y > 171 && currentt->sprite->x == 604) {
                    currentt->sprite->y -= currentt->sprite->yspeed;
                    enemy_move_neg_y(currentt->enemy);
                  }
                  else if (currentt->sprite->y > 121 && currentt->sprite->x < 604) {
                    currentt->sprite->y -= currentt->sprite->yspeed;
                    enemy_move_neg_y(currentt->enemy);
                  }
                  else if ((currentt->sprite->y == 221 || currentt->sprite->y == 220 || currentt->sprite->y == 219) && currentt->sprite->x < 677) {
                    move_sprite_x(currentt->sprite);
                    enemy_move_x(currentt->enemy);
                  }
                  else if ((currentt->sprite->y == 171 || currentt->sprite->y == 170) && currentt->sprite->x < 677) {
                    move_sprite_x(currentt->sprite);
                    enemy_move_x(currentt->enemy);
                  }
                  else if (currentt->sprite->y == 121 && currentt->sprite->x < 677) {
                    move_sprite_x(currentt->sprite);
                    enemy_move_x(currentt->enemy);
                  }
                  else if ((currentt->sprite->x == 677 || currentt->sprite->x == 678 || currentt->sprite->x == 679)) {
                    enemy_die(currentt->enemy);
                    chest_life -= 600;
                  }
                }
                draw_sprite(currentt->sprite);
                prev = currentt;
                currentt = currentt->next;
              }
              ListNode *listnode = projectile_list->head;
              while (listnode != NULL) {
                if (listnode->projectile->target_id != -1) {
                  draw_sprite(listnode->sprite);
                }
                listnode = listnode->next;
              }
              tsp = tower_list->head;
              if (tsp != NULL) {
                while (tsp != NULL) {
                  draw_sprite(tsp->sprite);
                  int padding = 0;
                  int level = tsp->tower->level;
                  Sprite *numberr;
                  for (int i = 0; i < 2; i++) {
                    if (level % 10 == 1) {
                      numberr = sprite_init((xpm_map_t) draw_one_xpm, tsp->tower->position.x + 65 + padding, tsp->tower->position.y, 0, 0);
                      draw_sprite(numberr);
                    }
                    else if (level % 10 == 2) {
                      numberr = sprite_init((xpm_map_t) draw_two_xpm, tsp->tower->position.x + 65 + padding, tsp->tower->position.y, 0, 0);
                      draw_sprite(numberr);
                    }
                    else if (level % 10 == 3) {
                      numberr = sprite_init((xpm_map_t) draw_three_xpm, tsp->tower->position.x + 65 + padding, tsp->tower->position.y, 0, 0);
                      draw_sprite(numberr);
                    }
                    else if (level % 10 == 4) {
                      numberr = sprite_init((xpm_map_t) draw_four_xpm, tsp->tower->position.x + 65 + padding, tsp->tower->position.y, 0, 0);
                      draw_sprite(numberr);
                    }
                    else if (level % 10 == 5) {
                      numberr = sprite_init((xpm_map_t) draw_five_xpm, tsp->tower->position.x + 65 + padding, tsp->tower->position.y, 0, 0);
                      draw_sprite(numberr);
                    }
                    else if (level % 10 == 6) {
                      numberr = sprite_init((xpm_map_t) draw_six_xpm, tsp->tower->position.x + 65 + padding, tsp->tower->position.y, 0, 0);
                      draw_sprite(numberr);
                    }
                    else if (level % 10 == 7) {
                      numberr = sprite_init((xpm_map_t) draw_seven_xpm, tsp->tower->position.x + 65 + padding, tsp->tower->position.y, 0, 0);
                      draw_sprite(numberr);
                    }
                    else if (level % 10 == 8) {
                      numberr = sprite_init((xpm_map_t) draw_eight_xpm, tsp->tower->position.x + 65 + padding, tsp->tower->position.y, 0, 0);
                      draw_sprite(numberr);
                    }
                    else if (level % 10 == 9) {
                      numberr = sprite_init((xpm_map_t) draw_nine_xpm, tsp->tower->position.x + 65 + padding, tsp->tower->position.y, 0, 0);
                      draw_sprite(numberr);
                    }
                    else if (level % 10 == 0) {
                      numberr = sprite_init((xpm_map_t) draw_zero_xpm, tsp->tower->position.x + 65 + padding, tsp->tower->position.y, 0, 0);
                      draw_sprite(numberr);
                    }
                    padding -= 13;
                    level /= 10;
                  }
                  tsp = tsp->next;
                }
              }
              tsp = tower_list->head;
              if (tsp != NULL) {
                if (counter % 10 == 0) {
                  while (tsp != NULL) {
                    draw_sprite(tsp->sprite);
                    while (listnode != NULL) {
                      draw_sprite(listnode->sprite);
                      listnode = listnode->next;
                    }
                    currentt = sprite_list->head;

                    while (currentt != NULL) {
                      if ((currentt->enemy->isDead == 1) || (currentt->enemy->actHP < 0)) {
                        currentt = currentt->next;
                        continue;
                      }
                      tsp->tower->enemy_target_id = currentt->enemy->id;
                      tsp->tower->targeted = 1;
                      if (tower_get_symbol(tsp->tower) == 'A') {
                        Projectile *projectile = (Projectile *) malloc(sizeof(Projectile));
                        Sprite *projectile_sprite = sprite_init((xpm_map_t) draw_arrow_xpm, tsp->tower->position.x, tsp->tower->position.y, 5, 5);
                        create_projectile(tsp->tower->position.x, tsp->tower->position.y, currentt->sprite->x, currentt->sprite->y, currentt->enemy->id, 10, tsp->tower->type->damage);
                        list_appenddd(projectile_list, projectile, projectile_sprite);
                        break;
                      }
                      if (tower_get_symbol(tsp->tower) == 'C') {
                        Projectile *projectile = (Projectile *) malloc(sizeof(Projectile));
                        Sprite *projectile_sprite = sprite_init((xpm_map_t) draw_canon_ball_xpm, tsp->tower->position.x, tsp->tower->position.y, 5, 5);
                        create_projectile(tsp->tower->position.x, tsp->tower->position.y, currentt->sprite->x, currentt->sprite->y, currentt->enemy->id, 10, tsp->tower->type->damage);
                        list_appenddd(projectile_list, projectile, projectile_sprite);
                        break;
                      }
                      if (tower_get_symbol(tsp->tower) == 'M') {
                        Projectile *projectile = (Projectile *) malloc(sizeof(Projectile));
                        Sprite *projectile_sprite = sprite_init((xpm_map_t) draw_fireball_xpm, tsp->tower->position.x, tsp->tower->position.y, 5, 5);
                        create_projectile(tsp->tower->position.x, tsp->tower->position.y, currentt->sprite->x, currentt->sprite->y, currentt->enemy->id, 10, tsp->tower->type->damage);
                        projectile->active = 1;
                        list_appenddd(projectile_list, projectile, projectile_sprite);
                        break;
                      }
                      currentt = currentt->next;
                    }
                    tsp = tsp->next;
                  }
                }
              }
              tsp = tower_list->head;
              currentt = sprite_list->head;
              if (tsp != NULL) {
                while (currentt != NULL && currentt->enemy->id != tsp->tower->enemy_target_id) {
                  currentt = currentt->next;
                }
                if (currentt != NULL && tsp->tower->targeted == 1) {
                  ListNode *listnode = projectile_list->head;
                  while (listnode != NULL) {
                    if (listnode->projectile->active == 1 || listnode->projectile->target_id != -1) {
                      float dx = currentt->sprite->x - listnode->sprite->x;
                      float dy = currentt->sprite->y - listnode->sprite->y;
                      float distance = sqrt(dx * dx + dy * dy);
                      if (distance <= 30) {
                        listnode->projectile->active = 0;
                        listnode->projectile->target_id = -1;
                        enemy_damage(currentt->enemy, tsp->tower->type->damage);

                        if (currentt->enemy->actHP <= 0) {
                          if (enemy_get_symbol(currentt->enemy) == 'G') {
                            coins += 40;
                          }
                          else if (enemy_get_symbol(currentt->enemy) == 'O') {
                            coins += 25;
                          }
                          else if (enemy_get_symbol(currentt->enemy) == 'S') {
                            coins += 10;
                          }
                          tsp->tower->enemy_target_id = 0;
                          tsp->tower->targeted = 0;
                          currentt = sprite_list->head;

                          continue;
                        }
                      }
                      draw_sprite(listnode->sprite);
                      listnode = listnode->next;
                    }
                    else {
                      listnode = listnode->next;
                      continue;
                    }
                  }
                }
              }
            }
            else if (mode_of_game == OPTIONS) {
              draw_options();
              if (keyboard_scancode == 0x01) {
                mode_of_game = MAIN_MENU;
              }
            }
            else if (mode_of_game == LEADERBOARD) {
              load_leaderboard();
              display_leaderboard();
              if (keyboard_scancode == 0x1C) {
                save_player_data();
                mode_of_game = MAIN_MENU;
              }
              if (keyboard_scancode == 0x01) {
                mode_of_game = MAIN_MENU;
              }
              if (chest_life <= 0 && score > 0) {
                draw_player_name();
              }
            }

            display_mouse();
            copy_buffer_to_screen();
            memset(image_loader, 0, x_res * y_res * bytes_being_user_per_pixel);
          }
          if (msg.m_notify.interrupts & kbd_mask) {
            keyboard_interrupt_handler();
            if ((mode_of_game == GAME && keyboard_scancode == 0x81) || (mode_of_game == LEADERBOARD && (keyboard_scancode == 0x1C || keyboard_scancode == 0x01))) {
              if (score > 0 && chest_life <= 0) {
                save_player_data();
              }
              mode_of_game = MAIN_MENU;
              player_name[0] = '\0';
              name_length = 0;
              chest_life = 5000;
              coins = 300;
              score = 0;
              selected = 0;
              select0 = 1;
              select1 = 1;
              select2 = 1;
              select3 = 1;
              select4 = 1;
              select5 = 1;
              count = 0;
              level = 1;
              num = 0;
              list_destroy(sprite_list);
              list_destroyy(tower_list);
              list_destroyyy(projectile_list);
              tower_list = list_createe();
              sprite_list = list_create();
              projectile_list = list_createee();
              int num = 1;
              for (int i = 0; i < 7; i++) {
                Sprite *orc = sprite_init((xpm_map_t) draw_orc_xpm, 50, 0 - (50 * i), 3, 3);
                Enemy *orc_enemy = (Enemy *) malloc(sizeof(Enemy));
                create_orc(orc_enemy, 50, 0 - (50 * i) - 4, num);
                num++;
                list_append(sprite_list, orc, orc_enemy);
              }
              for (int i = 0; i < 10; i++) {
                Sprite *skeleton = sprite_init((xpm_map_t) draw_skeleton_xpm, 100, 0 - (50 * i) - 2, 2, 2);
                Enemy *skeleton_enemy = (Enemy *) malloc(sizeof(Enemy));
                create_skeleton(skeleton_enemy, 100, 0 - (50 * i) - 2, num);
                num++;
                list_append(sprite_list, skeleton, skeleton_enemy);
              }
              for (int i = 0; i < 4; i++) {
                Sprite *golem = sprite_init((xpm_map_t) draw_golem_xpm, 150, 0 - (50 * i) - 1, 1, 1);
                Enemy *golem_enemy = (Enemy *) malloc(sizeof(Enemy));
                create_golem(golem_enemy, 150, 0 - (50 * i) - 1, num);
                num++;
                list_append(sprite_list, golem, golem_enemy);
              }
            }
            if ((mode_of_game == MAIN_MENU || mode_of_game == LEADERBOARD) && keyboard_scancode == 0x10) {
              list_destroy(sprite_list);
              list_destroyy(tower_list);
              list_destroyyy(projectile_list);
              mode_of_game = QUIT;
            }
            if (mode_of_game == MAIN_MENU && keyboard_scancode == 0x26) {
              mode_of_game = LEADERBOARD;
            }
            if (mode_of_game == MAIN_MENU && keyboard_scancode == 0x19) {
              mode_of_game = GAME;
            }
            if (mode_of_game == MAIN_MENU && keyboard_scancode == 0x18) {
              mode_of_game = OPTIONS;
            }

            if (mode_of_game == GAME && keyboard_scancode == 0x16) {
              if (coins >= 300) {
                if (selected == 0) {
                  if (select0 == 0) {
                    tsp = tower_list->head;
                    while (tsp->sprite->x != 220 || tsp->sprite->y != 80) {
                      tsp = tsp->next;
                    }
                    upgrade_tower(tsp->tower);
                  }
                }
                if (selected == 1) {
                  if (select1 == 0) {
                    tsp = tower_list->head;
                    while (tsp->sprite->x != 220 || tsp->sprite->y != 220) {
                      tsp = tsp->next;
                    }
                    upgrade_tower(tsp->tower);
                  }
                }
                if (selected == 2) {
                  if (select2 == 0) {
                    tsp = tower_list->head;
                    while (tsp->sprite->x != 220 || tsp->sprite->y != 360) {
                      tsp = tsp->next;
                    }
                    upgrade_tower(tsp->tower);
                  }
                }
                if (selected == 3) {
                  if (select3 == 0) {
                    tsp = tower_list->head;
                    while (tsp->sprite->x != 410 || tsp->sprite->y != 360) {
                      tsp = tsp->next;
                    }
                    upgrade_tower(tsp->tower);
                  }
                }
                if (selected == 4) {
                  if (select4 == 0) {
                    tsp = tower_list->head;
                    while (tsp->sprite->x != 505 || tsp->sprite->y != 290) {
                      tsp = tsp->next;
                    }
                    upgrade_tower(tsp->tower);
                  }
                }
                if (selected == 5) {
                  if (select5 == 0) {
                    tsp = tower_list->head;
                    while (tsp->sprite->x != 505 || tsp->sprite->y != 150) {
                      tsp = tsp->next;
                    }
                    upgrade_tower(tsp->tower);
                  }
                }
                coins -= 300;
              }
            }

            if (mode_of_game == GAME && keyboard_scancode == 0x32) {
              if (coins >= 150) {
                coins -= 150;
                if (selected == 0) {
                  if (select0 == 1) {
                    Sprite *towerr = sprite_init((xpm_map_t) draw_mage_tower, 220, 80, 0, 0);
                    Tower *tower = (Tower *) malloc(sizeof(Tower));
                    create_mage_tower(tower, 220, 80);
                    list_appendd(tower_list, towerr, tower);
                    select0 = 0;
                  }
                }
                if (selected == 1) {
                  if (select1 == 1) {
                    Sprite *towerr = sprite_init((xpm_map_t) draw_mage_tower, 220, 220, 0, 0);
                    Tower *tower = (Tower *) malloc(sizeof(Tower));
                    create_mage_tower(tower, 220, 220);
                    list_appendd(tower_list, towerr, tower);
                    select1 = 0;
                  }
                }
                if (selected == 2) {
                  if (select2 == 1) {
                    Sprite *towerr = sprite_init((xpm_map_t) draw_mage_tower, 220, 360, 0, 0);
                    Tower *tower = (Tower *) malloc(sizeof(Tower));
                    create_mage_tower(tower, 220, 360);
                    list_appendd(tower_list, towerr, tower);
                    select2 = 0;
                  }
                }
                if (selected == 3) {
                  if (select3 == 1) {
                    Sprite *towerr = sprite_init((xpm_map_t) draw_mage_tower, 410, 360, 0, 0);
                    Tower *tower = (Tower *) malloc(sizeof(Tower));
                    create_mage_tower(tower, 410, 360);
                    list_appendd(tower_list, towerr, tower);
                    select3 = 0;
                  }
                }
                if (selected == 4) {
                  if (select4 == 1) {
                    Sprite *towerr = sprite_init((xpm_map_t) draw_mage_tower, 505, 290, 0, 0);
                    Tower *tower = (Tower *) malloc(sizeof(Tower));
                    create_mage_tower(tower, 505, 290);
                    list_appendd(tower_list, towerr, tower);
                    select4 = 0;
                  }
                }
                if (selected == 5) {
                  if (select5 == 1) {
                    Sprite *towerr = sprite_init((xpm_map_t) draw_mage_tower, 505, 150, 0, 0);
                    Tower *tower = (Tower *) malloc(sizeof(Tower));
                    create_mage_tower(tower, 505, 150);
                    list_appendd(tower_list, towerr, tower);
                    select5 = 0;
                  }
                }
              }
            }
            if (mode_of_game == GAME && keyboard_scancode == 0x1E) {
              if (coins >= 50) {
                coins -= 50;
                if (selected == 0) {
                  if (select0 == 1) {
                    Sprite *towerr = sprite_init((xpm_map_t) draw_archer_tower, 220, 80, 0, 0);
                    Tower *tower = (Tower *) malloc(sizeof(Tower));
                    create_archer_tower(tower, 220, 80);
                    list_appendd(tower_list, towerr, tower);
                    select0 = 0;
                  }
                }
                if (selected == 1) {
                  if (select1 == 1) {
                    Sprite *towerr = sprite_init((xpm_map_t) draw_archer_tower, 220, 220, 0, 0);
                    Tower *tower = (Tower *) malloc(sizeof(Tower));
                    create_archer_tower(tower, 220, 220);
                    list_appendd(tower_list, towerr, tower);
                    select1 = 0;
                  }
                }
                if (selected == 2) {
                  if (select2 == 1) {
                    Sprite *towerr = sprite_init((xpm_map_t) draw_archer_tower, 220, 360, 0, 0);
                    Tower *tower = (Tower *) malloc(sizeof(Tower));
                    create_archer_tower(tower, 220, 360);
                    list_appendd(tower_list, towerr, tower);
                    select2 = 0;
                  }
                }
                if (selected == 3) {
                  if (select3 == 1) {
                    Sprite *towerr = sprite_init((xpm_map_t) draw_archer_tower, 410, 360, 0, 0);
                    Tower *tower = (Tower *) malloc(sizeof(Tower));
                    create_archer_tower(tower, 410, 360);
                    list_appendd(tower_list, towerr, tower);
                    select3 = 0;
                  }
                }
                if (selected == 4) {
                  if (select4 == 1) {
                    Sprite *towerr = sprite_init((xpm_map_t) draw_archer_tower, 505, 290, 0, 0);
                    Tower *tower = (Tower *) malloc(sizeof(Tower));
                    create_archer_tower(tower, 505, 290);
                    list_appendd(tower_list, towerr, tower);
                    select4 = 0;
                  }
                }
                if (selected == 5) {
                  if (select5 == 1) {
                    Sprite *towerr = sprite_init((xpm_map_t) draw_archer_tower, 505, 150, 0, 0);
                    Tower *tower = (Tower *) malloc(sizeof(Tower));
                    create_archer_tower(tower, 505, 150);
                    list_appendd(tower_list, towerr, tower);
                    select5 = 0;
                  }
                }
              }
            }

            if (mode_of_game == GAME && keyboard_scancode == 0x2E) {
              if (coins >= 100) {
                coins -= 100;
                if (selected == 0) {
                  if (select0 == 1) {
                    Sprite *towerr = sprite_init((xpm_map_t) draw_canon_tower, 220, 80, 0, 0);
                    Tower *tower = (Tower *) malloc(sizeof(Tower));
                    create_canon_tower(tower, 220, 80);
                    list_appendd(tower_list, towerr, tower);
                    select0 = 0;
                  }
                }
                if (selected == 1) {
                  if (select1 == 1) {
                    Sprite *towerr = sprite_init((xpm_map_t) draw_canon_tower, 220, 220, 0, 0);
                    Tower *tower = (Tower *) malloc(sizeof(Tower));
                    create_canon_tower(tower, 220, 220);
                    list_appendd(tower_list, towerr, tower);
                    select1 = 0;
                  }
                }
                if (selected == 2) {
                  if (select2 == 1) {
                    Sprite *towerr = sprite_init((xpm_map_t) draw_canon_tower, 220, 360, 0, 0);
                    Tower *tower = (Tower *) malloc(sizeof(Tower));
                    create_canon_tower(tower, 220, 360);
                    list_appendd(tower_list, towerr, tower);
                    select2 = 0;
                  }
                }
                if (selected == 3) {
                  if (select3 == 1) {
                    Sprite *towerr = sprite_init((xpm_map_t) draw_canon_tower, 410, 360, 0, 0);
                    Tower *tower = (Tower *) malloc(sizeof(Tower));
                    create_canon_tower(tower, 410, 360);
                    list_appendd(tower_list, towerr, tower);
                    select3 = 0;
                  }
                }
                if (selected == 4) {
                  if (select4 == 1) {
                    Sprite *towerr = sprite_init((xpm_map_t) draw_canon_tower, 505, 290, 0, 0);
                    Tower *tower = (Tower *) malloc(sizeof(Tower));
                    create_canon_tower(tower, 505, 290);
                    list_appendd(tower_list, towerr, tower);
                    select4 = 0;
                  }
                }
                if (selected == 5) {
                  if (select5 == 1) {
                    Sprite *towerr = sprite_init((xpm_map_t) draw_canon_tower, 505, 150, 0, 0);
                    Tower *tower = (Tower *) malloc(sizeof(Tower));
                    create_canon_tower(tower, 505, 150);
                    list_appendd(tower_list, towerr, tower);
                    select5 = 0;
                  }
                }
              }
            }
            if (mode_of_game == GAME && keyboard_scancode == 0x4D) {
              selected++;
              if (selected > 5) {
                selected = 0;
              }
            }

            if (mode_of_game == GAME && keyboard_scancode == 0x4B) {
              selected--;
              if (selected < 0) {
                selected = 5;
              }
            }
            if (mode_of_game == LEADERBOARD) {
              process_scancode(keyboard_scancode);
            }
          }
          if (msg.m_notify.interrupts & mouse_mask) {
            interrupt_handler_of_mouse();
            synchronization_of_mouse_bytes();
            if (mouse_bytes_index == 3) {
              mouse_bytes_index = 0;
              transform_mouse_bytes_to_packets();
              update_mouse_location();
              if (mode_of_game == MAIN_MENU) {
                memset(image_loader, 0, x_res * y_res * bytes_being_user_per_pixel);
                memset(drawer_buffer, 0xDDDDDD, x_res * y_res * bytes_being_user_per_pixel);

                clickLeaderboard(x, y);
                clickPlay(x, y);
                clickOptions(x, y);
                clickQuit(x, y, &q);
                if (q) {
                  list_destroy(sprite_list);
                  list_destroyy(tower_list);
                  list_destroyyy(projectile_list);
                  mode_of_game = QUIT;
                }
              }
              if (mode_of_game == GAME) {
                memset(image_loader, 0, x_res * y_res * bytes_being_user_per_pixel);
                memset(drawer_buffer, 0xDDDDDD, x_res * y_res * bytes_being_user_per_pixel);

                select_towers(x, y, &selected);
              }
            }
          }
          break;
        default:
          break;
      }
    }
  }
  if (unsubscription_of_mouse_interrupts() != 0) {
    return 1;
  }
  if (unsubscription_of_timer_interrupts() != 0) {
    return 1;
  }
  if (unsubscription_of_keyboard_interrupts() != 0) {
    return 1;
  }
  return 0;
}

int(proj_main_loop)(int argc, char *argv[]) {
  tower_list = list_createe();
  sprite_list = list_create();
  projectile_list = list_createee();

  int num = 1;
  for (int i = 0; i < 7; i++) {
    Sprite *orc = sprite_init((xpm_map_t) draw_orc_xpm, 50, 0 - (50 * i), 3, 3);
    Enemy *orc_enemy = (Enemy *) malloc(sizeof(Enemy));
    create_orc(orc_enemy, 50, 0 - (50 * i) - 4, num);
    num++;
    list_append(sprite_list, orc, orc_enemy);
  }
  for (int i = 0; i < 10; i++) {
    Sprite *skeleton = sprite_init((xpm_map_t) draw_skeleton_xpm, 100, 0 - (50 * i) - 2, 2, 2);
    Enemy *skeleton_enemy = (Enemy *) malloc(sizeof(Enemy));
    create_skeleton(skeleton_enemy, 100, 0 - (50 * i) - 2, num);
    num++;
    list_append(sprite_list, skeleton, skeleton_enemy);
  }
  for (int i = 0; i < 4; i++) {
    Sprite *golem = sprite_init((xpm_map_t) draw_golem_xpm, 150, 0 - (50 * i) - 1, 1, 1);
    Enemy *golem_enemy = (Enemy *) malloc(sizeof(Enemy));
    create_golem(golem_enemy, 150, 0 - (50 * i) - 1, num);
    num++;
    list_append(sprite_list, golem, golem_enemy);
  }
  if (set_video_mem(0x115)) {
    return 1;
  }

  if (set_vbe_mode(0x115)) {
    return 1;
  }
  load_sprites_to_menu();
  allocate_image_loader();
  drawer_buffer = (uint8_t *) malloc(x_res * y_res * bytes_being_user_per_pixel);
  memset(drawer_buffer, 0xFFFFFF, x_res * y_res * bytes_being_user_per_pixel);

  if (game_loop() != 0) {
    return 1;
  }
  if (vg_exit() != 0) {
    return 1;
  }
  unload_sprites_of_menu();
  free(image_loader);
  free(drawer_buffer);
  return 0;
}
