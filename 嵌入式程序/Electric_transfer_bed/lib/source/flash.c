#include "common.h"


//-------------------------------��flashд������-----------------------
FLASH_Status FLASH_WriteData(uint32_t addr,uint16_t* data,uint16_t num)
{
	uint16_t temp = 0;
	FLASH_Status status = FLASH_COMPLETE;
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	for(temp=0;temp<num;temp++)
  {
		status = FLASH_ProgramHalfWord(addr,data[temp]);
		addr+=2;
	  if(status!=FLASH_COMPLETE)
			break;
	}
	FLASH_Lock();
	return status;
}

//-------------------------------��flashд������(32λд�룩-----------------------
FLASH_Status FLASH_WriteData_32(uint32_t addr,uint32_t* data,uint16_t num)
{
	uint16_t temp = 0;
	FLASH_Status status = FLASH_COMPLETE;
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	for(temp=0;temp<num;temp++)
  {
		status = FLASH_ProgramWord(addr,data[temp]);
		addr+=4;
	  if(status!=FLASH_COMPLETE)
			break;
	}
	FLASH_Lock();
	return status;
}
//-------------------------------����ҳ��flashд��ǰһ��Ҫ�ǲ���״̬��----------------------------	
FLASH_Status FLASH_Erase(uint32_t addr,uint16_t PageNum)
{
	uint16_t temp = 0;
	FLASH_Status status = FLASH_COMPLETE;
	FLASH_Unlock();
	for(temp=0;temp<PageNum;temp++)
	{
		status = FLASH_ErasePage(addr);
		addr+=PAGE_SIZE;
		if(status!=FLASH_COMPLETE)
			break;
	}
	FLASH_Lock();
	return status;
}
//-------------------------------��flash����-----------------------
void FLASH_Read(uint32_t addr,uint16_t* data,uint16_t num)
{
	uint16_t temp = 0;
	for(temp=0;temp<num;temp++)
  {
		data[temp] = *(__IO uint16_t *) addr;
		addr+=2;
	}
}
//-------------------------------��flash����(32λ��ȡ��-----------------------
void FLASH_Read_32(uint32_t addr,uint32_t* data,uint16_t num)
{
	uint16_t temp = 0;
	for(temp=0;temp<num;temp++)
  {
		data[temp] = *(__IO uint32_t *) addr;
		addr+=4;
	}
}
