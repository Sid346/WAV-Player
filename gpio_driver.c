#include "gpio_driver.h"

void Gpio_Init(GPIO_TypeDef *Gpio_port,u32 Pin_Number,u32 Mode)
{ 
	if(Pin_Number<8)
	{
		Gpio_port->CRL &= ~(15<<4*Pin_Number);
		Gpio_port->CRL |= (Mode<<4*Pin_Number);
	}
	else
	{
		Gpio_port->CRH &= ~(15<<4*(Pin_Number-8));
		Gpio_port->CRH |= (Mode<<4*(Pin_Number-8));
	}
}

void Gpio_BitSet(GPIO_TypeDef *Gpio_port,u32 Pin_Number)	
{
	Gpio_port->BSRR	|= (1<<Pin_Number);
}
void Gpio_BitReset(GPIO_TypeDef *Gpio_port,u32 Pin_Number)
{
Gpio_port -> BRR  |= (1<<Pin_Number);
}

int Gpio_Read(GPIO_TypeDef *Gpio_port,u32 Pin_Number)
{
	u8 value = ((Gpio_port->IDR>>Pin_Number)& 0x00000001);
	return value ;
}

void GpioInterruptConfigure(u32 Pin_Number,edge EDGE)
{
 if(EDGE == RISING_EDGE)
	EXTI->RTSR|=1<<Pin_Number;
 if(EDGE == FALLING_EDGE)
	EXTI->FTSR|=1<<Pin_Number;
 if(EDGE == STATE_CHANGE)
 {
	 EXTI->RTSR|=1<<Pin_Number;
	 EXTI->FTSR|=1<<Pin_Number;
 }
	 
}
void GpioInterruptEnable(u32 Pin_Number,IRQn_Type number)
{
		EXTI->IMR|=1<<Pin_Number;
	  NVIC_EnableIRQ(number);
}
	
void GpioInterruptClear(u32 Pin_Number)
{
	EXTI->PR|=1<<Pin_Number;
}
void Toggle_Gpio(GPIO_TypeDef *Gpio_port,u32 Pin_Number)
{ 
	if(Gpio_Read(Gpio_port,Pin_Number))
		Gpio_BitReset(Gpio_port,Pin_Number);
	else
		Gpio_BitSet(Gpio_port,Pin_Number);
}