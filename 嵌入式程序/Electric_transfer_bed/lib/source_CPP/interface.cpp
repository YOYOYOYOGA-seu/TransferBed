#include "common.h"
#include "string.h"
#include "class_definition.h"


//--------------------全局变量--------------------------------------
const char APP_name[APPNUM][9]={"drawing","transBed"};  //APP的名字，最多8个字符
APP darwing((const TCHAR*)APP_name[DRAWING],0,0,TS_Adjusting_test,30,40, (const TCHAR*)_TEXT("0:test.bmp")); //画图APP定义
APP transferBed((const TCHAR*)APP_name[TRANSBED],1,1,TransferBed_APP,90,40, (const TCHAR*)_TEXT("0:transBed.bmp"));//病床控制APP定义
APP *appPtr [APPNUM] = {&darwing,&transferBed};//APP的指针向量，用于APP操作

uint8_t ShowTitleCmd = 0;    //标题显示使能位
uint8_t currentApp = INITIAL_INTERFACE; //当前运行APP序号
char temp[30] = {0}; //供sprintf使用 

//-------------------------------标题栏----------------------------------------------------
void ShowTitle(void)
{
	uint16_t i = 0;
	uint16_t temp_PointColor = POINT_COLOR;
	uint16_t temp_BackColor = BACK_COLOR;
	POINT_COLOR = BLACK;
	BACK_COLOR = GRAY;
	if(!lcddev.dir)
	{
		LCD_Fill(0,0,240,TITLE_HEIGHT,GRAY);

		for(i=0;i<4;i++)
		{
			sprintf(temp,"%d:%d%d",time_and_date[hour],(uint8_t)(time_and_date[min]/10),(uint8_t)(time_and_date[min]%10));
			LCD_ShowString(200,3,40,15,12,(uint8_t*)temp,0);
			sprintf(temp,"%d/%d/%d  %s",time_and_date[year],time_and_date[month],time_and_date[date],weeks[time_and_date[week]]);
			LCD_ShowString(10,3,150,15,12,(uint8_t*)temp,0);
		}	
		POINT_COLOR = temp_PointColor;
		BACK_COLOR = temp_BackColor;
		//key_action();
	}
	else
	{
		LCD_Fill(0,0,320,20,GRAY);

		for(i=0;i<4;i++)
		{
			sprintf(temp,"%d:%d%d",time_and_date[hour],(uint8_t)(time_and_date[min]/10),(uint8_t)(time_and_date[min]%10));
			LCD_ShowString(280,3,40,15,12,(uint8_t*)temp,0);
			sprintf(temp,"%d/%d/%d  %s",time_and_date[year],time_and_date[month],time_and_date[date],weeks[time_and_date[week]]);
			LCD_ShowString(10,3,150,15,12,(uint8_t*)temp,0);
		}	
		POINT_COLOR = temp_PointColor;
		BACK_COLOR = temp_BackColor;
		//key_action();
	}	

}
//--------------------返回主页-----------------------
void GoHomePage(void)
{
	currentApp = HOMEPAGE;
	appProgramPtr = HomePage;
	key[S4].short_press = 0;
}

//-------------------初始页面不是主页时的设置---------------
void IfNoHomePage(void)
{
	if(INITIAL_INTERFACE != MAIN_PAGE)
	{
		appPtr[INITIAL_INTERFACE]->GetProgramPointToApp();
		ShowTitleCmd = appPtr[INITIAL_INTERFACE]->ifShowTitle;
		currentApp = INITIAL_INTERFACE;
	}
}
//--------------------主页------------------------
void HomePage(void)
{

	uint16_t i = 0;
	LCD_Display_Dir(0);
	ShowTitleCmd = 1;   //主页不是一个APP,需要手动设置标题使能
	ShowTitle();
	LCD_CLearInterface(ShowTitleCmd,WHITE);
	FATFS fs;
	FRESULT res;
	res = f_mount(&fs,(const TCHAR*) _TEXT("0:"), 0);
	if (res == FR_OK)
	{

		LCD_ShowBMP(0,20, (const TCHAR*)_TEXT("/home_back.bmp"),&fs);

	}
	for(i = 0;i < APPNUM; i++)//显示app的图标
		appPtr[i]->ShowButton();
	f_mount(0,(const TCHAR*) _TEXT("0:"), 0);
	while(currentApp == HOMEPAGE)
	{
		if(Period_Divide_Counter == 1)
		{
			sprintf(temp,"%s : %d","Touch_Screen_X_AD",TS_AD_XY.x);
			LCD_ShowString(20,125,200,15,12,(u8 *)temp,0);
			
			sprintf(temp,"%s : %d","Touch_Screen_Y_AD",TS_AD_XY.y);
			LCD_ShowString(20,145,200,15,12,(u8 *)temp,0);
		}
	}
//卸载文件系统（可以放在循环之上）
}

//---------------判断是否有app图标被按下--------------------
void ButtonPressJudgement(void)
{

	for(int i=0 ; i< APPNUM ; i++)
	{
		if(appPtr[i]->AppIfBeSelected() == 1)
		{
			appPtr[i]->GetProgramPointToApp();
			ShowTitleCmd = appPtr[i]->ifShowTitle;
			currentApp = i;
		}
	}
}


//---------------------button 成员函数------------------------
Button::Button(uint16_t x,uint16_t y,const TCHAR* iFname,uint16_t Color,const TCHAR* Text)  //APP按钮
{
	x_coord = x;
	y_coord = y;
	iconFile = iFname;
	xSize = DEFAULT_BUTTON_X_SIZE;
	ySize = DEFAULT_BUTTON_Y_SIZE;
	selectFlag = 0;
	ButtonColor = Color;
	text = Text;
	buttonFun = NULL;
}

Button::Button(uint16_t x,uint16_t y,const TCHAR* iFname,uint16_t X_Size,uint16_t Y_Size,void (*ptr)(void),uint16_t Color ,const TCHAR* Text)//其他按钮
{
	x_coord = x;
	y_coord = y;
	iconFile = iFname;
	xSize = X_Size;
	ySize = Y_Size;
	selectFlag = 0;
	ButtonColor = Color;
	text = Text;
	buttonFun = ptr;
}


void Button ::Show(void)
{
	uint16_t strPixelNum;
	int16_t retractPixelNum;
	if(text == NULL)
	 LCD_ShowBMP(x_coord,y_coord,iconFile,NULL);
	else
	{
		LCD_Fill(x_coord,y_coord,x_coord + xSize, y_coord + ySize, ButtonColor);
		strPixelNum = 6*strlen((const char*)text);
		retractPixelNum =(xSize - strPixelNum )/2;
		LCD_ShowString(x_coord + retractPixelNum,y_coord + (ySize - 12)/2,strPixelNum ,13 ,12,(u8*)text,1);
	}
	
}

uint8_t Button::ButtonIfBeSelected(void)
{
	if(TS_XY.x>x_coord&&TS_XY.x<x_coord+xSize&&TS_XY.y>y_coord&&TS_XY.y<y_coord+ySize)
		selectFlag = 1;
	else if(TS_XY.x ==0&&TS_XY.y == 0)
	{
		if(selectFlag == 1)
		{
			selectFlag = 2;
		}
		else if(selectFlag == 2||selectFlag == 3)
			selectFlag = 0;
	}
	else
	{
		if(selectFlag == 1)
		{
			selectFlag = 3;
		}
		else if(selectFlag == 2)
		{
			selectFlag = 0;
		}
			
	}
	return selectFlag;
}
//-----------------------------APP成员函数--------------------------------------------------------
APP::APP(const TCHAR* Name,bool titleFlag,bool LandscapeMode,void (*ptr)(void),uint16_t x,uint16_t y,const TCHAR* iFname):appButton(x,y,iFname)
{
	name = Name;
	ifShowTitle  = titleFlag;
	ifLandscapeMode = LandscapeMode;
	appFun = ptr;
}

APP::APP(const TCHAR* Name,bool titleFlag,bool LandscapeMode,void (*ptr)(void),uint16_t x,uint16_t y,const TCHAR* iFname,uint16_t X_Size,uint16_t Y_Size):appButton(x,y,iFname,X_Size,Y_Size)
{
	name = Name;
	ifShowTitle  = titleFlag;
	ifLandscapeMode = LandscapeMode;
	appFun = ptr;
}

void APP::ShowButton()
{
	u8 strPixelNum = 0;
	int8_t retractPixelNum  = 0;
	appButton.Show();
	
	strPixelNum = 6*strlen((const char*)name);
	retractPixelNum = (strPixelNum - appButton.xSize)/2;
	POINT_COLOR = WHITE;
	LCD_ShowString(u16(appButton.x_coord - retractPixelNum),appButton.y_coord + appButton.ySize + 1,strPixelNum,13,12,(u8*)name,1);
	POINT_COLOR = BLACK;
}

uint8_t APP::AppIfBeSelected()
{
	if(appButton.ButtonIfBeSelected()==2)
	{
		appButton.selectFlag = 0;
		return 1;
	}
	else
		return 0;
}

void APP::GetProgramPointToApp(void)
{
	appProgramPtr = appFun;
	LCD_Display_Dir(ifLandscapeMode);
}


//-----------------------------------------------------------------------------
