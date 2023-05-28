#include "ports.h"

unsigned char inb(unsigned short port) {
    unsigned char data;
    __asm__ volatile("inb %1, %0" : "=a"(data) : "d"(port));
    return data;
}

void outb(unsigned short port, unsigned char data) {
    __asm__ volatile("outb %0, %1" : : "a"(data), "d"(port));
}

unsigned char port_byte_in(unsigned short port) {
    return inb(port);
}

void port_byte_out(unsigned short port, unsigned char data) {
    outb(port, data);
}

unsigned short port_word_in(unsigned short port) {
    unsigned short data;
    __asm__ volatile("inw %1, %0" : "=a"(data) : "d"(port));
    return data;
}

void port_word_out(unsigned short port, unsigned short data) {
    __asm__ volatile("outw %0, %1" : : "a"(data), "d"(port));
}
