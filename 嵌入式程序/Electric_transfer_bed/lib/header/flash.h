#ifndef __FLASH_H
#define __FLASH_H
#endif
#ifdef __cplusplus
 extern "C" {
#endif
	 
#include "stm32f10x_conf.h"

#define FLASH_STAT_ADDRESS ((uint32_t)0x08000000)
#define PAGE_SIZE   ((uint32_t)0x00000800)
#define DATA_STAT_PAGE 128
#define DATA_STAT_ADDRESS FLASH_STAT_ADDRESS+DATA_STAT_PAGE * PAGE_SIZE

//���ݿռ�Ԥ����
#define TAST_DATA_SIZE 1     //test ������Ҫռ��һҳ��1kb��������Ԥ���䴢��ռ�
#define TIME_DATA_SIZE 1
#define TS_ADJUSTING_DATA_SIZE 1
#define BED_SPEED_DATA_SIZE  1


//���ݴ����ַ����
#define TAST_DATA_ADDRESS  DATA_STAT_ADDRESS  
#define TIME_DATA_ADDRESS TAST_DATA_ADDRESS + TAST_DATA_SIZE * PAGE_SIZE 
#define TS_ADJUSTING_DATA_ADDRESS TIME_DATA_ADDRESS + TIME_DATA_SIZE * PAGE_SIZE 
#define BED_SPEED_DATA_ADDRESS TS_ADJUSTING_DATA_ADDRESS + TS_ADJUSTING_DATA_SIZE * PAGE_SIZE 

FLASH_Status FLASH_WriteData(uint32_t addr,uint16_t* data,uint16_t num);
FLASH_Status FLASH_WriteData_32(uint32_t addr,uint32_t* data,uint16_t num);
FLASH_Status FLASH_Erase(uint32_t addr,uint16_t PageNum);
void FLASH_Read(uint32_t addr,uint16_t* data,uint16_t num);
void FLASH_Read_32(uint32_t addr,uint32_t* data,uint16_t num);

#ifdef __cplusplus
 }
#endif

