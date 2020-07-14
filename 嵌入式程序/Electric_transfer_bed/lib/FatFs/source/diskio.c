/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2016        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
#include "rtc.h"
/* Definitions of physical drive number for each drive */
#define SDIO_SD		0	/* Example: Map Ramdisk to physical drive 0 */
#define DEV_MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
//#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	//DSTATUS stat;
//	int result;

	switch (pdrv) {
	case SDIO_SD :	

		// translate the reslut code here

		return RES_OK;

	case DEV_MMC :
		// translate the reslut code here

		return RES_OK;


	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
//	DSTATUS stat;
	//int result;

	switch (pdrv) {
	case SDIO_SD :
		if(SD_Init()!=0)
			return RES_ERROR;
		else
			return RES_OK;
		// translate the reslut code here


	case DEV_MMC :

		// translate the reslut code here

		return 0;

	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	switch (pdrv) 
	{

	case SDIO_SD :
		if(SD_ReadDisk((u8*)buff, sector, count)!=0)
			return RES_ERROR;
		else
			return RES_OK;
		
	case DEV_MMC :
		return RES_OK;

	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	switch (pdrv) 
	{
		
	case SDIO_SD :
		if(SD_WriteDisk((u8*)buff, sector, count)!=0)
			return RES_ERROR;
		else
			return RES_OK;


	case DEV_MMC :
		return RES_OK;

	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	if(pdrv==SDIO_SD)
	{
		switch (cmd)
		{
			case CTRL_SYNC:	    
 		        res = RES_OK;
		        break;	 
		    case GET_SECTOR_SIZE:
		        *(WORD*)buff = 512;
		        res = RES_OK;
		        break;	 
		    case GET_BLOCK_SIZE:
		        *(WORD*)buff = 8;
		        res = RES_OK;
		        break;	 
		    case GET_SECTOR_COUNT:
 		        res = RES_OK;
		        break;
		    default:
		        res = RES_PARERR;
		        break;
		}
		return res;
	}
	else if(pdrv==DEV_MMC)
	{
		return RES_OK;
	}

	return RES_PARERR;
}

DWORD get_fattime()
{
	u32 temp = 0;
	temp |=((uint32_t)time_and_date[sec]&0x003F)>>1;
	temp |=((uint32_t)time_and_date[min]&0x003F)<<5;
	temp |=((uint32_t)time_and_date[hour]&0x001F)<<11;
	temp |=((uint32_t)time_and_date[date]&0x001F)<<16;
	temp |=((uint32_t)time_and_date[month]&0x000F)<<21;
	temp |=((uint32_t)time_and_date[date]&0x007F)<<25;
	return temp;
}
