#ifndef _GAME_H_
#define _GAME_H_

#include "devices/graphic/graphics.h"
#include "devices/mouse/mouse.h"
#include <lcom/lcf.h>
#include <lcom/xpm.h>

/**
 * @brief Draws the game screen.
 * 
 * This function is responsible for rendering the main game screen, including
 * the arena, towers, coins, hearts, medals, and other game elements.
 * 
 * @return int 0 on success, non-zero otherwise
 */
int draw_game();

/**
 * @brief Displays the mouse cursor on the screen.
 * 
 * This function draws the mouse cursor at its current position on the screen.
 * It is typically called after handling mouse movement events.
 */
void display_mouse();

/**
 * @brief Selects towers based on mouse coordinates.
 * 
 * This function determines which tower is selected based on the mouse coordinates
 * provided. It updates the selected tower(s) accordingly.
 * 
 * @param x The x-coordinate of the mouse cursor
 * @param y The y-coordinate of the mouse cursor
 * @param selected Pointer to an array indicating the selected tower(s)
 */
void select_towers(uint16_t x, uint16_t y, int *selected);

/**
 * @brief Draws the selected tower(s) on the screen.
 * 
 * This function draws visual indicators for the selected tower(s) on the game screen.
 * 
 * @param selected Array indicating the selected tower(s)
 */
void draw_selected(int *selected);

#endif /* _GAME_H_ */
