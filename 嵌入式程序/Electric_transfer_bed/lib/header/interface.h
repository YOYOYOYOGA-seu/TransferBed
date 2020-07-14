#ifndef __INTERFACE_H
#define __INTERFACE_H

#ifdef __cplusplus
 extern "C" {
#endif 


#include "stm32f10x_conf.h"
#include "ff.h"

#define DEFAULT_BUTTON_X_SIZE 40 // Ĭ����ҳͼ���С
#define DEFAULT_BUTTON_Y_SIZE 40	 

#define APPNUM 2

#define INITIAL_INTERFACE_FUN  HomePage//��������ʾ�Ľ�����APP���
#define INITIAL_INTERFACE  	 HOMEPAGE
	 
#define HOME_BUTTON_CMD 1  //HOME��ť�ͱ����������ڣ�ʹ�ܶ��壬����Ҫʱ��ע�͵� 
#define TITLE_CMD 1
#define TITLE_HEIGHT 20

//APP���ö��	 
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
