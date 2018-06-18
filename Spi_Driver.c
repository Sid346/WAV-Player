#include "Spi_driver.h"

u8 value;

static void Spi_Mode(SPI_TypeDef *Spi,Mode mode)
{ 
	if(mode==MASTER)
		Spi->CR1 |= SPI_CR1_MSTR;
	else if(mode==SLAVE)
		Spi->CR1 &= ~SPI_CR1_MSTR;
}
static void Spi_Phase_Polarity(SPI_TypeDef *Spi,u32 phase,u32 polarity)
{
	if(phase)
		Spi->CR1 |= SPI_CR1_CPHA;
	else
		Spi->CR1 &= ~SPI_CR1_CPHA;
	if(polarity)
		Spi->CR1 |= SPI_CR1_CPOL;
  else
    Spi->CR1 &= ~SPI_CR1_CPOL;
}	
static void Spi_DataSize_Direction(SPI_TypeDef *Spi,u32 Datasize,u32 Direction)
{
	if(Datasize)
		Spi->CR1 |= SPI_CR1_DFF;
	else
		Spi->CR1 &= ~SPI_CR1_DFF;
	if(Direction)
		Spi->CR1 |= SPI_CR1_LSBFIRST;
	else
		Spi->CR1 &= ~SPI_CR1_LSBFIRST;
}
void Spi_Baudrate(SPI_TypeDef *Spi,u16 Baudrate)
{
	Spi->CR1 |= Baudrate; 
}

static void Spi_SlaveSelect_Master(SPI_TypeDef *Spi,u32 SSM_ENABLE)
{
	if(SSM_ENABLE)
	{
		Spi->CR1 |= SPI_CR1_SSM;
		Spi->CR1 |= SPI_CR1_SSI;
	}
	else
		Spi->CR1 &= ~SPI_CR1_SSM;
}

static void Spi_SlaveSelect_Slave(SPI_TypeDef *Spi,u32 SSM_ENABLE)
{
	if(SSM_ENABLE)
	{
		Spi->CR1 |= SPI_CR1_SSM;
	}
	else
		Spi->CR1 &= ~SPI_CR1_SSM;
}	
static void Spi_Enable(SPI_TypeDef *Spi)
{
	Spi->CR1|= SPI_CR1_SPE;
}
void Spi_Disable(SPI_TypeDef *Spi)
{
	Spi->CR1 &= ~SPI_CR1_SPE;
}
void Spi_EnableTxeInterrupt(SPI_TypeDef *Spi)
{
	Spi->CR2 |=  SPI_CR2_TXEIE;              //0x04
}
void Spi_EnableRxeInterrupt(SPI_TypeDef *Spi)
{
	Spi->CR2 |=  SPI_CR2_RXNEIE;
	
}
void Spi_DisableTxeInterrupt(Spi_Init *Init)
{
	Init->Spi->CR2 &=  ~SPI_CR2_TXEIE;
	
	if (Init->Spiconfig.Mode && (Init->state != HAL_SPI_STATE_BUSY_RX))
		Init->state = HAL_SPI_STATE_READY;
}

u8 spi_is_bus_busy(SPI_TypeDef *Spi)
{
	if (Spi->SR & SPI_REG_SR_BUSY_FLAG )
	{
		return SPI_IS_BUSY;
	}else
	   return SPI_IS_NOT_BUSY;
}


void Spi_DisableRxeInterrupt(Spi_Init *Init)
{
	while(spi_is_bus_busy(Init->Spi));
	Init->Spi->CR2 &=  ~SPI_CR2_RXNEIE;
	Init->state = HAL_SPI_STATE_READY;
}

/**
	*	@brief API used to do master daata transmission
	*	@param *Init 	 : Pointer to Spi_Init structure
	*	@param *buffer : Pointer to Tx buffer
	*	@param *len		 : lenght of data to be transferred
  */

void Spi_MasterTx(Spi_Init *Init,u8 *buffer,u8 len)
{
	Init->Tx_BufferPtr = buffer;
	Init->TxBuffer_Size = len;
	Init->TxBuffer_Counter = len;
	
	Init->Rx_BufferPtr = 0;
	Init->RxBuffer_Counter = 0;
	
	Init->state = HAL_SPI_STATE_BUSY_TX;
	
	Spi_EnableTxeInterrupt(Init->Spi);
	Spi_Enable(Init->Spi);
}

void Spi_MasterRx(Spi_Init *Init,u8 *buffer,u8 len)
{ int val;
	u8 static dummy=0xff;
	Init->Tx_BufferPtr = &dummy;
	Init->TxBuffer_Size = len;
	Init->TxBuffer_Counter = len;
	
	Init->Rx_BufferPtr = buffer;
	Init->RxBuffer_Size = len;
	Init->RxBuffer_Counter = len;
	
	Init->state = HAL_SPI_STATE_BUSY_RX;
	//val = Init->Spi->DR;
	
	Spi_EnableTxeInterrupt(Init->Spi);
	Spi_EnableRxeInterrupt(Init->Spi);
	Spi_Enable(Init->Spi);
}

void Spi_SlaveTx(Spi_Init *Init,u8 *buffer,u8 len)
{
	Init->Tx_BufferPtr = buffer;
	Init->TxBuffer_Size = len;
	Init->TxBuffer_Counter = len;
	
	Init->Rx_BufferPtr = buffer;
	Init->RxBuffer_Size = len;
	Init->RxBuffer_Counter = len;
	
		Init->state = HAL_SPI_STATE_BUSY_TX;

	Spi_EnableTxeInterrupt(Init->Spi);
	Spi_EnableRxeInterrupt(Init->Spi);
	Spi_Enable(Init->Spi);
}

void Spi_SlaveRx(Spi_Init *Init,u8 *buffer,u8 len)
{
	Init->Rx_BufferPtr = buffer;
	Init->RxBuffer_Size = len;
	Init->RxBuffer_Counter = len;
	
	Init->state = HAL_SPI_STATE_BUSY_RX;

	Spi_EnableRxeInterrupt(Init->Spi);
		Spi_Enable(Init->Spi);
}
void Spi_Initialize(Spi_Init *Init)
{
	 Spi_Mode(Init->Spi,Init->Spiconfig.Mode);
	 Spi_Phase_Polarity(Init->Spi,Init->Spiconfig.CLKPhase,Init->Spiconfig.CLKPolarity);
	 Spi_DataSize_Direction(Init->Spi,Init->Spiconfig.DataSize,Init->Spiconfig.Direction);
	 Spi_Baudrate(Init->Spi,Init->Spiconfig.BaudRate);
	 if(Init->Spiconfig.Mode==MASTER)
	   Spi_SlaveSelect_Master(Init->Spi,Init->Spiconfig.SlaveSelect);
	 else
		 Spi_SlaveSelect_Slave(Init->Spi,Init->Spiconfig.SlaveSelect);
}
void Spi_Interrupt_Handler(Spi_Init *Init)
{
	u8 val1=0;
	u8 val2=0;
	val1 = (Init->Spi->CR2)& SPI_CR2_RXNEIE ;
	val2 = (Init->Spi->SR)& SPI_SR_RXNE  ;
	if(val1 != 0 && val2 != 0)
		{
		Spi_RxInterrupt_Handler(Init);
		return;
		}
	val1 = (Init->Spi->CR2)& SPI_CR2_TXEIE ;
	val2 = (Init->Spi->SR)& SPI_SR_TXE  ;
	if(val1 != 0 && val2 != 0)
	  {
		Spi_TxInterrupt_Handler(Init);
		return;
		}
}
		
void Spi_TxInterrupt_Handler(Spi_Init *Init)
{
	if(Init->Spiconfig.DataSize == _8BIT)
	{
		value = *(Init->Tx_BufferPtr);
		Init->Spi->DR = value;
		Init->TxBuffer_Counter--;
		Init->Tx_BufferPtr++;
	}
	if(Init->Spiconfig.DataSize == _16BIT)
	{
		Init->Spi->DR = *(Init->Tx_BufferPtr);
		Init->Tx_BufferPtr+=2;
		Init->TxBuffer_Counter-=2;
	}
	if(Init->TxBuffer_Counter==0)
	{
		Spi_DisableTxeInterrupt(Init);
	}
}     
void Spi_RxInterrupt_Handler(Spi_Init *Init)
{ 
	if(Init->Spiconfig.DataSize == _8BIT)
	{
	 *(Init->Rx_BufferPtr) = Init->Spi->DR;
		Init->RxBuffer_Counter--;
		Init->Rx_BufferPtr++;
	}
	if(Init->Spiconfig.DataSize == _16BIT)
	{ 
		*(Init->Rx_BufferPtr) = Init->Spi->DR;
		
		Init->Rx_BufferPtr+=2;
		Init->RxBuffer_Counter-=2;
	}
	if(Init->RxBuffer_Counter==0)
	{
		Spi_DisableRxeInterrupt(Init);
		
	}
}


	