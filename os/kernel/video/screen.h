#pragma once

#define YMAX 25
#define XMAX 80

#define CELL_ALIVE 0x27
#define CELL_DEAD 0x00
#define TEXT 0x70

#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5
#define VIDMEM 0xA0000

void set_offset(int offset);
int get_offset();
void putchar(unsigned char c, int spec, int x, int y);
void putstring(char* text, int spec, int y);
void clear();
unsigned char port_byte_in(unsigned short port);
void port_byte_out(unsigned short port, unsigned char data);
unsigned short port_word_in(unsigned short port);
void port_word_out(unsigned short port, unsigned short data);
