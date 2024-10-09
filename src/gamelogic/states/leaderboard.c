#include "gamelogic/states/leaderboard.h"
#include "sprites/sprite.h"

extern struct packet mouse_packet;
extern int mode_of_game;
extern bool game_over;
extern int x_res;
extern int y_res;

int draw_leaderboard() {
  draw_sprite(leaderboard_title);
  draw_sprite(highscore);
  draw_sprite(highscore2);
  draw_letter('E', 250, 250);
  draw_letter('N', 270, 250);
  draw_letter('T', 290, 250);
  draw_letter('E', 310, 250);
  draw_letter('R', 330, 250);
  draw_letter(' ', 350, 250);
  draw_letter('Y', 370, 250);
  draw_letter('O', 390, 250);
  draw_letter('U', 410, 250);
  draw_letter('R', 430, 250);
  draw_letter(' ', 450, 250);
  draw_letter('N', 470, 250);
  draw_letter('A', 490, 250);
  draw_letter('M', 510, 250);
  draw_letter('E', 530, 250);

  draw_player_name();
  return 0;
}
