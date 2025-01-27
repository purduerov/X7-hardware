#include "led.h"


led::led()
{
	GPIO_InitTypeDef  GPIO_InitStructure; 
	
	/* GPIOD Periph clock enable */
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	  /* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void led::blueOn()
{
	GPIO_SetBits(GPIOD, GPIO_Pin_15); 
}

void led::redOn()
{
	GPIO_SetBits(GPIOD, GPIO_Pin_14); 
}

void led::greenOn()
{
	GPIO_SetBits(GPIOD, GPIO_Pin_12); 
}

void led::orangeOn()
{
	GPIO_SetBits(GPIOD, GPIO_Pin_13); 
}
