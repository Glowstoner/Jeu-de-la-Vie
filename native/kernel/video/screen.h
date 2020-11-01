#ifndef SCREEN_H
#define SCREEN_H

#define YMAX 25
#define XMAX 80

#define CELL_ALIVE 0x27
#define CELL_DEAD 0x00
#define TEXT 0x70

#define VIDMEM 0xB8000

void putchar(unsigned char c, int spec, int x, int y);
void putstring(char* text, int spec, int y);
void clear();

#endif