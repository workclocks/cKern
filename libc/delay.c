#include "delay.h"

void delay(int milliseconds) {
    for (int i = 0; i < milliseconds * 1000000; i++) {
        asm volatile("nop");
    }
}
