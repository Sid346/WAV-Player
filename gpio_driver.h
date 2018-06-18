/**
  *****************************************************************************************************************
* @file   		gpio_driver.h
* @author			Siddhartha Singh
* @version  	1.0
* @date				2 February 2018
* @brief    	Gpio peripheral interface Header file.
*							This file contains all the necessary Api functions which are needed  for 
*           	using the gpio ports in all available modes.It contains various Mcu specific macros 
*           	as well as the functions with which a programmer can access wole of the functionality 
*           	of the Gpio ports.
*
*
* @attention 	This file is open source and hence any one whether an individual or a company is entitled
*             to use its functionalities.The Author will not be liable for any Direct,Indirect or consequential
*             damage due to this driver.
*
*
*
*  *****************************************************************************************************************
  */


#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H


/*************************************************   Mcu specific header file   *************************************/

#include "stm32f10x.h"

/********************************************  MCU specific macros and Bit definitions  *******************************/


/********************************************  Bit definition for CRL & CRH Registers  *******************************/
#define AnalogInputMode       		((u32) 0x00) 
#define FloatingInputMode     		((u32) 0x04)
#define InputPull_UpDown     		  ((u32) 0x08)
#define PushPullOutput_Slow   		((u32) 0x02)
#define PushPullOutput_Medium 		((u32) 0x01)
#define PushPullOutput_Fast   		((u32) 0x03)
#define OpenDrainOutput_Slow  		((u32) 0x06)
#define OpenDrainOutput_Medium		((u32) 0x05)
#define OpenDrainOutput_Fast   		((u32) 0x07)
#define AFOutputOpenDrain_Slow  	((u32) 0x0E)
#define AFOutputOpenDrain_Medium	((u32) 0x0D)
#define AFOutputOpenDrain_Fast  	((u32) 0x0F)
#define AFOutputPushPull_Slow  		((u32) 0x0A)
#define AFOutputPushPull_Medium  	((u32) 0x09)
#define AFOutputPushPull_Fast  		((u32) 0x0B)

/********************************************  Macros for Enabling clock for Gpios  *************************************/

#define GPIOA_ClockEnable()       (RCC->APB2ENR |= ( 1 << 2 ) )
#define GPIOB_ClockEnable()       (RCC->APB2ENR |= ( 1 << 3 ) )
#define GPIOC_ClockEnable()       (RCC->APB2ENR |= ( 1 << 4 ) )
#define AFIO_ClockEnable()        (RCC->APB2ENR |= ( 1 << 0 ) )

/********************************************  Structures for Gpio Configuration  **************************************/
typedef enum 
{
 RISING_EDGE,
 FALLING_EDGE,
 STATE_CHANGE
}edge;	


/**************************************************** Gpio Api's *********************************************************/


void Gpio_Init(GPIO_TypeDef *Gpio_port,u32 Pin_Number,u32 Mode);
void Gpio_BitSet(GPIO_TypeDef *Gpio_port,u32 Pin_Number);
void Gpio_BitReset(GPIO_TypeDef *Gpio_port,u32 Pin_Number);
int Gpio_Read(GPIO_TypeDef *Gpio_port,u32 Pin_Number);
void GpioInterruptConfigure(u32 Pin_Number,edge EDGE);
void GpioInterruptClear(u32 Pin_Number);
void GpioInterruptEnable(u32 Pin_Number,IRQn_Type number);
void Toggle_Gpio(GPIO_TypeDef *Gpio_port,u32 Pin_Number);












#endif

