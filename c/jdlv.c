#include<stdlib.h>
#include<stdio.h>
#include"grille.h"

int main() {
    init_grid_ncurses();
    /*add_cell(&g, 20, 20);
    add_cell(&g, 20, 21);
    add_cell(&g, 20, 22);

    add_cell(&g, 20, 26);
    add_cell(&g, 20, 27);
    add_cell(&g, 20, 28);

    add_cell(&g, 18, 24);
    add_cell(&g, 17, 24);
    add_cell(&g, 16, 24);

    add_cell(&g, 22, 24);
    add_cell(&g, 23, 24);
    add_cell(&g, 24, 24);*/

    /*add_cell(&g, 50, 50);
    add_cell(&g, 51, 50);
    add_cell(&g, 52, 50);
    add_cell(&g, 50, 51);
    add_cell(&g, 50, 52);
    add_cell(&g, 52, 51);
    add_cell(&g, 52, 52);*/

    add_cell(100, 50);
    add_cell(101, 50);
    add_cell(101, 51);
    add_cell(101, 52);
    add_cell(102, 51);

    randomize_grid();
    start_game();
}