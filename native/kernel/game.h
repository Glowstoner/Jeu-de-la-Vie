#pragma once

#include "video/screen.h"
#define DELAY 100000000
#define GYMAX YMAX - 1

typedef unsigned char GRID[XMAX][GYMAX];

int get_neighbours(GRID g, int x, int y);
void add_cell(GRID g, int x, int y);
void display_grid(GRID g);
void update_grid(GRID g);
void init_grid(GRID g);
void add_infobar();