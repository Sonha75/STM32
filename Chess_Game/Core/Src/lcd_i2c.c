#include "lcd_i2c.h"
#include "main.h"
#include "string.h"
#include "stdio.h"
extern I2C_HandleTypeDef hi2c1;

#define addr_pcf8574 0x4E

void LCD_I2C_Write_CMD(uint8_t cmd)
{
	uint8_t buffer[4];
	buffer[0]=(cmd & 0xF0)|0x0C ;
	buffer[1]=(cmd & 0xF0)| 0x08;
	buffer[2]=(cmd <<4)&0xF0 |0x0C;
	buffer[3]=(cmd <<4)&0xF0 |0x08;
	HAL_I2C_Master_Transmit(&hi2c1,addr_pcf8574,(uint8_t *)buffer,4,HAL_MAX_DELAY);
}

void LCD_I2C_Write_Data(uint8_t data)
{
 uint8_t buffer[4]={(data & 0xF0) | 0x0D,(data & 0xF0) | 0x09,(data << 4)&0xF0 | 0x0D ,(data << 4)&0xF0 | 0x09 };
 HAL_I2C_Master_Transmit(&hi2c1,addr_pcf8574,buffer,4,HAL_MAX_DELAY);
}

void LCD_I2C_Clear()   // xoa man hinh
{
	LCD_I2C_Write_CMD(0x01);
	HAL_Delay(2);
	
	
}

void LCD_I2C_Location(uint8_t hang, uint8_t cot) //chon vi tri
{
 if(hang==0)
 {
	 LCD_I2C_Write_CMD(0x80+cot);
 }
 else if(hang==1)
	 {
	 LCD_I2C_Write_CMD(0xC0+cot);
	 }
}

void LCD_I2C_Init()
{
	
	LCD_I2C_Write_CMD(0x33); //lenh khoi tao
	LCD_I2C_Write_CMD(0x32); //khoi tao
	LCD_I2C_Write_CMD(0x28);  //che do 4 bit, 2 hang 5x7
	LCD_I2C_Write_CMD(0x0C);  //hien thi man hinh va tat con tro
	LCD_I2C_Write_CMD(0x06);  //tang con tro
	LCD_I2C_Write_CMD(0x01);  //xoa man hinh
	
	HAL_Delay(2);
	
	
}

void LCD_I2C_String(char *string)
{
for(int i=0;i<strlen(string);i++)
	{
LCD_I2C_Write_Data(string[i]);
  }
}

void LCD_I2C_Number(int number)
{
	char num2str[20];
	sprintf(num2str,"%d",number);
	for(int i=0;i<strlen(num2str);i++)
	{
LCD_I2C_Write_Data(num2str[i]);
  }
}