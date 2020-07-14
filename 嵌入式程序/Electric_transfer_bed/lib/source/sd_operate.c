#include "common.h"
#include <string.h> 
void SD_fs_test(void)//欢迎界面
{
	


		FATFS fs;           /* Filesystem object */

    FIL fil;            /* File object */

    FRESULT res;  /* API result code */
	

	/* 挂载文件系统 */
#if (INITIAL_INTERFACE == TRANSBED)
	uint32_t temp_dir = lcddev.dir;
	LCD_Display_Dir(1);
#endif
	res = f_mount(&fs, _TEXT("0:"), 0);

	if (res)

	{

		LCD_ShowString(40,60,200,20,12,"File system failed.\r\n",0);
		Delay_ms(5000);
		return;

	}

	if(INITIAL_INTERFACE == MAIN_PAGE)
		LCD_ShowBMP(0,0,_TEXT("/welcome.bmp"),&fs);
	else if(INITIAL_INTERFACE == TRANSBED)
	{
		LCD_ShowBMP(0,0,_TEXT("0:/transB/welcome.bmp"),&fs);
	}
	Delay_ms(3000);
	LCD_CLearInterface(ShowTitleCmd,WHITE);
	
	

	/* Create a file as new */

	/* Close the file */

	f_close(&fil);

	/*卸载文件系统*/

	f_mount(0,_TEXT("0:"), 0);
#if (INITIAL_INTERFACE == TRANSBED)
	if(temp_dir != 1)
	{
		LCD_Display_Dir(temp_dir);
	}
#endif
	


}
