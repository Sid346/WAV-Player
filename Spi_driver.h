/**
  *************************************************************************************************************
* 
*	@file					Spi_Driver.h
*	@author				Siddhartha Singh
*	@date					17 February 2018
*	@brief				This file contains all the necessary Api functions which are needed for 
*           		using the Spi communication protocol in all available modes.It contains 
*								various Mcu specific macros as well as the functions with which a programmer 
*								can access whole of the functionality of the Spi peripherals for stm32f10x 
*								family of MCUs and this can also be used as a template for the development 
*								of SPI drivers for other MCUs.
*           		
*
*
*@attention 	This file is open source and hence any one whether an individual or a company is entitled
*             to use its functionalities.The Author will not be liable for any Direct,Indirect or consequential
*             damage due to this driver.
*
*
*  *****************************************************************************************************************
  */
	
#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H

/*************************************************   Mcu specific header file   *************************************/

#include "stm32f10x.h"

/**************************************************************************************************************************
*										                                                                                                      *
*																					 MCU specific macros and Bit definitions                                        *
*                                                                                                                         *
**************************************************************************************************************************/


/***************************************  Bit definition for SPI_CR1 register  ***********************************/

#define  SPI_CR1_CPHA                        ((uint16_t)0x0001)            /*!< Clock Phase */
#define  SPI_CR1_CPOL                        ((uint16_t)0x0002)            /*!< Clock Polarity */
#define  SPI_CR1_MSTR                        ((uint16_t)0x0004)            /*!< Master Selection */

#define  SPI_CR1_BR_256                      ((uint16_t)0x0038)            /*!< BR[2:0] bits (Baud Rate Control) */
#define  SPI_CR1_BR_4                        ((uint16_t)0x0008)            /*!< Bit 0 */
#define  SPI_CR1_BR_8                        ((uint16_t)0x0010)            /*!< Bit 1 */
#define  SPI_CR1_BR_16                       ((uint16_t)0x0018)            /*!< Bit 2 */
#define  SPI_CR1_BR_32                       ((uint16_t)0x0020)
#define  SPI_CR1_BR_64                       ((uint16_t)0x0028)
#define  SPI_CR1_BR_128                      ((uint16_t)0x0030)
#define  SPI_CR1_SPE                         ((uint16_t)0x0040)            /*!< SPI Enable */
#define  SPI_CR1_LSBFIRST                    ((uint16_t)0x0080)            /*!< Frame Format */
#define  SPI_CR1_SSI                         ((uint16_t)0x0100)            /*!< Internal slave select */
#define  SPI_CR1_SSM                         ((uint16_t)0x0200)            /*!< Software slave management */
#define  SPI_CR1_RXONLY                      ((uint16_t)0x0400)            /*!< Receive only */
#define  SPI_CR1_DFF                         ((uint16_t)0x0800)            /*!< Data Frame Format */
#define  SPI_CR1_CRCNEXT                     ((uint16_t)0x1000)            /*!< Transmit CRC next */
#define  SPI_CR1_CRCEN                       ((uint16_t)0x2000)            /*!< Hardware CRC calculation enable */
#define  SPI_CR1_BIDIOE                      ((uint16_t)0x4000)            /*!< Output enable in bidirectional mode */
#define  SPI_CR1_BIDIMODE                    ((uint16_t)0x8000)            /*!< Bidirectional data mode enable */
#define  SPI_CR1_2LINE_UNIMODE                        0
/***************************************  Bit definition for SPI_CR2 register  *************************************/

#define  SPI_CR2_RXDMAEN                     ((uint8_t)0x01)               /*!< Rx Buffer DMA Enable */
#define  SPI_CR2_TXDMAEN                     ((uint8_t)0x02)               /*!< Tx Buffer DMA Enable */
#define  SPI_CR2_SSOE                        ((uint8_t)0x04)               /*!< SS Output Enable */
#define  SPI_CR2_ERRIE                       ((uint8_t)0x20)               /*!< Error Interrupt Enable */
#define  SPI_CR2_RXNEIE                      ((uint8_t)0x40)               /*!< RX buffer Not Empty Interrupt Enable */
#define  SPI_CR2_TXEIE                       ((uint8_t)0x80)               /*!< Tx buffer Empty Interrupt Enable */

/***************************************  Bit definition for SPI_SR register  **************************************/

#define  SPI_SR_RXNE                         ((uint8_t)0x01)               /*!< Receive buffer Not Empty */
#define  SPI_SR_TXE                          ((uint8_t)0x02)               /*!< Transmit buffer Empty */
#define  SPI_SR_CHSIDE                       ((uint8_t)0x04)               /*!< Channel side */
#define  SPI_SR_UDR                          ((uint8_t)0x08)               /*!< Underrun flag */
#define  SPI_SR_CRCERR                       ((uint8_t)0x10)               /*!< CRC Error flag */
#define  SPI_SR_MODF                         ((uint8_t)0x20)               /*!< Mode fault */
#define  SPI_SR_OVR                          ((uint8_t)0x40)               /*!< Overrun flag */
#define  SPI_SR_BSY                          ((uint8_t)0x80)               /*!< Busy flag */
#define SPI_IS_BUSY 																			1 
#define SPI_IS_NOT_BUSY 																  0
#define SPI_REG_SR_BUSY_FLAG        				 ((uint16_t)1 << 7)

/********************************************** Spi clock enable Macros *********************************************/

#define  SPI3_CLOCK_ENABLE()                 (RCC->APB1ENR |= ( 1<<19))
#define  SPI1_CLOCK_ENABLE()                 (RCC->APB2ENR |= ( 1<<12))
#define  SPI2_CLOCK_ENABLE()                 (RCC->APB1ENR |= ( 1<<14))

 
 #define PERIPH_BASE           ((uint32_t)0x40000000) 
 #define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000)
 #define SPI1_BASE             (APB2PERIPH_BASE + 0x3000)
 #define SPI2_BASE             (APB1PERIPH_BASE + 0x3800)
 #define APB1PERIPH_BASE       PERIPH_BASE
/**************************************************************************************************************************
*										                       															                                                	*
*											                   MCU specific Data Structures For Spi 																						*
*                                                                                                                         *
**************************************************************************************************************************/
typedef struct
{
	u32 Mode;
	u32 Direction;
	u32 DataSize;
	u32 CLKPolarity;
	u32 SlaveSelect;
	u32 CLKPhase;
	u32 BaudRate;
	u32 FirstBit;
}Spi_configure;
	
typedef enum
{
  HAL_SPI_STATE_RESET      = 0x00,  /*  SPI not yet initialized or disabled                */
  HAL_SPI_STATE_READY      = 0x01,  /*  SPI initialized and ready for use                  */
  HAL_SPI_STATE_BUSY       = 0x02,  /*  SPI process is ongoing                             */
  HAL_SPI_STATE_BUSY_TX    = 0x12,  /*  Data Transmission process is ongoing               */
  HAL_SPI_STATE_BUSY_RX    = 0x22,  /*  Data Reception process is ongoing                  */
  HAL_SPI_STATE_BUSY_TX_RX = 0x32,  /*  Data Transmission and Reception process is ongoing */
  HAL_SPI_STATE_ERROR      = 0x03   /*  SPI error state                                    */
}SPI_STATE;


typedef struct
{
	SPI_TypeDef *Spi;
	Spi_configure Spiconfig;
	u8 *Tx_BufferPtr;
	u16 TxBuffer_Size;
	u16 TxBuffer_Counter;
  u8 *Rx_BufferPtr;
	u16 RxBuffer_Size;
	u16 RxBuffer_Counter;
	SPI_STATE state;
}Spi_Init;

typedef enum
{
	MASTER=1,
	SLAVE=0
}Mode;
typedef enum
{
	_8BIT=0,
	_16BIT=1
	
}BUFFER;	
/**************************************************************************************************************************
*										                       															                                                	*
*											                             Driver APIs For Spi 																						        *
*                                                                                                                         *
**************************************************************************************************************************/

/*static void Spi_Mode(SPI_TypeDef *Spi,Mode mode);
static void Spi_Phase_Polarity(SPI_TypeDef *Spi,u32 phase,u32 polarity);
static void Spi_Baudrate(SPI_TypeDef *Spi,u16 Baudrate);
static void Spi_DataSize_Direction(SPI_TypeDef *Spi,u32 Datasize,u32 Direction);
static void Spi_SlaveSelect_Master(SPI_TypeDef *Spi,u32 SSM_ENABLE);
static void Spi_SlaveSelect_Slave(SPI_TypeDef *Spi,u32 SSM_ENABLE);
static void Spi_Enable(SPI_TypeDef *Spi);*/
void Spi_Disable(SPI_TypeDef *Spi);
void Spi_Baudrate(SPI_TypeDef *Spi,u16 Baudrate);
void Spi_EnableTxeInterrupt(SPI_TypeDef *Spi);
void Spi_DisableTxeInterrupt(Spi_Init *Init);
void Spi_EnableRxeInterrupt(SPI_TypeDef *Spi);
void Spi_DisableRxeInterrupt(Spi_Init *Init);
void Spi_MasterTx(Spi_Init *Init,u8 *buffer,u8 len);
void Spi_MasterRx(Spi_Init *Init,u8 *buffer,u8 len);
void Spi_SlaveTx(Spi_Init *Init,u8 *buffer,u8 len);
void Spi_SlaveRx(Spi_Init *Init,u8 *buffer,u8 len);
void Spi_Initialize(Spi_Init *Init);
void Spi_RxInterrupt_Handler(Spi_Init *Init);
void Spi_TxInterrupt_Handler(Spi_Init *Init);
void Spi_Interrupt_Handler(Spi_Init *Init);
#endif
