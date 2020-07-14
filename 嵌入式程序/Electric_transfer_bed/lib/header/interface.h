#ifndef __INTERFACE_H
#define __INTERFACE_H

#ifdef __cplusplus
 extern "C" {
#endif 


#include "stm32f10x_conf.h"
#include "ff.h"

#define DEFAULT_BUTTON_X_SIZE 40 // 默认主页图标大小
#define DEFAULT_BUTTON_Y_SIZE 40	 

#define APPNUM 2

#define INITIAL_INTERFACE_FUN  HomePage//开机后显示的界面与APP编号
#define INITIAL_INTERFACE  	 HOMEPAGE
	 
#define HOME_BUTTON_CMD 1  //HOME按钮和标题栏（日期）使能定义，不需要时就注释掉 
#define TITLE_CMD 1
#define TITLE_HEIGHT 20

//APP序号枚举	 
typedef enum {
	DRAWING = 0,
	TRANSBED,
	
	
	HOMEPAGE = 10
	
	
}APP_Name;
//---------------
extern uint8_t currentApp;
extern uint8_t ShowTitleCmd;
	 
void ShowTitle(void);
void GoHomePage(void);
void IfNoHomePage(void);
void HomePage(void);
void ButtonPressJudgement(void);

#ifdef __cplusplus
}
#endif
#endif
