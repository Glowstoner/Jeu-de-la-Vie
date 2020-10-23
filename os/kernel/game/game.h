#ifndef GAME_H
#define GAME_H

typedef unsigned char GRID[ROWS][COLS];

void initgame();
void initgrid(GRID g);
int cell_neighbours(GRID g, int x, int y);
void update_game(GRID g);
void update_grid(GRID g);
void update_screen(GRID g);

#endif