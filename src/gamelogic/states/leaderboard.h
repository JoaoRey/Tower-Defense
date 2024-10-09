#ifndef _LEADERBOARD_H_
#define _LEADERBOARD_H_

#include "devices/graphic/graphics.h"
#include "devices/keyboard/kbd.h"
#include "devices/mouse/mouse.h"
#include <lcom/lcf.h>
#include <lcom/xpm.h>

/**
 * @brief Draws the leaderboard on the screen.
 * 
 * This function is responsible for rendering the leaderboard, which typically displays 
 * the high scores or rankings in the game.
 * 
 * @return int 0 on success, non-zero otherwise
 */
int draw_leaderboard();


#endif
