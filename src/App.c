/**
  ******************************************************************************
  * @file    App.c
  * @author  Ac6
  * @version V1.0
  * @date    18-08-2016
  * @brief   Laboratorio I UCC.
  ******************************************************************************
*/
#include "bsp/bsp.h"

uint16_t counter = 200;
uint8_t brightness = 0;


void delay_ms(void);



int main(void)
{
	BSP_Init();

	while(1)
	{
		brightness = BSP_GetBrightness();
		if(!counter)
		{
			RGB_PWM(0,brightness);
			counter = 200;
		}
	}

}

void delay_ms(void)
{
	if(counter){
		counter--;
	}

}
