#ifndef __BMP_H
#define __BMP_H


#ifdef __cplusplus
 extern "C" {
#endif 
	 
	 
#include "stm32f10x_conf.h"
#include "lcd.h"
#include "ff.h"
#include "stdlib.h"
	 
//bmp�ļ�ͷ
#pragma pack (1)//�޸�Ĭ�϶��뷽ʽ��Ĭ����4�ֽڶ��룬��DWORD��ֻ�ܴ����ƫ��Ϊ0x00,0x04,0x08��λ�ã�����ɰٶȣ�
typedef struct tagBITMAP_FILE_HEADER
{
	uint16_t bfType;
	uint32_t bfSize;
	uint16_t bfReserved1;
	uint16_t bfReserved2;
	uint32_t bfOffBits;
}BITMAP_FILE_HEADER;
#pragma pack ()
//bmpλͼ��Ϣͷ
typedef struct tagBITMAP_INFO_HEADER 
{  
	
uint32_t biSize;    
uint32_t biWith; 
uint32_t biHeight; 
uint16_t biPlanes; 
uint16_t biBitCount; 
uint32_t biCompression;
uint32_t biSizeImage;
uint32_t biXPelsPerMeter;
uint32_t biYPelsPerMeter;
uint32_t biClrUsed;
uint32_t biClrImportant;
	
} BITMAP_INFO_HEADER;

//��ɫ��
typedef struct tagRGBQUAD
{
	uint8_t rgbBlude;
	uint8_t rgbGreen;
	uint8_t rgbRed;
	uint8_t rgbReserved;
}RGBQUAD;

typedef enum
{
	BMP_NONE = 0,
	BMP_OPEN_FILE,
	BMP_FILE_HEARD,
	BMP_MALLOC,
	BMP_NOT_SUPPORT,
}BMP_ERR_TypeDef;

BMP_ERR_TypeDef LCD_ShowBMP(uint16_t x,uint16_t y,const TCHAR *bmpPathPtr,FATFS *fs);

#ifdef __cplusplus
 }

#endif
#endif
