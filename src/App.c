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

uint16_t counter = 20;
uint8_t adc_pot = 0;
uint8_t value_G, value_R, value_B=0;


void delay_ms(void);
void RGB_GREEN(void)
{
	if(adc_pot <= 12)
		value_G=(25/3)*adc_pot;
	else if (adc_pot <= 42)
		value_G = 100;
	else if (adc_pot <= 58)
		value_G = (((-20/3)*adc_pot)+(1160/3));
	else
		value_G=0;

	RGB_PWM(RGB_VERDE,value_G);
}
void RGB_RED(void)
{
	if(adc_pot <= 12)
		value_R = 100;
	else if (adc_pot <= 25)
		value_R = (((-25/3)*adc_pot)+(625/3));
	else if (adc_pot <= 57)
		value_R=0;
	else if (adc_pot <= 78)
		value_R = ((5*adc_pot)-290);
	else
		value_R=100;

	RGB_PWM(RGB_ROJO,value_R);
}
void RGB_BLUE(void)
{
	if (adc_pot <= 25)
		value_B = 0;
	else if (adc_pot <= 42)
		value_B = (((25/4)*adc_pot)-(325/2));
	else if (adc_pot <= 78)
		value_B = 100;
	else
		value_B = (((-100/21)*adc_pot)+(10000/21));

	RGB_PWM(RGB_AZUL,value_B);
}

int main(void)
{
	BSP_Init();

	while(1)
	{
		adc_pot =  BSP_GetBrightness();
		if(!counter)
		{
			counter = 20;
			RGB_RED();
			RGB_GREEN();
			RGB_BLUE();
		}
	}
}

void delay_ms(void)
{
	if(counter){
		counter--;
	}

}
