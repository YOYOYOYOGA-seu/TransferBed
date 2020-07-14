#ifndef __TRANS_BED_H
#define __TRANS_BED_H
#endif
#ifdef __cplusplus
 extern "C" {
#endif

	 
#include "stm32f10x_conf.h"
	 
//--------------------�˶�״̬��ʾ-------------------------	 
#define LONGP_STATE_X       170 //���˶�����Ļ�ϵ�״̬��ʾ����������λ��_X����
#define SHORTP_STATE_X      200
#define CONVEYOR_STATE_X    230
#define BEDPLATE_STATE_X    260
#define MOVE_STATE_Y        225//Y����
#define ICON_SIZE           4
#define ICON_OFFSET_X       15  //���������X����ƫ����
#define ICON_OFFSET_Y       4  //���������Y����ƫ����,��Ҫ����SIZE�������С����
//----------------------ҳ��߿����-----------------------
#define PAGE_BACK_COLOR     LGRAYBLUE
#define PAGE_NUM            3
#define FRAME_OFFSET        5   //�߿�������������
#define BUTTON_TOP_Y        215
#define BUTTON_HEIGHT       20
#define BUTTON_WIDTH        40
//--------------------mainPage�йغ궨��--------------------
#define MP_BUTTON_NUM       2       //�����ܸ���
#define MP_BUTTON_H_1       30      //�����ߴ�1��������ڡ��������ڣ�
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
//--------------------manualPage�йغ궨��--------------------
#define MLP_BUTTON_NUM       11       //�����ܸ���
#define MLP_BUTTON_H_1       30      //�����ߴ�1��������ڡ��������ڡ����崫�ʹ�����ջأ�
#define MLP_BUTTON_W_1       30   
#define MLP_BUTTON_H_2       30      //�����ߴ�2���ֶ��Ӳ��ˡ��Ͳ��ˡ��ջش��尴��)
#define MLP_BUTTON_W_2       60 

#define MLP_BUTTON_DIS_1     50      //�������루�߶ȡ��������ڵ��ϡ��°������룩
#define MLP_BUTTON_DIS_2     20      //�������루˿�ܡ����ʹ��ͳ����ջذ������룩
#define MLP_BUTTON_DIS_3     25      //�������루�ֶ��Ͳ��ˡ��ֶ��Ӳ��ˡ��ջز��˰������룩

#define BED_UP_DOWN_Y    	  80       //�߶ȵ��ڰ������϶�Y����
#define BED_UP_DOWN_X		    20       //�߶ȵ��ڰ��������X����
#define BACK_UP_DOWN_Y    	BED_UP_DOWN_Y   //�������ڰ������϶�Y����
#define BACK_UP_DOWN_X      70       //�������ڰ��������X����

#define BED_IN_OUT_Y        80       //��������ջذ������϶�Y����
#define BED_IN_OUT_X				130      //��������ջذ��������X����
#define CONV_IN_OUT_Y				160      //���ʹ�����ջذ������϶�Y����
#define CONV_IN_OUT_X       BED_IN_OUT_X       //���ʹ�����ջذ��������X����

#define MANUAL_CTRL_Y       60
#define MANUAL_CTRL_X				240

//------------------------setPage�йض���----------------------
#define SET_DATA_NUM        5                  //�ɵ����ݸ���,�����typedef enum
#define SET_DATA_EAXM_OK    0x0117      //У��Flash�д������ݵ���Ч��
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

   //4���ٶȵ�����������
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
}Setting_DataIndex;         //����������ö��

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
