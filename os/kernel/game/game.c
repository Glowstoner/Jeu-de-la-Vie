#include "../video/screen.h"
#include "game.h"

void initgame() {
    GRID g;
    initgrid(g);
    update_screen(g);

    /*for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 15; j++) {
            g[i][j] = '@';
        }
    }*/

    g[25][3] = '@';
    g[25][4] = '@';
    g[25][5] = '@';
    g[25][6] = '@';
    
    update_screen(g);
    //return;
    unsigned long long l = 100000000;
    while(1) {
        while(l > 0) {
            l--;
        }
        l = 100000000;
        update_game(g);
    }
}

void initgrid(GRID g) {
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            g[i][j] = ' ';
        }
    }
}

int cell_neighbours(GRID g, int x, int y) {
    int nt = 0;
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            if(x + i >= ROWS || y + j >= COLS || x + i < 0 || y + j < 0 || (i == 0 && j == 0)) {
                continue;
            }

            if(g[x+i][y+i] == '@') nt++;
        }
    }

    return nt;
}

void update_game(GRID g) {
    update_grid(g);
    update_screen(g);
}

void update_grid(GRID g) {
    GRID tmpg;

    for(int i = 0; i < COLS; i++) {
        for(int j = 0; j < ROWS; j++) {
            if(g[i][j] == '@') {
                int cn = cell_neighbours(g, i, j);
                if(cn == 2 || cn == 3) {
                    tmpg[i][j] = '@';
                }else {
                    tmpg[i][j] = ' ';
                }
            }else {
                if(cell_neighbours(g, i, j) == 3) {
                    tmpg[i][j] = '@';
                }else {
                    tmpg[i][j] = ' ';
                }
            }
        }
    }

    for(int i = 0; i < COLS; i++) {
        for(int j = 0; j < ROWS; j++) {
            g[i][j] = tmpg[i][j];
        }
    }
}

void update_screen(GRID g) {
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            putchar(g[i][j], i, j);
        }
    }
}