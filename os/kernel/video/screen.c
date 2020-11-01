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
    int size = XMAX * YMAX;
    unsigned char* VIDEOMEM = (unsigned char*) VIDMEM;
    for(int i = 0; i < size; i++) {
        VIDEOMEM[i*2] = ' ';
        VIDEOMEM[i*2+1] = TEXT;
    }
    set_offset(0);
}

void putchar(unsigned char c, int spec, int x, int y) {
    unsigned char* VIDEOMEM = (unsigned char*) VIDMEM;
    *(VIDEOMEM + 2 * (y * XMAX + x)) = c;
    *(VIDEOMEM + 2 * (y * XMAX + x) + 1) = spec;
    set_offset(2 * (y * XMAX + x));
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