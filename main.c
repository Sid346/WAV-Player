#include "stm32f10x.h"
#include "gpio_driver.h"
#include "Spi_driver.h"
#include "ff.h"
#include "xprintf.h"
#include "string.h"
#include "diskio.h"

void timer(void);
void pwmtimer(void);
void Samplingtimer(void);
char itoa(int v, char *buff, int radix_base);
char strrev(char *str);
extern void disk_timerproc (void);
void adc(void);

BYTE Buff[4096] __attribute__ ((aligned (4))) ;	/* Working buffer */
FATFS FatFs;				/* File system object for each logical drive */
FIL File;				/* File objects */
DIR Dir;					/* Directory object */
uint16_t b[1024];


	FRESULT fr;
		FATFS fs;
		FIL fil;
		UINT a,i=0,j=0,k=0;
		uint16_t data;
		char read[4];
		char zero[]= "0";
		
struct header
{
    char fileformat[4];
    int file_size;
    char subformat[4];
    char subformat_id[4];
    int chunk_bits;     //16or18or40 due to pcm it is 16 here
    short int audio_format;     //little or big endian
    short int num_channels;     //2 here for left and right
    int sample_rate;			// sample_rate denotes the sampling rate.
    int byte_rate;           //bytes  per second
    short int bytes_per_frame;
    short int bits_per_sample;
    char data_id[4];    //"data" written in ascii
    int data_size;
}head;



int main()
{ 	
		timer();
		//adc();
		
		TIM_SetCompare2(TIM2, 0);
	  GPIOC_ClockEnable();
		Gpio_Init(GPIOC,15,PushPullOutput_Fast);	
	
		const char newline[] = "\t";
		/* Open or create a log file and ready to append */
		f_mount(&fs, "", 0);
		fr = f_open(&fil, "fly.wav",FA_READ);
		if (fr != FR_OK) return 1;
		//Samplingtimer();
	f_read(&fil,&head,sizeof head,&a);
		if (fr != FR_OK) return 1; 
		if(head.data_id[0]!='L')return 1;
		
	while(read[0]!='d')
	{
			f_read(&fil,read,sizeof read,&a);
	}
	pwmtimer();
while(i < head.file_size)
	{
     if(i!=j)
		 {
			f_read(&fil,&data,sizeof data,&a);
			TIM_SetCompare2(TIM2,data/66);
			 j=i;
			 //Toggle_Gpio(GPIOC,15);
		 }			 
			 
}

  
	f_close(&fil);
	f_mount(0, "", 0);
	Gpio_BitSet(GPIOC,15);
TIM_Cmd(TIM4, DISABLE);
TIM_Cmd(TIM2, DISABLE);
	return 0;

}
void TIM2_IRQHandler()
		{ 
	    if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
		{
	    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
			
			
			i++;
			
		}
		}
void TIM3_IRQHandler()
		{ 
	    if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)
		{
	    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
			ADC_SoftwareStartConvCmd(ADC1, ENABLE);
			
			b[i]=ADC_GetConversionValue(ADC1);
			ADC_SoftwareStartConvCmd(ADC1, DISABLE);
			
			i++;
			if(i>1023)i=0;
		}
		}
void Samplingtimer(void)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_TimeBaseInitTypeDef Sampling_timer;
	TIM_TimeBaseStructInit(&Sampling_timer);
	
	Sampling_timer.TIM_Period=SystemCoreClock/8000;
	
	TIM_TimeBaseInit(TIM3,&Sampling_timer);
	
	TIM_Cmd(TIM3, ENABLE);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0e;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0e;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}	
	
void pwmtimer(void)
{
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
TIM_OCInitTypeDef TIM_OCInitStructure;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
TIM_TimeBaseStructure.TIM_Prescaler = SystemCoreClock/41100000; // 0..239
//TIM_TimeBaseStructure.TIM_Period = 896; // 0..999
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
TIM_OCStructInit(&TIM_OCInitStructure);
TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
TIM_OC2Init(TIM2, &TIM_OCInitStructure);
TIM_Cmd(TIM2, ENABLE);
TIM_SetCompare2(TIM2, 0);

TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}
void adc(void)
{
	
	
RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
GPIO_InitTypeDef gpio;
GPIO_StructInit(&gpio);
gpio.GPIO_Mode=GPIO_Mode_AIN;
gpio.GPIO_Pin=GPIO_Pin_4;
gpio.GPIO_Speed=GPIO_Speed_50MHz;
GPIO_Init(GPIOA,&gpio);
	
ADC_InitTypeDef adc;
ADC_StructInit(&adc);
adc.ADC_Mode= ADC_Mode_Independent;
adc.ADC_ScanConvMode = DISABLE;
adc.ADC_ContinuousConvMode = ENABLE;
adc.ADC_ExternalTrigConv =ADC_ExternalTrigConv_None;
adc.ADC_DataAlign = ADC_DataAlign_Right;
adc.ADC_NbrOfChannel = 1;
ADC_Init(ADC1, &adc);
// Configure ADC_IN6
ADC_RegularChannelConfig(ADC1,ADC_Channel_4, 1,ADC_SampleTime_55Cycles5);
// Enable ADC
ADC_Cmd(ADC1, ENABLE);
/* Enable ADC1 reset calibaration register */
  ADC_ResetCalibration(ADC1);
  //Check the end of ADC1 reset calibration register
  while(ADC_GetResetCalibrationStatus(ADC1));
   //Start ADC1 calibaration
  ADC_StartCalibration(ADC1);
   //Check the end of ADC1 calibration
  while(ADC_GetCalibrationStatus(ADC1));
}


void TIM4_IRQHandler()
		{
			if (TIM_GetITStatus(TIM4,TIM_IT_Update)!=RESET)
		{
	        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
					disk_timerproc();
		}
	}

void timer(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;																													
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);											
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = SystemCoreClock/990 ; 					// 0..239
	TIM_TimeBaseStructure.TIM_Period = 40; 																	// 0..1023...dutycycle
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
																															
	TIM_Cmd(TIM4, ENABLE);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);																	//interrupt config at update
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

char itoa(int v, char *buff, int radix_base){
    static char table[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char *p=buff;
    unsigned int n = (v < 0 && radix_base == 10)? -v : (unsigned int) v;
    while(n>=radix_base){
        *p++=table[n%radix_base];
        n/=radix_base;
    }
    *p++=table[n];
    if(v < 0 && radix_base == 10) *p++='-';
    *p='\0';
    return strrev(buff);
}
char strrev(char *str){
    char c, *front, *back;

    for(front=str,back=str+strlen(str)-1;front < back;front++,back--){
        c=*front;*front=*back;*back=c;
    }
    return *(str);
}

/*if(i!=j){
		  //itoa(b,data, 10);
			//f_write(&fil,newline, sizeof newline-1,&a);
		int diff,loop =i-j;	
		for(diff=0;diff<loop;diff++)
		{
			if(b[diff]>930){
				b[diff]-=930;
			itoa(b[diff],data,10);
			f_write(&fil,data, sizeof data,&a);
				if (fr != FR_OK) return 1;
			}
	else
		f_write(&fil,zero, sizeof zero,&a);	
		if (fr != FR_OK) return 1;		
	  }		
			k++;
		
			if(k>999)
				break;
		
		i=0;
		j=i;	
		
	}*/