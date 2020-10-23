#ifndef SCREEN_H
#define SCREEN_H

#define ROWS 80
#define COLS 25

#define RED_BACKGROUND 0x48
#define RED_TEXT 0x40

#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

void set_offset(int offset);
int get_offset();
void putchar(unsigned char c, int x, int y);
void clear();
unsigned char port_byte_in(unsigned short port);
void port_byte_out(unsigned short port, unsigned char data);
unsigned short port_word_in(unsigned short port);
void port_word_out(unsigned short port, unsigned short data);

#endif