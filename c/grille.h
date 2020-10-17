#ifndef GRILLE_H
#define GRILLE_H

#define ALIVE "\u2588"
#define DEATH " "

typedef struct {
    int row;
    int col;
    unsigned char** grid;
    int active;
} GRID;

GRID G;

void init_grid(int row, int col);
void init_grid_ncurses();
void show_grid_basic();
void init_ncurses();
void end_grid_ncurses();
void show_grid_ncurses();
void add_cell(int x, int y);
void randomize_grid();
int get_neighbours_alive(int x, int y);
void update_grid();
void start_game();

#endif