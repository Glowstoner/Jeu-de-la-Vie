#include "video/screen.h"
#include "game.h"

void kmain(void) {
    clear();
    
    GRID g;
    init_grid(g);
    display_grid(g);
    add_infobar();

    add_cell(g, 10, 10);
    add_cell(g, 11, 10);
    add_cell(g, 11, 11);
    add_cell(g, 11, 12);
    add_cell(g, 12, 11);

    display_grid(g);

    unsigned long long l = DELAY;
    for(;;) {
        while(l > 0) {
            l--;
        }
        l = DELAY;
        update_grid(g);
        display_grid(g);
    }
    display_grid(g);
}

void init_grid(GRID g) {
    for(int i = 0; i < XMAX; i++) {
        for(int j = 0; j < GYMAX; j++) {
            g[i][j] = CELL_DEAD;
        }
    }
}

void display_grid(GRID g) {
    for(int i = 0; i < XMAX; i++) {
        for(int j = 0; j < GYMAX; j++) {
            putchar(' ', g[i][j], i, j);
        }
    }
}

void add_cell(GRID g, int x, int y) {
    if(x >= 0 && x < XMAX && y >= 0 && y < GYMAX) {
        g[x][y] = CELL_ALIVE;
    }
}

int get_neighbours(GRID g, int x, int y) {
    int nei = 0;
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            if(x + i >= XMAX || y + j >= GYMAX || x + i < 0 || y + j < 0 || (i == 0 && j == 0)) {
                continue;
            }

            if(g[x + i][y + j] == CELL_ALIVE){
                nei++;
            }
        }
    }

    return nei;
}

void update_grid(GRID g) {
    unsigned char tmpg[XMAX][GYMAX];

    for(int i = 0; i < XMAX; i++) {
        for(int j = 0; j < GYMAX; j++) {
            if(g[i][j] == CELL_ALIVE) {
                int na = get_neighbours(g, i, j);
                if(na == 2 || na == 3) {
                    tmpg[i][j] = CELL_ALIVE;
                }else {
                    tmpg[i][j] = CELL_DEAD;
                }
            }else {
                if(get_neighbours(g, i, j) == 3) {
                    tmpg[i][j] = CELL_ALIVE;
                }else {
                    tmpg[i][j] = CELL_DEAD;
                }
            }
        }
    }
    
    for(int i = 0; i < XMAX; i++) {
        for(int j = 0; j < GYMAX; j++) {
            g[i][j] = tmpg[i][j];
        }
    }
}

void add_infobar() {
    putstring("     jeu de la vie :)", TEXT, YMAX - 1);
}