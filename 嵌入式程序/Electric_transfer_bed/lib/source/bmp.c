#include "bmp.h"

#define BMP_BUFF_SIZE  2880

BMP_ERR_TypeDef LCD_ShowBMP(uint16_t x,uint16_t y,const TCHAR *bmpPathPtr,FATFS *fs)
{
	FIL bmp_file;
	FRESULT fresult;
	BITMAP_FILE_HEADER fileHead;  //�ֽڶ��루
	BITMAP_INFO_HEADER infoHead;
	
	uint8_t ifIncludePalette = 0;
	RGBQUAD *palettePtr = NULL;
	uint32_t paletteNum;
	
	uint16_t addByte = 0;   //windows��BMPҪ��ÿ�е��ֽ�����4�ı�����������ʱ��Ҫ����
	uint32_t pixelDataReadOffset = 0;   //ÿ�ζ�ȡ��BUFFʱָ�뿪ʼλ�õĵ�ַƫ����
	uint8_t pixelDataPtr [BMP_BUFF_SIZE] = {0};
	uint32_t byteWith;//8��24��32λbmpһ�����ض�Ӧ���ֽ�����ͬ
	uint16_t LineNumOfBuff = 0;
	
	
	uint32_t br;
	
	 
	//bmp�ļ���
	fresult = f_open(&bmp_file , bmpPathPtr ,FA_READ|FA_OPEN_EXISTING);
	if(fresult != FR_OK)
	{
		return BMP_OPEN_FILE;
	}
	//�ļ�ͷ��ȡ������
	fresult = f_read(&bmp_file,&fileHead,sizeof(BITMAP_FILE_HEADER),&br);
	if(fresult != FR_OK)
	{
		f_close(&bmp_file);
		return BMP_OPEN_FILE;
	}
	if(fileHead.bfType !=0x4d42)
	{
		f_close(&bmp_file);
		return BMP_FILE_HEARD;
	}	
	//λͼ��Ϣͷ��
	fresult = f_read(&bmp_file,&infoHead,sizeof(BITMAP_INFO_HEADER),&br);
	if(fresult != FR_OK)
	{
		f_close(&bmp_file);
		return BMP_OPEN_FILE;
	}
	
	if((infoHead.biWith == 0)||(infoHead .biHeight == 0))
	{
		f_close(&bmp_file);
		return BMP_NONE;
	}
	//����ת����bmp�Ǵ����ң����ϵ��£�
	y += infoHead.biHeight;
	//λͼ���뷽ʽ�ж�
	addByte = ((infoHead.biWith*infoHead.biBitCount)>>3)&3;
	
	switch (infoHead.biBitCount)
	{
		case 8:
			byteWith = ((infoHead.biWith*infoHead.biBitCount + 31)>>5)<<2;
			break;
		case 16:
			byteWith = ((infoHead.biWith*infoHead.biBitCount + 31)>>5)<<2;
			break;
		case 24:
			byteWith = ((infoHead.biWith*infoHead.biBitCount + 31)>>5)<<2;
			break;	
		case 32:
			byteWith = ((infoHead.biWith*infoHead.biBitCount + 31)>>5)<<2;
			break;
		default:
		{
			f_close(&bmp_file);
			return BMP_NOT_SUPPORT;
		}
	}
	
	//�ж��Ƿ��е�ɫ�岢Ϊ��ɫ�������ڴ桢����
	if(fileHead.bfOffBits > sizeof(BITMAP_INFO_HEADER)+sizeof(BITMAP_FILE_HEADER))
	{
		ifIncludePalette = 1;
	}
	
	if(ifIncludePalette)
	{
		paletteNum = fileHead.bfOffBits - (sizeof(BITMAP_INFO_HEADER)+sizeof(BITMAP_FILE_HEADER));
		palettePtr = (RGBQUAD *)calloc(1,paletteNum);
	
		if(palettePtr == NULL)
		{
			f_close(&bmp_file);
			return BMP_MALLOC;
		}		
		
		fresult = f_read(&bmp_file,palettePtr,paletteNum,&br);
		if(fresult != FR_OK)
		{
			free(palettePtr);
			f_close(&bmp_file);
			return BMP_OPEN_FILE;
		}
	}
	//��buff�ж���ͼ������
	LineNumOfBuff = (BMP_BUFF_SIZE-2)/byteWith; //��֤4�ֽڶ���,dma�µ�SDIOҪ���ȡ�ĵ�ַΪ4�ı���
	pixelDataReadOffset = fileHead.bfOffBits - 2;
	
	uint8_t ifFileEnd = 0;
	
	uint16_t lineCount; //��BUFF��LCD����ʱ��¼����������buff�еĵڼ��У�
	uint16_t pixelCount;//��BUFF��LCD����ʱ��¼һ���еĵ������������еڼ��㣩
	uint16_t lcdDrawnPtr;//��BUff����LCD����ʱ��ָ�룬= lineCount*ByteWith + pixelCount;
	
	while(!ifFileEnd)
	{
		f_lseek(&bmp_file,pixelDataReadOffset);
		fresult = f_read(&bmp_file,pixelDataPtr,LineNumOfBuff*byteWith + 2,&br);
		br -=2;
		if(br != LineNumOfBuff*byteWith)//�����ļ�β
		{
			LineNumOfBuff = br/byteWith;
			ifFileEnd = 1;
		}
		if(fresult != FR_OK)
		{
			if(ifIncludePalette)
				free(palettePtr);
			f_close(&bmp_file);
			return BMP_OPEN_FILE;
		}
		
		pixelDataReadOffset += br;
		
		switch (infoHead.biBitCount)
		{
			case 8:
			{
				for(lineCount = 0;lineCount < LineNumOfBuff;lineCount ++)
				{
					for(pixelCount = 0;pixelCount < byteWith - addByte;pixelCount ++)
					{
						lcdDrawnPtr = lineCount*byteWith + pixelCount + 2;
						LCD_Fast_DrawPoint(x +pixelCount ,y,
						RGB565_Calculate(palettePtr[pixelDataPtr[lcdDrawnPtr]].rgbRed,palettePtr[pixelDataPtr[lcdDrawnPtr]].rgbGreen,palettePtr[pixelDataPtr[lcdDrawnPtr]].rgbBlude));
					}
					y -=1;
				}
				break;
			}
			
			case 24:
			{
				for(lineCount = 0;lineCount < LineNumOfBuff;lineCount ++)
				{
					for(pixelCount = 0;pixelCount < (byteWith - addByte)/3;pixelCount ++)
					{
						lcdDrawnPtr = lineCount*byteWith + 3*pixelCount + 2;
						LCD_Fast_DrawPoint(x +pixelCount ,y,RGB565_Calculate(pixelDataPtr[3*pixelCount+2],pixelDataPtr[3*pixelCount+1],pixelDataPtr[3*pixelCount]));
					}
					y -=1;
				}
				break;
			}
		}
	}
	f_close(&bmp_file);
	if(ifIncludePalette)
		free(palettePtr);
	return BMP_NONE;
}
