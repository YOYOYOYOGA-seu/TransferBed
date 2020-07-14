#include "common.h"

uint16_t spi_flash_ErrorFlag = SPI_FLASH_NORMAL;// spi_flash�����
uint32_t SPI_FLASH_id = 0;//spi_flash оƬ����
//--------------------spi_flash��ʼ��-----------------------
void SPI_FLASH_init(void)
{
	RCC_APB2PeriphClockCmd(SPI_FLASH_CS_GPIO_CLK|SPI_FLASH_CLK_GPIO_CLK|
													SPI_FLASH_SO_GPIO_CLK|SPI_FLASH_SI_GPIO_CLK,ENABLE);
	FLASH_SPI_CLK_INIT(FLASH_SPI_CLK,ENABLE);
	GPIO_InitTypeDef SPI_FlASH_GPIO_init;
	// CLK,SI,SO����GPIO��ʼ��
	SPI_FlASH_GPIO_init.GPIO_Mode = GPIO_Mode_AF_PP;
	SPI_FlASH_GPIO_init.GPIO_Speed = GPIO_Speed_50MHz;
	SPI_FlASH_GPIO_init.GPIO_Pin = (SPI_FLASH_CLK_PIN|SPI_FLASH_SI_PIN|SPI_FLASH_SO_PIN);
	GPIO_Init(SPI_FLASH_CLK_PORT,&SPI_FlASH_GPIO_init);
	
	//CS��������Ϊ��ͨGPIO���������SPI��NSS
	SPI_FlASH_GPIO_init.GPIO_Mode = GPIO_Mode_Out_PP;
	SPI_FlASH_GPIO_init.GPIO_Pin = SPI_FLASH_CS_PIN;
	GPIO_Init(SPI_FLASH_CS_PORT,&SPI_FlASH_GPIO_init);	
	
	SPI_FLASH_CS_HIGH();
	//SPI ����
	SPI_InitTypeDef SPI_FlASH_SPI_init;
	SPI_FlASH_SPI_init.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_FlASH_SPI_init.SPI_Mode = SPI_Mode_Master;
	SPI_FlASH_SPI_init.SPI_DataSize = SPI_DataSize_8b;
	SPI_FlASH_SPI_init.SPI_CPOL = SPI_CPOL_High;
	SPI_FlASH_SPI_init.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_FlASH_SPI_init.SPI_NSS = SPI_NSS_Soft;
	SPI_FlASH_SPI_init.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_FlASH_SPI_init.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_FlASH_SPI_init.SPI_CRCPolynomial = 7;
	SPI_Init(FLASH_SPI,&SPI_FlASH_SPI_init);
	
	SPI_Cmd(FLASH_SPI,ENABLE);
}


//--------------------spi_flash��������---------
//return  ���ܵ����ݻ������
uint8_t SPI_FLASH_SentByte(uint8_t data)
{
	uint16_t spi_flash_timeout = SPI_FLASH_WR_TIMEOUT;
	while(SPI_I2S_GetFlagStatus(FLASH_SPI,SPI_I2S_FLAG_TXE)==RESET)
	{
		if((spi_flash_timeout--)<=0)
			return SPI_FLASH_ErrorHandler(SPI_BUSY);
	}
	
	SPI_I2S_SendData(FLASH_SPI,data);
	spi_flash_timeout = SPI_FLASH_WR_TIMEOUT;
	while(SPI_I2S_GetFlagStatus(FLASH_SPI,SPI_I2S_FLAG_TXE)==RESET)
	{
		if((spi_flash_timeout--)<=0)
			return SPI_FLASH_ErrorHandler(SPI_BUSY);
	}
	
	return SPI_I2S_ReceiveData(FLASH_SPI);
}



//---------------������-------------
/*����SPIЭ�飬����������������ʱ��SCLK���ڿ���״̬�����ָߣ��ף���ƽ��
�����޷��Ӵӻ��յ����ݣ���Ҫд��Ч������������ʱ�ӣ��Ӷ����ܴӻ����ݣ�1byte����8�������ʱ�ӣ�
��SPI���������շ���ͬ����
*/
uint8_t SPI_FLASH_ReadByte(void)
{
	return (SPI_FLASH_SentByte(DUMMY_BYTE));
}



//---------------дʹ��-------------
void SPI_FLASH_WriteEnable(void)
{
	SPI_FLASH_CS_LOW();
	SPI_FLASH_SentByte(WRITE_ENABLE);
	SPI_FLASH_CS_HIGH();
}
//---------------�ȴ�оƬ��һ���������-------------
void SPI_FLASH_WaitForWriteEnd(void)
{
	uint8_t flag ;
	uint16_t spi_flash_timeout = SPI_FLASH_WR_TIMEOUT;
	SPI_FLASH_CS_LOW();
	flag = SPI_FLASH_SentByte(READ_STATUS_REGISTER_1);
	while((flag&SPI_FLASH_BUSY) == 1)
	{
		flag = SPI_FLASH_SentByte(DUMMY_BYTE);
		if((spi_flash_timeout--)<=0)
		{
			SPI_FLASH_ErrorHandler(SPI_FLASH_TIME_OUT);
			return;
		}
	}
	SPI_FLASH_CS_HIGH();
}

//---------------��������-------------
uint16_t SPI_FLASH_SectorErase(uint32_t addr)
{
	spi_flash_ErrorFlag = SPI_FLASH_NORMAL;
	SPI_FLASH_WriteEnable();
	SPI_FLASH_WaitForWriteEnd();
	if(spi_flash_ErrorFlag != SPI_FLASH_NORMAL)
	{
		return SPI_FLASH_ErrorHandler(SPI_FLASH_ERASE_ERROR);
	}
	SPI_FLASH_CS_LOW();
	SPI_FLASH_SentByte(SECTOR_ERASE);
	SPI_FLASH_SentByte((uint8_t)((addr&0xFF0000)>>16));
	SPI_FLASH_SentByte((uint8_t)((addr&0xFF00)>>8));
	SPI_FLASH_SentByte((uint8_t)(addr&0xFF));
	SPI_FLASH_CS_HIGH();
	SPI_FLASH_WaitForWriteEnd();
	if(spi_flash_ErrorFlag != SPI_FLASH_NORMAL)
	{
		return SPI_FLASH_ErrorHandler(SPI_FLASH_ERASE_ERROR);
	}
	return SPI_FLASH_ErrorHandler(SPI_FLASH_ERASE_COMPLETE);
}

//---------------��ҳд��-------------
uint16_t SPI_FLASH_PageWrite(uint16_t* ptr,uint32_t addr,uint16_t num)
{
	spi_flash_ErrorFlag = SPI_FLASH_NORMAL;
	uint16_t i=0;
	SPI_FLASH_WriteEnable();
	SPI_FLASH_CS_LOW();
	SPI_FLASH_SentByte(PAGE_PROGRAM);
	SPI_FLASH_SentByte((uint8_t)((addr&0xFF0000)>>16));
	SPI_FLASH_SentByte((uint8_t)((addr&0xFF00)>>8));
	SPI_FLASH_SentByte((uint8_t)(addr&0xFF));
	if(num>SPI_PAGE_SIZE/2)
		num = SPI_PAGE_SIZE/2;
	for(i=0;i<num;i++)
	{
		SPI_FLASH_SentByte((uint8_t)((ptr[i]&0xFF00)>>8));
		SPI_FLASH_SentByte((uint8_t)(ptr[i]&0xFF));
		if(spi_flash_ErrorFlag != SPI_FLASH_NORMAL)
		{
			return SPI_FLASH_ErrorHandler(SPI_FLASH_WRITE_ERROR);
		}
	}
	SPI_FLASH_CS_HIGH();
	SPI_FLASH_WaitForWriteEnd();
	return SPI_FLASH_ErrorHandler(SPI_FLASH_WRITE_COMPLETE);
	
}

//------------------------��spi_flash������----------------------
uint16_t SPI_FLASH_ReadData(uint16_t* ptr,uint32_t addr,uint16_t num)
{
	spi_flash_ErrorFlag = SPI_FLASH_NORMAL;
	uint8_t i;
	SPI_FLASH_CS_LOW();
	SPI_FLASH_SentByte(READ_DATA);
	SPI_FLASH_SentByte((uint8_t)((addr&0xFF0000)>>16));
	SPI_FLASH_SentByte((uint8_t)((addr&0xFF00)>>8));
	SPI_FLASH_SentByte((uint8_t)(addr&0xFF));
	for(i=0;i<num;i++)
	{
		ptr[i]=((uint16_t)SPI_FLASH_SentByte(DUMMY_BYTE)<<8);
		ptr[i]|=(uint16_t)SPI_FLASH_SentByte(DUMMY_BYTE);
		if(spi_flash_ErrorFlag != SPI_FLASH_NORMAL)
		{
			return SPI_FLASH_ErrorHandler(SPI_FLASH_READ_ERROR);
		}
	}
	SPI_FLASH_CS_HIGH();
		return SPI_FLASH_ErrorHandler(SPI_FLASH_READ_COMPLETE);
}

//----------------------------��ȡflashоƬID-----------------------
uint32_t SPI_FLASH_ReadID(void)
{
	spi_flash_ErrorFlag = SPI_FLASH_NORMAL;
	uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0; 
	/* ��ʼͨѶ��CS�͵�ƽ */
	SPI_FLASH_CS_LOW();

	/* ����JEDECָ���ȡID */
	SPI_FLASH_SentByte(DEVICE_ID);

	/* ��ȡһ���ֽ����� */
	Temp0 = SPI_FLASH_SentByte(DUMMY_BYTE);

	/* ��ȡһ���ֽ����� */
	Temp1 = SPI_FLASH_SentByte(DUMMY_BYTE);

	/* ��ȡһ���ֽ����� */
	Temp2 = SPI_FLASH_SentByte(DUMMY_BYTE);

	/* ֹͣͨѶ��CS�ߵ�ƽ */
	SPI_FLASH_CS_HIGH();

	/*�����������������Ϊ�����ķ���ֵ*/
	Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;

	return Temp;
} 

 
 
 uint16_t SPI_FLASH_ErrorHandler(uint16_t Error_Index)
 {
	 spi_flash_ErrorFlag = Error_Index;
	 return spi_flash_ErrorFlag;
 }
 