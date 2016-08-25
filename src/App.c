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
uint32_t adc_pot = 0;
uint32_t value_G, value_R, value_B=0;
uint32_t RES=10;

void delay_ms(void);
void RGB_GREEN(void)
{
	if(adc_pot <= 12*RES)
		value_G=((25*adc_pot)/(3*RES));
	else if (adc_pot <= 42*RES)
		value_G = 100;
	else if (adc_pot <= 58*RES)
		value_G = ((1160)/3) - ((20*adc_pot)/(3*RES));
	else
		value_G=0;

	RGB_PWM(RGB_VERDE,value_G);
}
void RGB_RED(void)
{
	if(adc_pot <= 12*RES)
		value_R = 100;
	else if (adc_pot <= 25*RES)
		value_R = (625/3) - ((25*adc_pot)/(3*RES));
	else if (adc_pot <= 57*RES)
		value_R=0;
	else if (adc_pot <= 78*RES)
		value_R = ((100*adc_pot)/(21*RES))-(1900/7);
	else
		value_R=100;

	RGB_PWM(RGB_ROJO,value_R);
}
void RGB_BLUE(void)
{
	if (adc_pot <= 25*RES)
		value_B = 0;
	else if (adc_pot <= 42*RES)
		value_B = ((((25*adc_pot/4))-(325*RES/2))/RES);
	else if (adc_pot <= 78*RES)
		value_B = 100;
	else
		value_B = ((((10000*RES)/21)-((100*adc_pot)/21))/RES);

	RGB_PWM(RGB_AZUL,value_B);
}


int main(void)
{
	BSP_Init();

	while(1)
	{
		adc_pot = (uint32_t)(BSP_GetBrightness()*RES);

		RGB_RED();
		RGB_GREEN();
		RGB_BLUE();
	}
}

