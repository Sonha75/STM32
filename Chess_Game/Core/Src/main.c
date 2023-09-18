/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "var.h"
#include "lcd_i2c.h"
#include "math.h"
#include "stdlib.h"
#include "time.h"
#include <string.h>
#include <stdio.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
uint8_t soxucxac;

uint8_t P1state=0;
uint8_t P2state=0;
uint8_t *v1=&P1state;
uint8_t *v2=&P2state;

uint8_t vitriP1=0;
uint8_t vitriP2=30;
uint8_t *Person1=&vitriP1;
uint8_t *Person2=&vitriP2;

uint8_t flag59=0;
uint8_t *Flag59=&flag59;

uint8_t Game_State;

uint8_t res1[30];
uint8_t res2[30];

uint8_t buffer[5];

uint8_t Start=0;
char stringLCD[50];
char str[50];
char buoc1[50];
char buoc2[50];

uint8_t c1=0,c2=0;
uint8_t *count1=&c1;
uint8_t *count2=&c2;


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
int Check1(uint8_t *Person1)
{
 return 60-*Person1;
}
int Check2(uint8_t *Person2,uint8_t *Flag59)
{ 
	if(*Person2 >30 && *Person2 <60)
	{
	*Flag59=0;
	}
	else
		*Flag59=1;
	
 if(*Flag59 == 0)
 {
  return 30 + 60-*Person2;
 }
 else if(*Flag59 == 1)
 {
  return 30- *Person2;
 }
}

void MoveP1(uint8_t soxucxac,uint8_t *Person1, uint8_t *Person2,uint8_t *Flag59,uint8_t *v1)
{
	if(*Person2 >= 60)
	{
	*Person2=*Person2-60;
	*Flag59=1;
	}
	if( *Person1 + soxucxac < 60)
{
	if(*Person2 - *Person1 > 0 )
	{
	 if( *Person2 - *Person1 > soxucxac )
	 {
	  *Person1 = *Person1 + soxucxac;
	 }
	 else if( *Person2 - *Person1 == soxucxac )
	 {
	  *Person1 = *Person1 + soxucxac;
		*Person2 = 31;
		 Game_State=12;
	 }
	 else
	{
	 Game_State=10;
	 }
	}
	else if( *Person2 - *Person1 < 0 )
	{
	 *Person1 = *Person1 + soxucxac;
	}
}
 else if(*Person1 + soxucxac == 60 )
 {
  *Person1=1;
	 *v1+=1;
	 Game_State=14;
 }
 else
	 Game_State=16;
 
}
void MoveP2(uint8_t soxucxac,uint8_t *Person1, uint8_t *Person2,uint8_t *Flag59,uint8_t *v2)
{
	if(*Person2 >= 60)
	{
	*Person2=*Person2-60;
	*Flag59=1;
	}
	if(*Flag59 ==0 || (*Flag59 == 1 && *Person2 + soxucxac < 30) )
	{
	 if( *Person1 - *Person2 > 0 )
	 {
	  if(*Person1 - *Person2 > soxucxac )
		{
		 *Person2 = *Person2 + soxucxac;
		}
		else if( *Person1 - *Person2 == soxucxac )
		{
		 *Person2 = *Person2 + soxucxac;
		 *Person1 = 1;
			Game_State=13;
		}
		else
			Game_State=11;
	 }
	 else if( *Person1 - *Person2 < 0)
	 {
	  *Person2 = *Person2 + soxucxac;
	 }
	}
	if( *Person2 + soxucxac == 30 )
	{
	 *Person2 =31;
	 *v2+=1;
		Game_State=15;
	}
	if(*Person2 + soxucxac > 30)
	{
		Game_State=17;
	}
}
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
void CMD(){
	
	 HAL_UART_Receive_IT(&huart1,(uint8_t*)buffer,sizeof(buffer));
	}
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  //  srand((unsigned int)time(NULL)); // lam thay doi so xuc xac ngau nhien
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  LCD_I2C_Init();
	LCD_I2C_Clear();
	HAL_Delay(500);
	LCD_I2C_Location(0,0);
	LCD_I2C_String("Hello ");
	HAL_Delay(1000);
	
	CMD();
		
		HAL_Delay(5000);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
switch(Game_State)
		{
			/*case 0:
				LCD_I2C_Clear();
		    LCD_I2C_Location(0,0);
			  HAL_Delay(1000);
		    LCD_I2C_String("Start game");
		    HAL_Delay(1000);
        break;*/
			case 1:
				LCD_I2C_Clear();
		    LCD_I2C_Location(0,0);
		    LCD_I2C_String("Make CMD");
		    HAL_Delay(1000);
        break;
			case 2:
				HAL_Delay(1000);
				LCD_I2C_Clear();
			  LCD_I2C_Location(0,0);
			  LCD_I2C_String("Person 1");
			  LCD_I2C_Location(1,0);
			
			  sprintf((char*)stringLCD,"Move %d buoc",soxucxac);
			  LCD_I2C_String((char*)stringLCD);
			  break;
			
			case 3:
				HAL_Delay(1000);
				LCD_I2C_Clear();
		  	LCD_I2C_Location(0,0);
			  LCD_I2C_String("Person 2");
			  LCD_I2C_Location(1,0);
			  LCD_I2C_String((char*)stringLCD);
			  break; 
			
			case 4:
				HAL_Delay(1000);
				LCD_I2C_Clear();
			  LCD_I2C_Location(0,0);
			  LCD_I2C_String((char*)buoc1);
			  HAL_Delay(2000);
			  LCD_I2C_Clear();
		  	LCD_I2C_Location(0,0);
	  		LCD_I2C_String("P1 cach dich");
		  	LCD_I2C_Location(1,2);
			  LCD_I2C_String((char*)res1);
			  HAL_Delay(1000);
			  break;
			
			case 5:
				HAL_Delay(1000);
			  LCD_I2C_Clear();
			  LCD_I2C_Location(0,0);
			  LCD_I2C_String((char*)buoc2);
			  HAL_Delay(2000);
				LCD_I2C_Clear();
			  LCD_I2C_Location(0,0);
		  	LCD_I2C_String("P2 cach dich");
			  LCD_I2C_Location(1,2);
			  LCD_I2C_String((char*)res2);
			  HAL_Delay(1000);
			  break;
			
			case 6:
				LCD_I2C_Clear();
			  LCD_I2C_Location(0,0);
			  LCD_I2C_String((char*)str);
			  HAL_Delay(1000);
			  break;
			
			case 7:
		    LCD_I2C_Clear();
			  LCD_I2C_Location(0,0);
			  LCD_I2C_String((char*)str); 
			  HAL_Delay(1000);
			  break;
			
		  case 8:
				LCD_I2C_Clear();
			  LCD_I2C_Location(0,0);
			  LCD_I2C_String("Person 1");
			  HAL_Delay(500);
			  LCD_I2C_Location(1,0);
			  LCD_I2C_String("Win");
			  HAL_Delay(1000);
			  break;
			
		  case 9:
				LCD_I2C_Clear();
			  LCD_I2C_Location(0,0);
			  LCD_I2C_String("Person 2");
			  HAL_Delay(500);
			  LCD_I2C_Location(1,0);
			  LCD_I2C_String("Win");
			  HAL_Delay(1000);
			  break;
		  case 10:
				LCD_I2C_Clear();
			  LCD_I2C_Location(0,0);
			  LCD_I2C_String("P1 can't kick P2");
			  HAL_Delay(1000);
			  break;
			case 11:
				LCD_I2C_Clear();
			  LCD_I2C_Location(0,0);
			  LCD_I2C_String("P2 can't kick P1");
			  HAL_Delay(1000);
			  break;
			case 12:
				LCD_I2C_Clear();
			  LCD_I2C_Location(0,0);
			  LCD_I2C_String("P1 kicked P2");
			  HAL_Delay(1000);
			  break;
			case 13:
				LCD_I2C_Clear();
			  LCD_I2C_Location(0,0);
			  LCD_I2C_String("P2 kicked P1");
			  HAL_Delay(1000);
		  	break;
			case 14:
				LCD_I2C_Clear();
			  LCD_I2C_Location(0,0);
			  char r1[50];
			  sprintf((char*)r1,"%d con P1 ve dich",*v1);
			  LCD_I2C_String((char*)r1);
			  HAL_Delay(1000);
		  	break;
			case 15:
				LCD_I2C_Clear();
			  LCD_I2C_Location(0,0);
			  char r2[50];
			  sprintf((char*)r2,"%d con P2 ve dich",*v2);
			  LCD_I2C_String((char*)r2);
			  HAL_Delay(1000);
		  	break;
			case 16:
				LCD_I2C_Clear();
			  LCD_I2C_Location(0,0);
			  LCD_I2C_String("P1 ko di dc");
			  HAL_Delay(1000);
			  break;
			case 17:
				LCD_I2C_Clear();
			  LCD_I2C_Location(0,0);
			  LCD_I2C_String("P2 ko di dc");
			  HAL_Delay(1000);
			  break;
		}
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
if(huart->Instance == huart1.Instance)
 {
	 
  if(Start ==0)
	{ 
		if(buffer[0]== 0xAB && buffer[4]==0xBA && buffer[1]==0x00) //Start
	 {                                                                   
	  Start=1;
		HAL_UART_Transmit(&huart1,(uint8_t*)"\nStart\n",sizeof("\nStart\n"),100);
		Game_State=1;
	 }
 }
	if(Start==1)
	{
		CMD();
		if(buffer[0]==0xAB&& buffer[4]==0xBA && buffer[1]==0x01) //Move
	 { 
		 HAL_UART_Transmit(&huart1,(uint8_t*)"\nMove\n",sizeof("\nMove\n"),100);
		 soxucxac=(rand() % 6) + 1;
		/* char resp[16];
		 sprintf((char*)resp,"soxucxac= %d ",soxucxac);*/
	  // soxucxac = 1 + (int)(rand()*(6-1+1.0)/(1.0+RAND_MAX)); //tung xuc xac
		// HAL_UART_Transmit(&huart1,(uint8_t*)resp,sizeof(resp),100);
		 
		 if( buffer[3]==0x01)
		 {
			 HAL_UART_Transmit(&huart1,(uint8_t*)"MoveP1\n",sizeof("MoveP1\n"),100);
			 //HAL_UART_Transmit(&huart1,(uint8_t*)"Start1",sizeof("Start"),100);
		  Game_State=2;
			 MoveP1(soxucxac,Person1,Person2,Flag59,v1);
			sprintf((char*)stringLCD,"Move %d buoc",soxucxac);
			HAL_UART_Transmit(&huart1,(uint8_t*)stringLCD,sizeof(stringLCD),100);
			
			*count1=*count1 +1;
			
			
				
		
		 }
		 else if(buffer[3]== 0x02 )
		 {
			 Game_State=3;
			HAL_UART_Transmit(&huart1,(uint8_t*)"MoveP2",sizeof("MoveP2"),100);
		  MoveP2(soxucxac,Person1,Person2,Flag59,v2);
			sprintf(stringLCD,"Move %d buoc",soxucxac);
			 
			 *count2=*count2 +1;
			 
		 
		 }
	 }
	 else if(buffer[0]==0xAB && buffer[4]==0xBA && buffer[1]==0x02) //Check
	 {
		HAL_UART_Transmit(&huart1,(uint8_t*)"\nCheck\n",sizeof("\nCheck\n"),100);
	  if(buffer[3]==0x01 )
		{
		 int d =Check1(Person1);
		
		sprintf((char*)buoc1,"P1 position: %d",*Person1);
		sprintf((char*)res1,"%d buoc",d);
		  Game_State=4;
		}
		else if(buffer[3]==0x02)
		{
		  int d=Check2(Person2,Flag59);
			sprintf((char*)buoc2,"P2 position: %d",*Person2);
		  sprintf((char*)res2,"%d buoc",d);
		  Game_State=5;
		}
	}
	 else if(buffer[0]==0xAB && buffer[4]==0xBA && buffer[1]==0x03) //Log
	 {
		 HAL_UART_Transmit(&huart1,(uint8_t*)"\nLog\n",sizeof("\nLog\n"),100);
	   if(buffer[3]== 0x01 )
		 {
			sprintf((char*)str,"P1 qua %d turn",*count1);
			Game_State=6;
		 }
		 else if(buffer[3]== 0x02)
		 {
			sprintf((char*)str,"P2 qua %d turn",*count2);
			Game_State=7;
		 }
	 
	 }
	 if(*v1 > *v2 && *v1 == 2)
	 {
	  Game_State=8;
	 }
	 else if(*v1 < *v2 && *v2 == 2)
	 {
	  Game_State=9;
	 }
	 else;
	}
 }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
