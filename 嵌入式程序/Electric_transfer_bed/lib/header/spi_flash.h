#ifndef __RTC_H
#define __RTC_H
#endif
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x_conf.h"

extern uint16_t spi_flash_ErrorFlag;//spi_Flash�������
extern uint32_t SPI_FLASH_id;
//----------------------------��ʼ������---------------------------------------
//SPIģ��ż�ʱ�Ӷ���
#define FLASH_SPI SPI2
#define FLASH_SPI_CLK RCC_APB1Periph_SPI2
#define FLASH_SPI_CLK_INIT RCC_APB1PeriphClockCmd 
//SPI CS���Ŷ���
#define SPI_FLASH_CS_PIN GPIO_Pin_12
#define SPI_FLASH_CS_PORT GPIOB
#define SPI_FLASH_CS_GPIO_CLK RCC_APB2Periph_GPIOB
//SPI FLASH CLK���Ŷ���
#define SPI_FLASH_CLK_PIN GPIO_Pin_13
#define SPI_FLASH_CLK_PORT GPIOB
#define SPI_FLASH_CLK_GPIO_CLK RCC_APB2Periph_GPIOB
//SPI FLASH SO���Ŷ���
#define SPI_FLASH_SO_PIN GPIO_Pin_14
#define SPI_FLASH_SO_PORT GPIOB
#define SPI_FLASH_SO_GPIO_CLK RCC_APB2Periph_GPIOB
//SPI FLASH SI���Ŷ���
#define SPI_FLASH_SI_PIN GPIO_Pin_15
#define SPI_FLASH_SI_PORT GPIOB
#define SPI_FLASH_SI_GPIO_CLK RCC_APB2Periph_GPIOB

//CSƬѡ�ź���λ
#define SPI_FLASH_CS_HIGH() GPIO_SetBits(SPI_FLASH_CS_PORT,SPI_FLASH_CS_PIN)
#define SPI_FLASH_CS_LOW() GPIO_ResetBits(SPI_FLASH_CS_PORT,SPI_FLASH_CS_PIN)


//---------------SPI_Flash�����շ����ȴ�ʱ�䣬�������򷵻�ʧ��------------------
#define SPI_FLASH_WR_TIMEOUT 65535
#define SPI_FLASH_NORMAL 0x00
#define SPI_FLASH_TIME_OUT 0X01
#define SPI_BUSY 0X02


#define SPI_FLASH_ERASE_ERROR 0x04
#define SPI_FLASH_ERASE_COMPLETE 0x14
#define SPI_FLASH_WRITE_ERROR 0x05
#define SPI_FLASH_WRITE_COMPLETE 0x15
#define SPI_FLASH_READ_ERROR 0x06
#define SPI_FLASH_READ_COMPLETE 0x16



//-----------------------------SPI_FLASH busyλ----------------------------------
#define SPI_FLASH_BUSY 0x01

//--------------------------SPI_FLASH ����������----------------------------------
#define SPI_FLASH_STAT_ADDRESS ((uint32_t)0x00000000)
#define SPI_PAGE_SIZE   ((uint32_t)0x00000100)
#define SPI_FLASH_DATA_STAT_PAGE 0
#define SPI_FLASH_DATA_STAT_ADDRESS SPI_FLASH_STAT_ADDRESS+SPI_FLASH_DATA_STAT_PAGE * SPI_PAGE_SIZE

//���ݿռ�Ԥ����
#define TAST1_DATA_SIZE 1     //test ������Ҫռ��һҳ��256byte��������Ԥ���䴢��ռ�
#define TAST2_DATA_SIZE 1


//���ݴ����ַ����
#define TAST1_DATA_ADDRESS  SPI_FLASH_DATA_STAT_ADDRESS  
#define TAST2_DATA_ADDRESS TAST1_DATA_ADDRESS + TAST1_DATA_SIZE * SPI_PAGE_SIZE 


//-----------------------------SPI_FLASHоƬ����code--------------------------------
#define WRITE_ENABLE 0x06
#define WRITE_DISABLE 0X04
#define READ_STATUS_REGISTER_1 0X05
#define READ_STATUS_REGISTER_2 0X35
#define WRITE_STATUS_REGISTER 0X01
#define PAGE_PROGRAM 0X02
#define QUAD_PAGE_PROGRAM 0X32
#define BLOCK_ERASE_64KB 0XD8
#define BLOCK_ERASE_32KB 0X52
#define SECTOR_ERASE 0X20
#define READ_DATA 0X03
#define DEVICE_ID 0x9F

#define  DUMMY_BYTE 0xFE //��Ч������ڽ�������ʱ�����Բ���ʱ��
//-------------------------------------------------------------------
void SPI_FLASH_init(void);
uint32_t SPI_FLASH_ReadID(void);
void SPI_FLASH_WriteEnable(void);
void SPI_FLASH_WriteDisable(void);
void SPI_FLASH_WaitForWriteEnd(void);
uint16_t SPI_FLASH_SectorErase(uint32_t addr);
uint16_t SPI_FLASH_PageWrite(uint16_t* ptr,uint32_t addr,uint16_t num);
uint16_t SPI_FLASH_ReadData(uint16_t* ptr,uint32_t addr,uint16_t num);


uint8_t SPI_FLASH_SentByte(uint8_t data);
uint8_t SPI_FLASH_ReadByte(void);
 uint16_t SPI_FLASH_ErrorHandler(uint16_t Error_Index);
#ifdef __cplusplus
 }
#endif
