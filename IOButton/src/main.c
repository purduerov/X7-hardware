/**
  ******************************************************************************
  * @file    IO_Toggle/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    19-September-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************  
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4_discovery.h"
#include "stm32f4xx_conf.h" // again, added because ST didn't put it here ?


/** @addtogroup STM32F4_Discovery_Peripheral_Examples
  * @{
  */

/** @addtogroup IO_Toggle
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
GPIO_InitTypeDef  GPIO_InitStructure;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t index = 0;
int GPIO[] = { GPIO_Pin_12, GPIO_Pin_13, GPIO_Pin_14, GPIO_Pin_15 };
int leds[] = { 0, 0, 0, 0 };
/* Private function prototypes -----------------------------------------------*/
void LEDStartupRoutine();
void Delay(__IO uint32_t nCount);
void SetLED(uint8_t led, uint8_t value);
void ToggleLED(uint8_t led);
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f4xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
        system_stm32f4xx.c file
     */

  /* GPIOD Periph clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  /* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /* GPIOD Periph clock enable */
  RCC_AHB1PeriphClockCmd(USER_BUTTON_GPIO_CLK, ENABLE);

  /* Configure Button in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = USER_BUTTON_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(USER_BUTTON_GPIO_PORT, &GPIO_InitStructure);

  LEDStartupRoutine();
 
  while (1) {
	  Delay(0x06FFFF);
	  uint8_t button = GPIO_ReadInputDataBit(USER_BUTTON_GPIO_PORT, USER_BUTTON_PIN);
	  index++;
	  
	  if (button) {
		  SetLED(1, 1);
	  }
	  else {
		  SetLED(1,0);
	  }
  }
}
/* If value is 0, turns led off. Otherwise turn led on.*/
void SetLED(uint8_t led, uint8_t value) {
	if (value != 0) {
		GPIO_SetBits(GPIOD, GPIO[led]);
		leds[led] = 1;
	}
	else if (value == 0) {
		GPIO_ResetBits(GPIOD, GPIO[led]);
		leds[led] = 0;
	}
}
/* If led is on, turn off. If led is off, turn on.*/
void ToggleLED(uint8_t led) {
	if (leds[led]) {
		SetLED(led, 0);
	}
	else {
		SetLED(led, 1);
	}
}

void LEDStartupRoutine() {
	// Turn on in sequence
	SetLED(0, 1);
	Delay(0x3FFFFF);
	SetLED(1, 1);
	Delay(0x3FFFFF);
	SetLED(2, 1);
	Delay(0x3FFFFF);
	SetLED(3, 1);
	Delay(0x3FFFFF);
	// Turn off in sequence
	SetLED(0, 0);
	Delay(0x3FFFFF);
	SetLED(1, 0);
	Delay(0x3FFFFF);
	SetLED(2, 0);
	Delay(0x3FFFFF);
	SetLED(3, 0);
	Delay(0x3FFFFF);
}

/**
  * @brief  Delay Function.
  * @param  nCount:specifies the Delay time length.
  * @retval None
  */
void Delay(__IO uint32_t nCount)
{
  while(nCount--)
  {
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
