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

#define RGB_ROJO	 	(uint16_t)0x0001U
#define RGB_VERDE	 	(uint16_t)0x0002U
#define RGB_AZUL	 	(uint16_t)0x0010U
#define RGB_LEDS		RGB_ROJO | RGB_VERDE | RGB_AZUL


	void BSP_Init(void);

	void RGB_ON(uint16_t led);
	void RGB_OFF(uint16_t led);
	void RGB_PWM(uint8_t led, uint8_t value);
	uint8_t BSP_GetBrightness(void);

#endif /* BSP_BSP_H_ */

