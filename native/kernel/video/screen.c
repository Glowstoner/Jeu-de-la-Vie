#include "screen.h"

void clear() {
    int size = XMAX * YMAX;
    unsigned char* VIDEOMEM = (unsigned char*) VIDMEM;
    for(int i = 0; i < size; i++) {
        VIDEOMEM[i*2] = ' ';
        VIDEOMEM[i*2+1] = TEXT;
    }
}

void putchar(unsigned char c, int spec, int x, int y) {
    unsigned char* VIDEOMEM = (unsigned char*) VIDMEM;
    *(VIDEOMEM + 2 * (y * XMAX + x)) = c;
    *(VIDEOMEM + 2 * (y * XMAX + x) + 1) = spec;
}

void putstring(char* text, int spec, int y) {
    unsigned char* VIDEOMEM = (unsigned char*) VIDMEM;
    int c = 0;
    while(text[c] != '\0') {
        *(VIDEOMEM + 2 * (y * XMAX + c)) = text[c];
        *(VIDEOMEM + 2 * (y * XMAX + c) + 1) = spec;
        c++;
    }
}