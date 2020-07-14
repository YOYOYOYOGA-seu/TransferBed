#include "bmp.h"

#define BMP_BUFF_SIZE  2880

BMP_ERR_TypeDef LCD_ShowBMP(uint16_t x,uint16_t y,const TCHAR *bmpPathPtr,FATFS *fs)
{
	FIL bmp_file;
	FRESULT fresult;
	BITMAP_FILE_HEADER fileHead;  //字节对齐（
	BITMAP_INFO_HEADER infoHead;
	
	uint8_t ifIncludePalette = 0;
	RGBQUAD *palettePtr = NULL;
	uint32_t paletteNum;
	
	uint16_t addByte = 0;   //windows下BMP要求每行的字节数是4的倍数，当不是时需要不齐
	uint32_t pixelDataReadOffset = 0;   //每次读取到BUFF时指针开始位置的地址偏移量
	uint8_t pixelDataPtr [BMP_BUFF_SIZE] = {0};
	uint32_t byteWith;//8、24、32位bmp一个像素对应的字节数不同
	uint16_t LineNumOfBuff = 0;
	
	
	uint32_t br;
	
	 
	//bmp文件打开
	fresult = f_open(&bmp_file , bmpPathPtr ,FA_READ|FA_OPEN_EXISTING);
	if(fresult != FR_OK)
	{
		return BMP_OPEN_FILE;
	}
	//文件头读取及检验
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
	//位图信息头打开
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
	//坐标转换（bmp是从左到右，从上到下）
	y += infoHead.biHeight;
	//位图编码方式判断
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
	
	//判断是否有调色板并为调色板申请内存、读入
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
	//向buff中读入图像数据
	LineNumOfBuff = (BMP_BUFF_SIZE-2)/byteWith; //保证4字节对齐,dma下的SDIO要求读取的地址为4的倍数
	pixelDataReadOffset = fileHead.bfOffBits - 2;
	
	uint8_t ifFileEnd = 0;
	
	uint16_t lineCount; //从BUFF往LCD画点时记录行数（画到buff中的第几行）
	uint16_t pixelCount;//从BUFF往LCD画点时记录一行中的点数（画到该行第几点）
	uint16_t lcdDrawnPtr;//从BUff中往LCD画点时的指针，= lineCount*ByteWith + pixelCount;
	
	while(!ifFileEnd)
	{
		f_lseek(&bmp_file,pixelDataReadOffset);
		fresult = f_read(&bmp_file,pixelDataPtr,LineNumOfBuff*byteWith + 2,&br);
		br -=2;
		if(br != LineNumOfBuff*byteWith)//读到文件尾
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
