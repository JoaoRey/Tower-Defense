#include "menu.h"
#include "devices/graphic/graphics.h"
#include "devices/keyboard/kbd.h"
#include "devices/mouse/mouse.h"
#include "gamelogic/utils/position.h"
#include "macros/game_modes.h"
#include "sprites/sprite.h"
#include <lcom/lcf.h>
#include <lcom/xpm.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

extern Sprite *arena;
extern Sprite *mouse;
extern Sprite *title;
extern Sprite *play;
extern Sprite *leaderboard;
extern Sprite *quit;
extern Sprite *settings;
extern Sprite *play_selected;
extern Sprite *leaderboard_selected;
extern Sprite *settings_selected;
extern Sprite *quit_selected;

extern uint8_t *drawer_buffer;
extern uint32_t *image_loader;
extern unsigned int bytes_being_user_per_pixel;
extern struct packet mouse_packet_structure;
extern int mode_of_game;
extern bool game_over;
extern uint16_t x_res;
extern uint16_t y_res;

int xscreen = 0;
int yscreen = 0;
bool isPlay = false;
bool isQuit = false;
bool isOptions = false;
bool isLeaderboard = false;

int draw_menu(uint16_t x, uint16_t y) {
  memset(image_loader, 0, x_res * y_res * bytes_being_user_per_pixel);
  draw_sprite(title);

  if (x > 300 && x < 480 && y > 300 && y < 380) {
    draw_sprite(play_selected);
  }
  else {
    draw_sprite(play);
  }
  if (x > 300 && x < 480 && y > 455 && y < 535) {
    draw_sprite(leaderboard_selected);
  }
  else {
    draw_sprite(leaderboard);
  }
  if (x > 60 && x < 240 && y > 455 && y < 535) {
    draw_sprite(settings_selected);
  }
  else {
    draw_sprite(settings);
  }
  if (x > 545 && x < 725 && y > 455 && y < 535) {
    draw_sprite(quit_selected);
  }
  else {
    draw_sprite(quit);
  }
  return 0;
}


int clickPlay(uint16_t x, uint16_t y) {
  if (x > 300 && x < 480 && y > 300 && y < 380) {
    if (!isPlay)
      if (mouse_packet_structure.lb)
        isPlay = true;
    if (isPlay)
      if (!mouse_packet_structure.lb) {
        
        mode_of_game = GAME;

        isPlay = false;
      }
  }
  else {
    isPlay = false;
  }
  return 0;
}

int clickLeaderboard(uint16_t x, uint16_t y) {
  if (x > 300 && x < 480 && y > 455 && y < 535) {
    if (!isLeaderboard)
      if (mouse_packet_structure.lb)
        isLeaderboard = true;
    if (isLeaderboard)
      if (!mouse_packet_structure.lb) {
        mode_of_game = LEADERBOARD;

        isLeaderboard = false;
      }
  }
  else {
    isLeaderboard = false;
  }
  return 0;
}

int clickQuit(uint16_t x, uint16_t y, bool *quit) {
  if (x > 545 && x < 725 && y > 455 && y < 535) {
    if (!isQuit && mouse_packet_structure.lb) {
      isQuit = true;
    }
    if (isQuit && !mouse_packet_structure.lb) {

      *quit = TRUE;
      isQuit = false;
    }
  }
  else {
    isQuit = false;
  }
  return 0;
}

int clickOptions(uint16_t x, uint16_t y) {
  if(x > 60 && x < 240 && y > 455 && y < 535){
    if (!isOptions)
      if (mouse_packet_structure.lb)
        isOptions = true;
    if (isOptions)
      if (!mouse_packet_structure.lb) {
        isOptions = false;
        mode_of_game = OPTIONS;

        isOptions = false;
      }
  }
  else {
    isOptions = false;
  }
  return 0;
}
