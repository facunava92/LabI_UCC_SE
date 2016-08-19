/*
 * bsp.c
 *
 *  Created on: 18 de ago. de 2016
 *      Author: Facundo Navarro
 */

#include "bsp.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

extern void delay_ms(void);

uint32_t* const leds_pwm[] = { &TIM3->CCR1, &TIM3->CCR2, &TIM3->CCR3};

TIM_HandleTypeDef TIM2_Handle;
TIM_HandleTypeDef TIM3_Handle;

void CLOCK_CONTROL_REGISTER_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;

	__PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	// Configuracion de CLOCK a 168 MHZ

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 336;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}

void ADC_Config(void)
{
	//CONFIGURACION DEL PIN DE ADC

	__GPIOC_CLK_ENABLE();

	GPIO_InitTypeDef GPIOC_Init;

	GPIOC_Init.Mode = GPIO_MODE_ANALOG;
	GPIOC_Init.Pull = GPIO_NOPULL;
	GPIOC_Init.Speed = GPIO_SPEED_FAST;
	GPIOC_Init.Pin = GPIO_PIN_2;
	HAL_GPIO_Init(ADC_PORT, &GPIOC_Init);

//CONFIGURACION ADC



//SETEO DE LAS PROPIEDADES DEL CONFIG TYPEDEF

	 ADC_InitTypeDef ADC_Init;
	 ADC_Init.Resolution = ;
}

void TIMER_Init(void)
{
	__TIM2_CLK_ENABLE();

	TIM2_Handle.Instance = TIM2;
	TIM2_Handle.Init.Period = 1000 - 1;
	TIM2_Handle.Init.Prescaler = 84 - 1;
	TIM2_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	TIM2_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;

	HAL_TIM_Base_Init(&TIM2_Handle);
	HAL_TIM_Base_Start_IT(&TIM2_Handle);

	HAL_NVIC_SetPriority(TIM2_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

void PWM_Timer(void)
{
	__TIM3_CLK_ENABLE();
	TIM_MasterConfigTypeDef TIM_MasterConfig;
	TIM_OC_InitTypeDef TIM_OC_Init;

	TIM3_Handle.Instance = TIM3;
	TIM3_Handle.Init.Prescaler = 84 - 1;

	TIM3_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	TIM3_Handle.Init.Period = 1500;
	TIM3_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV2;
	HAL_TIM_PWM_Init(&TIM3_Handle);

	TIM_MasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	TIM_MasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	HAL_TIMEx_MasterConfigSynchronization(&TIM3_Handle, &TIM_MasterConfig);

	TIM_OC_Init.OCMode = TIM_OCMODE_PWM2;
	TIM_OC_Init.Pulse = 0;
	TIM_OC_Init.OCPolarity = TIM_OCPOLARITY_LOW;
	TIM_OC_Init.OCFastMode = TIM_OCFAST_ENABLE;

	HAL_TIM_PWM_ConfigChannel(&TIM3_Handle, &TIM_OC_Init, TIM_CHANNEL_1);
	HAL_TIM_PWM_ConfigChannel(&TIM3_Handle, &TIM_OC_Init, TIM_CHANNEL_2);
	HAL_TIM_PWM_ConfigChannel(&TIM3_Handle, &TIM_OC_Init, TIM_CHANNEL_3);

	HAL_TIM_PWM_Start(&TIM3_Handle, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&TIM3_Handle, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&TIM3_Handle, TIM_CHANNEL_3);
}

void GPIO_RGB_Config(void)
{
	__GPIOB_CLK_ENABLE();

	GPIO_InitTypeDef GPIOB_Init;

	GPIOB_Init.Mode = GPIO_MODE_AF_PP;
	GPIOB_Init.Pull = GPIO_NOPULL;
	GPIOB_Init.Speed = GPIO_SPEED_FAST;
	GPIOB_Init.Alternate = GPIO_AF2_TIM3 ;
	GPIOB_Init.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4;
	HAL_GPIO_Init(RGB_PORT, &GPIOB_Init);
}



void RGB_PWM(uint16_t led) {
	HAL_GPIO_WritePin(RGB_PORT, led, GPIO_PIN_RESET );
}


void TIM2_IRQHandler(void) {

	__HAL_TIM_CLEAR_FLAG(&TIM2_Handle, TIM_FLAG_UPDATE);
	delay_ms();
}

void BSP_Init(void)
{
	CLOCK_CONTROL_REGISTER_Config();
	TIMER_Init();
	GPIO_Config();
}



