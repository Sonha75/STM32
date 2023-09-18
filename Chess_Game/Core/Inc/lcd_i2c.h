#ifndef _LCD_I2C_h_

#include "stm32f1xx_hal.h"

#include "main.h"

void LCD_I2C_Write_CMD(uint8_t cmd);
void LCD_I2C_Write_Data(uint8_t data);
void LCD_I2C_Clear();
void LCD_I2C_Location(uint8_t hang, uint8_t cot);
void LCD_I2C_Init();
void LCD_I2C_String(char *string);
void LCD_I2C_Number(int number);



#endif