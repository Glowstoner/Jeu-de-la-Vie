#include "screen.h"

int get_offset() {
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2;
}

void set_offset(int offset) {
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

void clear() {
    int size = ROWS * COLS;
    unsigned char* VIDEOMEM = (unsigned char*) 0xb8000;
    for(int i = 0; i < size; i++) {
        VIDEOMEM[i*2] = ' ';
        VIDEOMEM[i*2+1] = RED_BACKGROUND;
    }
    set_offset(0);
}

void putchar(unsigned char c, int x, int y) {
    unsigned char* VIDEOMEM = (unsigned char*) 0xb8000;
    *(VIDEOMEM + 2 * (y * ROWS + x)) = c;
    *(VIDEOMEM + 2 * (y * ROWS + x) + 1) = RED_TEXT;
    set_offset(2 * (y * ROWS + x));
}

unsigned char port_byte_in(unsigned short port) {
    unsigned char result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_byte_out(unsigned short port, unsigned char data) {
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

unsigned short port_word_in(unsigned short port) {
    unsigned short result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_word_out(unsigned short port, unsigned short data) {
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}