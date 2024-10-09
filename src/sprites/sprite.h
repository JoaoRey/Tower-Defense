#ifndef _SPRITES_H_
#define _SPRITES_H_

#include "devices/graphic/graphics.h"
#include "images/arena/archer_tower.xpm"
#include "images/arena/arena.xpm"
#include "images/arena/arrow.xpm"
#include "images/arena/canon_ball.xpm"
#include "images/arena/canon_tower.xpm"
#include "images/arena/chest.xpm"
#include "images/arena/coin.xpm"
#include "images/arena/fireball.xpm"
#include "images/arena/heart.xpm"
#include "images/controls/controls.xpm"
#include "images/arena/mage_tower.xpm"
#include "images/arena/medal.xpm"
#include "images/arena/position_square.xpm"
#include "images/arena/select_position_square.xpm"
#include "images/enemies/golem.xpm"
#include "images/enemies/orc.xpm"
#include "images/enemies/skeleton.xpm"
#include "images/leaderboard/highscore.xpm"
#include "images/leaderboard/leaderboard_title.xpm"
#include "images/letters/a.xpm"
#include "images/letters/b.xpm"
#include "images/letters/c.xpm"
#include "images/letters/d.xpm"
#include "images/letters/e.xpm"
#include "images/letters/f.xpm"
#include "images/letters/g.xpm"
#include "images/letters/h.xpm"
#include "images/letters/i.xpm"
#include "images/letters/j.xpm"
#include "images/letters/k.xpm"
#include "images/letters/l.xpm"
#include "images/letters/m.xpm"
#include "images/letters/n.xpm"
#include "images/letters/o.xpm"
#include "images/letters/p.xpm"
#include "images/letters/q.xpm"
#include "images/letters/r.xpm"
#include "images/letters/s.xpm"
#include "images/letters/t.xpm"
#include "images/letters/u.xpm"
#include "images/letters/v.xpm"
#include "images/letters/w.xpm"
#include "images/letters/x.xpm"
#include "images/letters/y.xpm"
#include "images/letters/z.xpm"
#include "images/main_menu/leaderboard_button.xpm"
#include "images/main_menu/leaderboard_selected.xpm"
#include "images/main_menu/mouse_cursor.xpm"
#include "images/main_menu/options_button.xpm"
#include "images/main_menu/options_selected.xpm"
#include "images/main_menu/play_button.xpm"
#include "images/main_menu/play_selected.xpm"
#include "images/main_menu/quit_button.xpm"
#include "images/main_menu/quit_selected.xpm"
#include "images/main_menu/title.xpm"
#include "images/numbers/eight.xpm"
#include "images/numbers/five.xpm"
#include "images/numbers/four.xpm"
#include "images/numbers/nine.xpm"
#include "images/numbers/one.xpm"
#include "images/numbers/seven.xpm"
#include "images/numbers/six.xpm"
#include "images/numbers/three.xpm"
#include "images/numbers/two.xpm"
#include "images/numbers/zero.xpm"
#include <lcom/lcf.h>
#include <lcom/xpm.h>

#define NAME_LENGTH 10
#define MAX_LEADERBOARD_ENTRIES 10

/**
 * @brief Structure representing a sprite.
 */
typedef struct {
    uint32_t *colors; /**< @brief Pointer to the sprite's color data */
    int width;        /**< @brief Width of the sprite */
    int height;       /**< @brief Height of the sprite */
    int x;            /**< @brief Current x-coordinate of the sprite */
    int y;            /**< @brief Current y-coordinate of the sprite */
    int xspeed;       /**< @brief Speed of the sprite along the x-axis */
    int yspeed;       /**< @brief Speed of the sprite along the y-axis */
} Sprite;

/**
 * @brief Structure representing a leaderboard entry.
 */
typedef struct {
    char name[NAME_LENGTH]; /**< @brief Name of the player */
    int score;              /**< @brief Score of the player */
} LeaderboardEntry;

Sprite *leaderboard_title;
Sprite *highscore;
Sprite *controls;
Sprite *highscore2;
Sprite *canon_ball;
Sprite *fire_ball;
Sprite *arrow;
Sprite *archer_tower;
Sprite *mage_tower;
Sprite *canon_tower;
Sprite *play_selected;
Sprite *leaderboard_selected;
Sprite *settings_selected;
Sprite *quit_selected;
Sprite *mouse;
Sprite *title;
Sprite *arena;
Sprite *play;
Sprite *leaderboard;
Sprite *quit;
Sprite *settings;
Sprite *chest;
Sprite *coin;
Sprite *heart;
Sprite *medal;
Sprite *select_position_square;
Sprite *position_square1;
Sprite *position_square3;
Sprite *position_square5;
Sprite *position_square7;
Sprite *position_square9;
Sprite *position_square11;

/**
 * @brief Initializes a sprite with given properties.
 * 
 * @param sprite The XPM map representing the sprite
 * @param x Initial x-coordinate of the sprite
 * @param y Initial y-coordinate of the sprite
 * @param xspeed Speed of the sprite along the x-axis
 * @param yspeed Speed of the sprite along the y-axis
 * @return A pointer to the created sprite
 */
Sprite* sprite_init(xpm_map_t sprite, int x, int y, int xspeed, int yspeed);

/**
 * @brief Draws a sprite on the screen.
 * 
 * @param sprite Pointer to the sprite to be drawn
 * @return 0 on success, non-zero otherwise
 */
int draw_sprite(Sprite *sprite);

/**
 * @brief Destroys a sprite, freeing its resources.
 * 
 * @param sprite Pointer to the sprite to be destroyed
 */
void destroy_sprite(Sprite *sprite);

/**
 * @brief Sets the x-coordinate of a sprite.
 * 
 * @param sprite Pointer to the sprite
 * @param x New x-coordinate
 */
void sprite_set_x(Sprite* sprite, int x);

/**
 * @brief Sets the y-coordinate of a sprite.
 * 
 * @param sprite Pointer to the sprite
 * @param y New y-coordinate
 */
void sprite_set_y(Sprite* sprite, int y);

/**
 * @brief Adds a player to the leaderboard.
 * 
 * @param name Name of the player
 * @param score Score of the player
 */
void add_to_leaderboard(const char *name, int score);

/**
 * @brief Saves the current player data to the leaderboard.
 */
void save_player_data();

/**
 * @brief Loads the leaderboard from a file.
 */
void load_leaderboard();

/**
 * @brief Displays the leaderboard on the screen.
 */
void display_leaderboard();

/**
 * @brief Draws a letter on the screen.
 * 
 * @param letter The letter to draw
 * @param x The x-coordinate where the letter will be drawn
 * @param y The y-coordinate where the letter will be drawn
 */
void draw_letter(char letter, int x, int y);

/**
 * @brief Draws the player's name on the screen.
 */
void draw_player_name();

/**
 * @brief Draws a digit on the screen.
 * 
 * @param digit The digit to draw
 * @param x The x-coordinate where the digit will be drawn
 * @param y The y-coordinate where the digit will be drawn
 */
void draw_digit(int digit, int x, int y);

/**
 * @brief Draws the current time from the RTC on the screen.
 */
void draw_rtc();

/**
 * @brief Converts a keyboard scancode to a character.
 * 
 * @param keyboard_scancode The scancode to convert
 * @return The corresponding character, or '\0' if the scancode is not recognized
 */
char scancode_to_char(uint8_t keyboard_scancode);

/**
 * @brief Processes a keyboard scancode, adding the corresponding character to the player's name if valid.
 * 
 * @param keyboard_scancode The scancode to process
 */
void process_scancode(uint8_t keyboard_scancode);

/**
 * @brief Moves the sprite along the positive x-axis by its speed.
 * 
 * @param sprite Pointer to the sprite
 * @return 0 on success, non-zero otherwise
 */
int move_sprite_x(Sprite *sprite);

/**
 * @brief Moves the sprite along the negative x-axis by its speed.
 * 
 * @param sprite Pointer to the sprite
 * @return 0 on success, non-zero otherwise
 */
int move_sprite_neg_x(Sprite *sprite);

/**
 * @brief Moves the sprite along the positive y-axis by its speed.
 * 
 * @param sprite Pointer to the sprite
 * @return 0 on success, non-zero otherwise
 */
int move_sprite_y(Sprite *sprite);

/**
 * @brief Moves the sprite along the negative y-axis by its speed.
 * 
 * @param sprite Pointer to the sprite
 * @return 0 on success, non-zero otherwise
 */
int move_sprite_neg_y(Sprite *sprite);

/**
 * @brief Moves the sprite along the positive x-axis by 15 pixels.
 * 
 * @param sprite Pointer to the sprite
 * @return 0 on success, non-zero otherwise
 */
int move_sprite_x_p(Sprite *sprite);

/**
 * @brief Moves the sprite along the negative x-axis by 15 pixels.
 * 
 * @param sprite Pointer to the sprite
 * @return 0 on success, non-zero otherwise
 */
int move_sprite_neg_x_p(Sprite *sprite);

/**
 * @brief Moves the sprite along the positive y-axis by 15 pixels.
 * 
 * @param sprite Pointer to the sprite
 * @return 0 on success, non-zero otherwise
 */
int move_sprite_y_p(Sprite *sprite);

/**
 * @brief Moves the sprite along the negative y-axis by 15 pixels.
 * 
 * @param sprite Pointer to the sprite
 * @return 0 on success, non-zero otherwise
 */
int move_sprite_neg_y_p(Sprite *sprite);

/**
 * @brief Loads sprites for the screen.
 */
void load_sprites_to_menu();

/**
 * @brief Unloads sprites for the screen.
 */
void unload_sprites_of_menu();

/**
 * @brief Sorts sprites for the Leaderboard screen.
 */
void sort_leaderboard(); 

/**
 * @brief Draws the options screen.
 */
void draw_options();

#endif // SPRITE_H

