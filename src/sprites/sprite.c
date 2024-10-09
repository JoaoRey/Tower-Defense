#include "sprite.h"
#include "devices/keyboard/kbd.h"
#include "devices/rtc/rtc.h"
#include <lcom/lcf.h>
#include <lcom/xpm.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

extern uint16_t x_res;
extern uint16_t y_res;
extern uint8_t rtc_time_data[6];
extern uint8_t keyboard_scancode;
extern char player_name[10];
extern int name_length;
extern int score;

#define MAX_LEADERBOARD_ENTRIES 10
#define NAME_LENGTH 10
#define TOP_ENTRIES 6

LeaderboardEntry leaderboard_entries[MAX_LEADERBOARD_ENTRIES];
int leaderboard_count = 0;

void sort_leaderboard() {
  for (int i = 0; i < leaderboard_count - 1; i++) {
    for (int j = i + 1; j < leaderboard_count; j++) {
      if (leaderboard_entries[j].score > leaderboard_entries[i].score) {
        LeaderboardEntry temp = leaderboard_entries[i];
        leaderboard_entries[i] = leaderboard_entries[j];
        leaderboard_entries[j] = temp;
      }
    }
  }
}

void add_to_leaderboard(const char *name, int score) {
  if (leaderboard_count < MAX_LEADERBOARD_ENTRIES) {
    strcpy(leaderboard_entries[leaderboard_count].name, name);
    leaderboard_entries[leaderboard_count].score = score;
    leaderboard_count++;
  }
  else {
    int min_index = 0;
    for (int i = 1; i < MAX_LEADERBOARD_ENTRIES; i++) {
      if (leaderboard_entries[i].score < leaderboard_entries[min_index].score) {
        min_index = i;
      }
    }
    if (score > leaderboard_entries[min_index].score) {
      strcpy(leaderboard_entries[min_index].name, name);
      leaderboard_entries[min_index].score = score;
    }
  }
}

void save_player_data() {
  add_to_leaderboard(player_name, score);

  sort_leaderboard();

  FILE *file = fopen("/home/lcom/labs/g1/proj/src/sprites/leaderboard.txt", "w");
  if (file == NULL) {
    printf("Error opening file!\n");
    return;
  }
  int entries_to_save = leaderboard_count < TOP_ENTRIES ? leaderboard_count : TOP_ENTRIES;
  for (int i = 0; i < entries_to_save; i++) {
    fprintf(file, "%s %d\n", leaderboard_entries[i].name, leaderboard_entries[i].score);
  }
  fclose(file);
}

void load_leaderboard() {
  FILE *file = fopen("/home/lcom/labs/g1/proj/src/sprites/leaderboard.txt", "r");
  if (file == NULL) {
    printf("Error opening file!\n");

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
      printf("Current working directory: %s\n", cwd);
    }
    else {
      perror("getcwd() error");
    }
    return;
  }

  leaderboard_count = 0;
  while (fscanf(file, "%s %d", leaderboard_entries[leaderboard_count].name, &leaderboard_entries[leaderboard_count].score) != EOF) {
    leaderboard_count++;
    if (leaderboard_count >= MAX_LEADERBOARD_ENTRIES) {
      break;
    }
  }
  fclose(file);

  sort_leaderboard();
}

void display_leaderboard() {
  int x = 300;
  int y = 350;
  draw_sprite(leaderboard_title);
  int entries_to_display = leaderboard_count < TOP_ENTRIES ? leaderboard_count : TOP_ENTRIES;
  for (int i = 0; i < entries_to_display; i++) {
    for (int j = 0; j < NAME_LENGTH && leaderboard_entries[i].name[j] != '\0'; j++) {
      draw_letter(leaderboard_entries[i].name[j], x + j * 20, y);
    }

    int score = leaderboard_entries[i].score;
    int digit_x = x + NAME_LENGTH * 20 + 20;
    int digits[5];
    int digit_count = 0;
    do {
      digits[digit_count++] = score % 10;
      score /= 10;
    } while (score > 0);
    for (int j = digit_count - 1; j >= 0; j--) {
      draw_digit(digits[j], digit_x, y);
      digit_x += 20;
    }
    y += 30;
  }
}

Sprite *sprite_init(xpm_map_t sprite, int x, int y, int xspeed, int yspeed) {
  Sprite *new_sprite = (Sprite *) malloc(sizeof(Sprite));
  if (new_sprite == NULL) {
    return NULL;
  }
  xpm_image_t image;
  new_sprite->colors = (uint32_t *) xpm_load(sprite, XPM_8_8_8_8, &image);
  new_sprite->width = image.width;
  new_sprite->height = image.height;
  new_sprite->x = x;
  new_sprite->y = y;
  new_sprite->xspeed = xspeed;
  new_sprite->yspeed = yspeed;
  return new_sprite;
}

int draw_sprite(Sprite *sprite) {
  if (sprite == NULL) {
    return 1;
  }
  for (int i = 0; i < sprite->height; i++) {
    for (int j = 0; j < sprite->width; j++) {
      if (sprite->colors[i * sprite->width + j] == TRANSPARENCY_COLOR) {
        continue;
      }
      if (draw_pixel(sprite->x + j, sprite->y + i, sprite->colors[i * sprite->width + j])) {
        return 1;
      }
    }
  }
  return 0;
}
char scancode_to_char(uint8_t keyboard_scancode) {
  switch (keyboard_scancode) {
    case 0x1E: return 'A';
    case 0x30: return 'B';
    case 0x2E: return 'C';
    case 0x20: return 'D';
    case 0x12: return 'E';
    case 0x21: return 'F';
    case 0x22: return 'G';
    case 0x23: return 'H';
    case 0x17: return 'I';
    case 0x24: return 'J';
    case 0x25: return 'K';
    case 0x26: return 'L';
    case 0x32: return 'M';
    case 0x31: return 'N';
    case 0x18: return 'O';
    case 0x19: return 'P';
    case 0x10: return 'Q';
    case 0x13: return 'R';
    case 0x1F: return 'S';
    case 0x14: return 'T';
    case 0x16: return 'U';
    case 0x2F: return 'V';
    case 0x11: return 'W';
    case 0x2D: return 'X';
    case 0x15: return 'Y';
    case 0x2C: return 'Z';
    default: return '\0';
  }
}

void process_scancode(uint8_t keyboard_scancode) {
  char letter = scancode_to_char(keyboard_scancode);
  if (letter != '\0' && name_length < 10) {
    player_name[name_length++] = letter;
    player_name[name_length] = '\0';
  }
}

void draw_letter(char letter, int x, int y) {
  Sprite *letter_sprite = NULL;

  switch (letter) {
    case 'A':
      letter_sprite = sprite_init((xpm_map_t) draw_a_xpm, x, y, 0, 0);
      break;
    case 'B':
      letter_sprite = sprite_init((xpm_map_t) draw_b_xpm, x, y, 0, 0);
      break;
    case 'C':
      letter_sprite = sprite_init((xpm_map_t) draw_c_xpm, x, y, 0, 0);
      break;
    case 'D':
      letter_sprite = sprite_init((xpm_map_t) draw_d_xpm, x, y, 0, 0);
      break;
    case 'E':
      letter_sprite = sprite_init((xpm_map_t) draw_e_xpm, x, y, 0, 0);
      break;
    case 'F':
      letter_sprite = sprite_init((xpm_map_t) draw_f_xpm, x, y, 0, 0);
      break;
    case 'G':
      letter_sprite = sprite_init((xpm_map_t) draw_g_xpm, x, y, 0, 0);
      break;
    case 'H':
      letter_sprite = sprite_init((xpm_map_t) draw_h_xpm, x, y, 0, 0);
      break;
    case 'I':
      letter_sprite = sprite_init((xpm_map_t) draw_i_xpm, x, y, 0, 0);
      break;
    case 'J':
      letter_sprite = sprite_init((xpm_map_t) draw_j_xpm, x, y, 0, 0);
      break;
    case 'K':
      letter_sprite = sprite_init((xpm_map_t) draw_k_xpm, x, y, 0, 0);
      break;
    case 'L':
      letter_sprite = sprite_init((xpm_map_t) draw_l_xpm, x, y, 0, 0);
      break;
    case 'M':
      letter_sprite = sprite_init((xpm_map_t) draw_m_xpm, x, y, 0, 0);
      break;
    case 'N':
      letter_sprite = sprite_init((xpm_map_t) draw_n_xpm, x, y, 0, 0);
      break;
    case 'O':
      letter_sprite = sprite_init((xpm_map_t) draw_o_xpm, x, y, 0, 0);
      break;
    case 'P':
      letter_sprite = sprite_init((xpm_map_t) draw_p_xpm, x, y, 0, 0);
      break;
    case 'Q':
      letter_sprite = sprite_init((xpm_map_t) draw_q_xpm, x, y, 0, 0);
      break;
    case 'R':
      letter_sprite = sprite_init((xpm_map_t) draw_r_xpm, x, y, 0, 0);
      break;
    case 'S':
      letter_sprite = sprite_init((xpm_map_t) draw_s_xpm, x, y, 0, 0);
      break;
    case 'T':
      letter_sprite = sprite_init((xpm_map_t) draw_t_xpm, x, y, 0, 0);
      break;
    case 'U':
      letter_sprite = sprite_init((xpm_map_t) draw_u_xpm, x, y, 0, 0);
      break;
    case 'V':
      letter_sprite = sprite_init((xpm_map_t) draw_v_xpm, x, y, 0, 0);
      break;
    case 'W':
      letter_sprite = sprite_init((xpm_map_t) draw_w_xpm, x, y, 0, 0);
      break;
    case 'X':
      letter_sprite = sprite_init((xpm_map_t) draw_x_xpm, x, y, 0, 0);
      break;
    case 'Y':
      letter_sprite = sprite_init((xpm_map_t) draw_y_xpm, x, y, 0, 0);
      break;
    case 'Z':
      letter_sprite = sprite_init((xpm_map_t) draw_z_xpm, x, y, 0, 0);
      break;
    default:
      return;
  }

  if (letter_sprite != NULL) {
    draw_sprite(letter_sprite);
    destroy_sprite(letter_sprite);
  }
}

void draw_player_name() {
  int x = 300;
  int y = 280;

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

  draw_letter('P', 250, 310);
  draw_letter('R', 270, 310);
  draw_letter('E', 290, 310);
  draw_letter('S', 310, 310);
  draw_letter('S', 330, 310);
  draw_letter(' ', 350, 310);
  draw_letter('E', 370, 310);
  draw_letter('N', 390, 310);
  draw_letter('T', 410, 310);
  draw_letter('E', 430, 310);
  draw_letter('R', 450, 310);
  draw_letter(' ', 470, 310);
  draw_letter('T', 490, 310);
  draw_letter('O', 510, 310);
  draw_letter(' ', 530, 310);
  draw_letter('S', 550, 310);
  draw_letter('A', 570, 310);
  draw_letter('V', 590, 310);
  draw_letter('E', 610, 310);

  for (int i = 0; i < name_length; i++) {
    draw_letter(player_name[i], x, y);
    x += 20;
  }
}

void draw_digit(int digit, int x, int y) {
  Sprite *digit_sprite = NULL;

  switch (digit) {
    case 0:
      digit_sprite = sprite_init((xpm_map_t) draw_zero_xpm, x, y, 0, 0);
      break;
    case 1:
      digit_sprite = sprite_init((xpm_map_t) draw_one_xpm, x, y, 0, 0);
      break;
    case 2:
      digit_sprite = sprite_init((xpm_map_t) draw_two_xpm, x, y, 0, 0);
      break;
    case 3:
      digit_sprite = sprite_init((xpm_map_t) draw_three_xpm, x, y, 0, 0);
      break;
    case 4:
      digit_sprite = sprite_init((xpm_map_t) draw_four_xpm, x, y, 0, 0);
      break;
    case 5:
      digit_sprite = sprite_init((xpm_map_t) draw_five_xpm, x, y, 0, 0);
      break;
    case 6:
      digit_sprite = sprite_init((xpm_map_t) draw_six_xpm, x, y, 0, 0);
      break;
    case 7:
      digit_sprite = sprite_init((xpm_map_t) draw_seven_xpm, x, y, 0, 0);
      break;
    case 8:
      digit_sprite = sprite_init((xpm_map_t) draw_eight_xpm, x, y, 0, 0);
      break;
    case 9:
      digit_sprite = sprite_init((xpm_map_t) draw_nine_xpm, x, y, 0, 0);
      break;
  }

  if (digit_sprite != NULL) {
    draw_sprite(digit_sprite);
    destroy_sprite(digit_sprite);
  }
}

void draw_rtc() {

  initialize_rtc();

  draw_digit(rtc_time_data[3] / 10, 0, 0);
  draw_digit(rtc_time_data[3] % 10, 20, 0);

  draw_digit(rtc_time_data[4] / 10, 50, 0);
  draw_digit(rtc_time_data[4] % 10, 70, 0);

  draw_digit(rtc_time_data[5] / 10, 100, 0);
  draw_digit(rtc_time_data[5] % 10, 120, 0);
}
int move_sprite_x(Sprite *sprite) {
  if (sprite == NULL) {
    return 1;
  }
  sprite->x += sprite->yspeed;
  return 0;
}

int move_sprite_neg_x(Sprite *sprite) {
  if (sprite == NULL) {
    return 1;
  }
  sprite->x -= sprite->yspeed;
  return 0;
}

int move_sprite_y(Sprite *sprite) {
  if (sprite == NULL) {
    return 1;
  }
  sprite->y += sprite->yspeed;
  return 0;
}

int move_sprite_neg_y(Sprite *sprite) {
  if (sprite == NULL) {
    return 1;
  }
  sprite->y -= sprite->yspeed;
  return 0;
}
int move_sprite_x_p(Sprite *sprite) {
  if (sprite == NULL) {
    return 1;
  }
  sprite->x += 15;
  return 0;
}

int move_sprite_neg_x_p(Sprite *sprite) {
  if (sprite == NULL) {
    return 1;
  }
  sprite->x -= 15;
  return 0;
}

int move_sprite_y_p(Sprite *sprite) {
  if (sprite == NULL) {
    return 1;
  }
  sprite->y += 15;
  return 0;
}

int move_sprite_neg_y_p(Sprite *sprite) {
  if (sprite == NULL) {
    return 1;
  }
  sprite->y -= 15;
  return 0;
}
void destroy_sprite(Sprite *sprite) {
  if (sprite == NULL) {
    return;
  }
  else if (sprite->colors) {
    free(sprite->colors);
  }

  free(sprite);
  sprite = NULL;
}

void sprite_set_x(Sprite *sprite, int x) {
  sprite->x = x;
}

void sprite_set_y(Sprite *sprite, int y) {
  sprite->y = y;
}

void load_sprites_to_menu() {
  mouse = sprite_init((xpm_map_t) draw_mouse, 5, 5, 0, 0);
  title = sprite_init((xpm_map_t) draw_title_xpm, 0, 0, 0, 0);
  arena = sprite_init((xpm_map_t) draw_arena, 0, -140, 0, 0);
  title = sprite_init((xpm_map_t) draw_title_xpm, x_res / 2 - 636 / 2, -165, 0, 0);
  play_selected = sprite_init((xpm_map_t) draw_play_selected_xpm, x_res / 2 - 200 / 2, y_res / 2 - 121 / 2 + 50, 0, 0);
  play = sprite_init((xpm_map_t) draw_play_button_xpm, x_res / 2 - 200 / 2, y_res / 2 - 121 / 2 + 50, 0, 0);
  leaderboard_selected = sprite_init((xpm_map_t) draw_leaderboard_selected_xpm, x_res / 2 - 200 / 2, y_res / 2 - 121 / 2 + 200, 0, 0);
  leaderboard = sprite_init((xpm_map_t) draw_leaderboard_button_xpm, x_res / 2 - 200 / 2, y_res / 2 - 121 / 2 + 200, 0, 0);
  settings_selected = sprite_init((xpm_map_t) draw_options_selected_xpm, x_res / 2 - 200 / 2 - 242, y_res / 2 - 121 / 2 + 200, 0, 0);
  settings = sprite_init((xpm_map_t) draw_options_xpm, x_res / 2 - 200 / 2 - 242, y_res / 2 - 121 / 2 + 200, 0, 0);
  quit_selected = sprite_init((xpm_map_t) draw_quit_selected_xpm, x_res / 2 - 200 / 2 + 242, y_res / 2 - 121 / 2 + 200, 0, 0);
  quit = sprite_init((xpm_map_t) draw_quit_button_xpm, x_res / 2 - 200 / 2 + 242, y_res / 2 - 121 / 2 + 200, 0, 0);
  chest = sprite_init((xpm_map_t) draw_chest, 730, 190, 0, 0);
  archer_tower = sprite_init((xpm_map_t) draw_archer_tower, 300, 300, 0, 0);
  highscore = sprite_init((xpm_map_t) draw_highscore_xpm, x_res / 2 - 300, y_res / 2, 0, 0);
  leaderboard_title = sprite_init((xpm_map_t) draw_leaderboard_title, x_res / 2 - 200, 0, 0, 0);
  highscore2 = sprite_init((xpm_map_t) draw_highscore_xpm, x_res / 2 - 300, y_res / 2 + 100, 0, 0);
  coin = sprite_init((xpm_map_t) draw_coin_xpm, x_res / 2 + 50, 10, 0, 0);
  heart = sprite_init((xpm_map_t) draw_heart_xpm, x_res / 2 - 50, 10, 0, 0);
  medal = sprite_init((xpm_map_t) draw_medal_xpm, x_res / 2 + 150, 10, 0, 0);
  select_position_square = sprite_init((xpm_map_t) draw_select_position_square, 220, 10, 0, 0);
  position_square1 = sprite_init((xpm_map_t) draw_position_square, 220, 80, 0, 0);
  position_square3 = sprite_init((xpm_map_t) draw_position_square, 220, 220, 0, 0);
  position_square5 = sprite_init((xpm_map_t) draw_position_square, 220, 360, 0, 0);
  position_square7 = sprite_init((xpm_map_t) draw_position_square, 410, 360, 0, 0);
  position_square9 = sprite_init((xpm_map_t) draw_position_square, 505, 290, 0, 0);
  position_square11 = sprite_init((xpm_map_t) draw_position_square, 505, 150, 0, 0);
  controls = sprite_init((xpm_map_t) draw_controls_xpm, 0, 0, 0, 0);
}

void unload_sprites_of_menu() {
  destroy_sprite(title);
  destroy_sprite(arena);
  destroy_sprite(play);
  destroy_sprite(leaderboard);
  destroy_sprite(quit);
  destroy_sprite(settings);
  destroy_sprite(play_selected);
  destroy_sprite(leaderboard_selected);
  destroy_sprite(quit_selected);
  destroy_sprite(settings_selected);
  destroy_sprite(archer_tower);
  destroy_sprite(canon_tower);
  destroy_sprite(mage_tower);
  destroy_sprite(chest);
  destroy_sprite(mouse);
  destroy_sprite(highscore);
  destroy_sprite(leaderboard_title);
  destroy_sprite(coin);
  destroy_sprite(medal);
  destroy_sprite(heart);
  destroy_sprite(select_position_square);
  destroy_sprite(position_square1);
  destroy_sprite(position_square3);
  destroy_sprite(position_square5);
  destroy_sprite(position_square7);
  destroy_sprite(position_square9);
  destroy_sprite(position_square11);
}

void draw_options() {
  draw_sprite(controls);
}
