#ifndef __MAX7219_H
#define __MAX7219_H

#include <stdint.h>

void write_max7219(uint8_t address, uint8_t dat);
void init_max7219(void);
#endif