#include "game.h"
#include "macros/game_modes.h"
#include "sprites/sprite.h"
#include <stdbool.h>

extern Sprite *chest;
extern Sprite *archer_tower;
extern Sprite *canon_tower;
extern Sprite *mage_tower;
extern Sprite *arena;
extern Sprite *coin;
extern Sprite *heart;
extern Sprite *medal;
extern Sprite *select_position_square;
extern Sprite *position_square;

extern struct packet mouse_packet;
extern int mode_of_game;
extern bool game_over;
extern uint32_t *image_loader;
extern unsigned int bytes_being_user_per_pixel;
extern uint16_t x_res;
extern uint16_t y_res;
extern int x;
extern int y;

int draw_game() {
  memset(image_loader, 0, x_res * y_res * bytes_being_user_per_pixel);
  draw_sprite(arena);
  draw_sprite(chest);
  draw_sprite(coin);
  draw_sprite(medal);
  draw_sprite(heart);
  draw_sprite(select_position_square);
  draw_sprite(position_square1);
  draw_sprite(position_square3);
  draw_sprite(position_square5);
  draw_sprite(position_square7);
  draw_sprite(position_square9);
  draw_sprite(position_square11);

  return 0;
}

void(display_mouse)() {
  if (mode_of_game == MAIN_MENU || mode_of_game == GAME) {
    if (x > 150 && x < 350) {
      if ((y > 300 && y < 400) || (y > 420 && y < 520)) {
        sprite_set_x(mouse, x);
        sprite_set_y(mouse, y);
        draw_sprite(mouse);
      }
      else {
        sprite_set_x(mouse, x);
        sprite_set_y(mouse, y);
        draw_sprite(mouse);
      }
    }
    else if (x > 450 && x < 650) {
      if ((y > 300 && y < 400) || (y > 420 && y < 520)) {
        sprite_set_x(mouse, x);
        sprite_set_y(mouse, y);
        draw_sprite(mouse);
      }
      else {
        sprite_set_x(mouse, x);
        sprite_set_y(mouse, y);
        draw_sprite(mouse);
      }
    }
    else {
      sprite_set_x(mouse, x);
      sprite_set_y(mouse, y);
      draw_sprite(mouse);
    }
  }
}

void select_towers(uint16_t x, uint16_t y, int *selected) {
  if (x > 220 && x < 270 && y > 80 && y < 130) {
    *selected = 0;
  }
  else if (x > 220 && x < 270 && y > 220 && y < 270) {
    *selected = 1;
  }
  else if (x > 220 && x < 270 && y > 360 && y < 410) {
    *selected = 2;
  }
  else if (x > 410 && x < 460 && y > 360 && y < 410) {
    *selected = 3;
  }
  else if (x > 505 && x < 555 && y > 290 && y < 340) {
    *selected = 4;
  }
  else if (x > 505 && x < 555 && y > 150 && y < 200) {
    *selected = 5;
  }
}

void draw_selected(int *selected) {
  if (*selected == 0) {
    select_position_square = sprite_init((xpm_map_t) draw_select_position_square, 220, 80, 0, 0);
    draw_sprite(select_position_square);
  }
  else if (*selected == 1) {
    select_position_square = sprite_init((xpm_map_t) draw_select_position_square, 220, 220, 0, 0);
    draw_sprite(select_position_square);
  }
  else if (*selected == 2) {
    select_position_square = sprite_init((xpm_map_t) draw_select_position_square, 220, 360, 0, 0);
    draw_sprite(select_position_square);
  }
  else if (*selected == 3) {
    select_position_square = sprite_init((xpm_map_t) draw_select_position_square, 410, 360, 0, 0);
    draw_sprite(select_position_square);
  }
  else if (*selected == 4) {
    select_position_square = sprite_init((xpm_map_t) draw_select_position_square, 505, 290, 0, 0);
    draw_sprite(select_position_square);
  }
  else if (*selected == 5) {
    select_position_square = sprite_init((xpm_map_t) draw_select_position_square, 505, 150, 0, 0);
    draw_sprite(select_position_square);
  }
}
