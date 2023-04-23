#include <stdint.h>
#include "max7219.h"
#include "main.h"

#define MAX7219_CLK_RESET() HAL_GPIO_WritePin(MAX7219_CLK_GPIO_Port, MAX7219_CLK_Pin, GPIO_PIN_RESET)
#define MAX7219_CLK_SET() HAL_GPIO_WritePin(MAX7219_CLK_GPIO_Port, MAX7219_CLK_Pin, GPIO_PIN_SET)
#define MAX7219_CS_RESET() HAL_GPIO_WritePin(MAX7219_CS_GPIO_Port, MAX7219_CS_Pin, GPIO_PIN_RESET)
#define MAX7219_CS_SET() HAL_GPIO_WritePin(MAX7219_CS_GPIO_Port, MAX7219_CS_Pin, GPIO_PIN_SET)

static void write_max7219_byte(uint8_t data)
{
    uint8_t i;
    MAX7219_CS_RESET();
    for (i = 8; i >= 1; i--)
    {
        // Max7219_pinCLK = 0;
        MAX7219_CLK_RESET();
        // Max7219_pinDIN = data & 0x80;
        // 从最高位写入
        if (data & 0x80)
        {
            HAL_GPIO_WritePin(MAX7219_IN_GPIO_Port, MAX7219_IN_Pin, GPIO_PIN_SET);
        }
        else
        {
            HAL_GPIO_WritePin(MAX7219_IN_GPIO_Port, MAX7219_IN_Pin, GPIO_PIN_RESET);
        }
        data = data << 1;
        MAX7219_CLK_SET();
    }
}

void write_max7219(uint8_t address, uint8_t dat)
{
    MAX7219_CS_RESET();
    write_max7219_byte(address); // 写入地址，即数码管编号
    write_max7219_byte(dat);     // 写入数据，即数码管显示数字
    MAX7219_CS_SET();
}

void init_max7219(void)
{
    write_max7219(0x09, 0xff); // 译码方式：BCD码
    write_max7219(0x0a, 0x01); // 亮度
    write_max7219(0x0b, 0x07); // 扫描界限；4个数码管显示
    write_max7219(0x0c, 0x01); // 掉电模式：0，普通模式：1
    write_max7219(0x0f, 0x01); // 显示测试：1；测试结束，正常显示：0
}