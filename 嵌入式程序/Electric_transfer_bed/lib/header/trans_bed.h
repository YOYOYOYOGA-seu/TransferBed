#ifndef __TRANS_BED_H
#define __TRANS_BED_H
#endif
#ifdef __cplusplus
 extern "C" {
#endif

	 
#include "stm32f10x_conf.h"
	 
//--------------------运动状态显示-------------------------	 
#define LONGP_STATE_X       170 //各运动在屏幕上的状态显示（红绿蓝）位置_X坐标
#define SHORTP_STATE_X      200
#define CONVEYOR_STATE_X    230
#define BEDPLATE_STATE_X    260
#define MOVE_STATE_Y        225//Y坐标
#define ICON_SIZE           4
#define ICON_OFFSET_X       15  //红绿蓝光点X坐标偏移量
#define ICON_OFFSET_Y       4  //红绿蓝光点Y坐标偏移量,需要根据SIZE和字体大小计算
//----------------------页面边框绘制-----------------------
#define PAGE_BACK_COLOR     LGRAYBLUE
#define PAGE_NUM            3
#define FRAME_OFFSET        5   //边框上下左右留白
#define BUTTON_TOP_Y        215
#define BUTTON_HEIGHT       20
#define BUTTON_WIDTH        40
//--------------------mainPage有关宏定义--------------------
#define MP_BUTTON_NUM       2       //按键总个数
#define MP_BUTTON_H_1       30      //按键尺寸1（床身调节、靠背调节）
#define MP_BUTTON_W_1       60

#define MLP_BUTTON_DIS      80

#define AUTO_SENT_Y         80
#define AUTO_SENT_X         220
#define AUTO_TAKE_Y         AUTO_SENT_Y + MLP_BUTTON_DIS
#define AUTO_TAKE_X         AUTO_SENT_X
#define AUTO_NEXT_Y         AUTO_SENT_Y
#define AUTO_NEXT_X         AUTO_SENT_X
#define AUTO_CANCEL_Y       AUTO_NEXT_Y + MLP_BUTTON_DIS
#define AUTO_CANCEL_X       AUTO_NEXT_X



#define MESG_PAD_X          10      
#define MESG_PAD_Y					50
#define MESG_PAD_WIDTH      150      
#define MESG_PAD_HEIGHT			150
//--------------------manualPage有关宏定义--------------------
#define MLP_BUTTON_NUM       11       //按键总个数
#define MLP_BUTTON_H_1       30      //按键尺寸1（床身调节、靠背调节、床板传送带伸出收回）
#define MLP_BUTTON_W_1       30   
#define MLP_BUTTON_H_2       30      //按键尺寸2（手动接病人、送病人、收回床板按键)
#define MLP_BUTTON_W_2       60 

#define MLP_BUTTON_DIS_1     50      //按键距离（高度、靠背调节的上、下按键距离）
#define MLP_BUTTON_DIS_2     20      //按键距离（丝杠、传送带送出、收回按键距离）
#define MLP_BUTTON_DIS_3     25      //按键距离（手动送病人、手动接病人、收回病人按键距离）

#define BED_UP_DOWN_Y    	  80       //高度调节按键最上端Y坐标
#define BED_UP_DOWN_X		    20       //高度调节按键最左端X坐标
#define BACK_UP_DOWN_Y    	BED_UP_DOWN_Y   //靠背调节按键最上端Y坐标
#define BACK_UP_DOWN_X      70       //靠背调节按键最左端X坐标

#define BED_IN_OUT_Y        80       //床板伸出收回按键最上端Y坐标
#define BED_IN_OUT_X				130      //床板伸出收回按键最左端X坐标
#define CONV_IN_OUT_Y				160      //传送带伸出收回按键最上端Y坐标
#define CONV_IN_OUT_X       BED_IN_OUT_X       //传送带伸出收回按键最左端X坐标

#define MANUAL_CTRL_Y       60
#define MANUAL_CTRL_X				240

//------------------------setPage有关定义----------------------
#define SET_DATA_NUM        5                  //可调数据个数,详见下typedef enum
#define SET_DATA_EAXM_OK    0x0117      //校验Flash中储存数据的有效性
#define MAX_SPEED_LEVEL     10
#define MAX_SPPED_LEVEL     10


#define SPEED_BLOCK_H      	10
#define SPEED_BLOCK_W       5
#define SPEED_BAR_H         SPEED_BLOCK_H
#define SPEED_BAR_LENGTH    100   
#define SAVE_BUTTON_H       20
#define SAVE_BUTTON_W			  30
#define CANCEL_BUTTON_H 		SAVE_BUTTON_H	
#define CANCEL_BUTTON_W 		SAVE_BUTTON_W

#define SPEED_SETTING_DIS   20

   //4个速度调整条的坐标
#define SPEED_SETTING_X     25     
#define SPEED_SETTING_Y_1   60                 
#define SPEED_SETTING_Y_2   SPEED_SETTING_Y_1 + SPEED_BAR_H + SPEED_SETTING_DIS
#define SPEED_SETTING_Y_3   SPEED_SETTING_Y_2 + SPEED_BAR_H + SPEED_SETTING_DIS + 20
#define SPEED_SETTING_Y_4   SPEED_SETTING_Y_3 + SPEED_BAR_H + SPEED_SETTING_DIS
#define SAVE_BUTTON_X       220 
#define SAVE_BUTTON_Y				180
#define CANCEL_BUTTON_X     SAVE_BUTTON_X + SAVE_BUTTON_W + 10 
#define CANCEL_BUTTON_Y			SAVE_BUTTON_Y

extern uint16_t settingData[SET_DATA_NUM];
typedef enum{
	MAIN_PAGE = 0,
	MANUAL_ADJUST,
	SETTING

}TransBed_PageNum;	


typedef enum{
	SET_DATA_FLAG = 0,
	BED_OUT_SPEAD_LEVEL,
	BED_IN_SPEAD_LEVEL,
	CONVEYOR_OUT_SPEED_LEVEL,
	CONVEYOR_IN_SPEED_LEVEL,
}Setting_DataIndex;         //可设置数据枚举

void TransferBed_APP(void);
void TransBed_APPinit(void);
void TransBed_KeyAction(void);
void RefreshMoveState(void);
void SetPage(uint16_t num);
void SwitchPage(void);
void mainPageInit(void);
void mAdjPageInit(void);
void setPageInit(void);

void mainPageFun(void);
void manualAdjPageFun(void);
void settingPageFun(void);

Motor_Error AutoTakePatient(void);
Motor_Error AutoSentPatient(void);
#ifdef __cplusplus
 }
#endif
