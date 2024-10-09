/**
 * @file menu.h
 * @brief Header file for menu-related functions.
 */

#ifndef _MENU_H_
#define _MENU_H_

#include "devices/graphic/graphics.h"
#include "devices/keyboard/kbd.h"
#include "devices/mouse/mouse.h"
#include <lcom/lcf.h>
#include <lcom/xpm.h>

/**
 * @brief Draws the menu on the screen at the specified coordinates.
 * 
 * @param x The x-coordinate of the menu.
 * @param y The y-coordinate of the menu.
 * @return Return 0 upon success and non-zero otherwise.
 */
int draw_menu(uint16_t x, uint16_t y);

/**
 * @brief Handles a click event on the "Play" button.
 * 
 * @param x The x-coordinate of the click.
 * @param y The y-coordinate of the click.
 * @return Return 0 if the click is within the "Play" button, and non-zero otherwise.
 */
int clickPlay(uint16_t x, uint16_t y);

/**
 * @brief Handles a click event on the "Quit" button.
 * 
 * @param x The x-coordinate of the click.
 * @param y The y-coordinate of the click.
 * @param quit Pointer to a boolean variable indicating if the game should quit.
 * @return Return 0 if the click is within the "Quit" button, and non-zero otherwise.
 */
int clickQuit(uint16_t x, uint16_t y, bool *quit);

/**
 * @brief Handles a click event on the "Leaderboard" button.
 * 
 * @param x The x-coordinate of the click.
 * @param y The y-coordinate of the click.
 * @return Return 0 if the click is within the "Leaderboard" button, and non-zero otherwise.
 */
int clickLeaderboard(uint16_t x, uint16_t y);

/**
 * @brief Handles a click event on the "Settings" button.
 * 
 * @param x The x-coordinate of the click.
 * @param y The y-coordinate of the click.
 * @return Return 0 if the click is within the "Settings" button, and non-zero otherwise.
 */
int clickOptions(uint16_t x, uint16_t y);

#endif
