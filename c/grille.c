#include<stdlib.h>
#include<stdio.h>
#include<ncursesw/ncurses.h>
#include<locale.h>
#include"grille.h"

void handle_grid_ncurses();

void init_grid(int row, int col) {
    unsigned char** g = malloc(sizeof(unsigned char*) * row);
    for(int i = 0; i < row; i++) {
        g[i] = malloc(sizeof(unsigned char) * col);
        for(int j = 0; j < col; j++) {
            g[i][j] = 0;
        }
    }

    G.row = row;
    G.col = col;
    G.grid = g;
}

void init_grid_ncurses() {
    setlocale(LC_ALL, "");
    initscr();
    init_grid(LINES, COLS);
    curs_set(0);
}

void show_grid_basic() {
    for(int i = G.row - 1; i >= 0; i--) {
        for(int j = 0; j < G.col; j++) {
            if(G.grid[i][j]) {
                printf("%s", ALIVE);
            }else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void end_grid_ncurses() {
    endwin();
}

void show_grid_ncurses() {
    end_grid_ncurses();
    initscr();
    clear();

    for(int i = 0; i < G.row; i++) {
        for(int j = 0; j < G.col; j++) {
            if(G.grid[i][j]) {
                mvaddstr(i, j, ALIVE);
            }else {
                mvaddstr(i, j, " ");
            }
        }
    }
    refresh();
}

void add_cell(int x, int y) {
    if(x >= G.col || y >= G.row) {
        end_grid_ncurses();
        fprintf(stderr, "Cellule or de portée %d;%d -/> (maxx: %d; maxy: %d)\n", x, y, G.col, G.row);
        exit(EXIT_FAILURE);
    }

    G.grid[y][x] = 1;
}

int get_neighbours_alive(int x, int y) {
    int c = 0;
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            if((i == 0 && j == 0) || y+i < 0 || y+i >= G.row || x+j < 0 || x+j >= G.col) {
                continue;
            }

            if(G.grid[y+i][x+j]) {
                c++;
            }
        }
    }

    return c;
}

void update_grid() {
    unsigned char** g = malloc(sizeof(unsigned char*) * G.row);
    for(int i = 0; i < G.row; i++) {
        g[i] = malloc(sizeof(unsigned char) * G.col);
    }

    for(int i = 0; i < G.row; i++) {
        for(int j = 0; j < G.col; j++) {
            if(G.grid[i][j]) {
                int na = get_neighbours_alive(j, i);
                if(!(na == 2 || na == 3)) {
                    g[i][j] = 0;
                }else {
                    g[i][j] = 1;
                }
            }else {
                if(get_neighbours_alive(j, i) == 3) {
                    g[i][j] = 1;
                }else {
                    g[i][j] = 0;
                }
            }
        }
    }

    for(int i = 0; i < G.row; i++) {
        free(G.grid[i]);
    }
    free(G.grid);
    G.grid = g;
}