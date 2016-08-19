/*
 * bsp.h
 *
 *  Created on: 18 de ago. de 2016
 *      Author: Facundo Navarro
 */

#ifndef BSP_BSP_H_
#define BSP_BSP_H_

#include "stdint.h"

#define RGB_PORT 	GPIOB
#define ADC_PORT 	GPIOC


enum{
	RGB_ROJO = 0,
	RGB_VERDE,
	RGB_AZUL
}leds;


	void BSP_Init(void);

	void RGB_PWM(uint8_t led, uint8_t value);
	uint8_t BSP_GetBrightness(void);

#endif /* BSP_BSP_H_ */

