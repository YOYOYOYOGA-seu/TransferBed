#include "common.h"
#include "class_definition.h"
//-------------------ȫ�ֱ���------------------------------------------------
FATFS fs;
uint16_t settingData[SET_DATA_NUM] = {SET_DATA_EAXM_OK,2,4,7,10}; //�ɱ���,��һλΪУ��λ���ٶȵ���ʼ��Ϊ��͵�
uint16_t stateIconColor[3] = {GREEN,RED,BLUE};   //�������˶�״̬ͼ����ɫ������motion_state��ѯ
//-------------------ҳ���л��йر�������ť-----------------------------
uint16_t PageNum = 0;
Button mainPage(FRAME_OFFSET + MAIN_PAGE ,BUTTON_TOP_Y,(const TCHAR*)_TEXT("0:/transB/mainPage.bmp"),BUTTON_WIDTH,BUTTON_HEIGHT,mainPageInit);
Button manualAdjPage(FRAME_OFFSET +MANUAL_ADJUST*BUTTON_WIDTH,BUTTON_TOP_Y,(const TCHAR*)_TEXT("0:/transB/mAdjPage.bmp"),BUTTON_WIDTH,BUTTON_HEIGHT,mAdjPageInit);
Button settingPage(FRAME_OFFSET +SETTING*BUTTON_WIDTH,BUTTON_TOP_Y,(const TCHAR*)_TEXT("0:/transB/setPage.bmp"),BUTTON_WIDTH,BUTTON_HEIGHT,setPageInit);
Button * PageButtonPtr[PAGE_NUM] = {&mainPage,&manualAdjPage,&settingPage}; //ҳ�л���ťָ�룬ע��˳��
//------------------mainPage��ť------------------------
Button autoSent(AUTO_SENT_X,AUTO_SENT_Y,(const TCHAR*)_TEXT("0:/transB/mainP/autoSent.bmp"),MP_BUTTON_W_1,MP_BUTTON_H_1);
Button autoTake(AUTO_TAKE_X,AUTO_TAKE_Y,(const TCHAR*)_TEXT("0:/transB/mainP/autoTake.bmp"),MP_BUTTON_W_1,MP_BUTTON_H_1);
Button autoNext(AUTO_NEXT_X,AUTO_NEXT_Y,(const TCHAR*)_TEXT("0:/transB/mainP/autoNext.bmp"),MP_BUTTON_W_1,MP_BUTTON_H_1);
Button autoCancel(AUTO_CANCEL_X,AUTO_CANCEL_Y,(const TCHAR*)_TEXT("0:/transB/mainP/autoCancel.bmp"),MP_BUTTON_W_1,MP_BUTTON_H_1);
//-------------------manualPage��ť----------------------
Button bedUp(BED_UP_DOWN_X,BED_UP_DOWN_Y,(const TCHAR*)_TEXT("0:/transB/manualAdjP/bedUp.bmp"),MLP_BUTTON_W_1,MLP_BUTTON_H_1);
Button bedDown(BED_UP_DOWN_X,BED_UP_DOWN_Y + MLP_BUTTON_H_1 + MLP_BUTTON_DIS_1,(const TCHAR*)_TEXT("0:/transB/manualAdjP/bedDown.bmp"),MLP_BUTTON_W_1,MLP_BUTTON_H_1);
Button backUp(BACK_UP_DOWN_X,BACK_UP_DOWN_Y,(const TCHAR*)_TEXT("0:/transB/manualAdjP/backUp.bmp"),MLP_BUTTON_W_1,MLP_BUTTON_H_1);
Button backDown(BACK_UP_DOWN_X,BACK_UP_DOWN_Y + MLP_BUTTON_H_1 + MLP_BUTTON_DIS_1,(const TCHAR*)_TEXT("0:/transB/manualAdjP/backDown.bmp"),MLP_BUTTON_W_1,MLP_BUTTON_H_1);

Button bedOut(BED_IN_OUT_X,BED_IN_OUT_Y,(const TCHAR*)_TEXT("0:/transB/manualAdjP/bedOut.bmp"),MLP_BUTTON_W_1,MLP_BUTTON_H_1);
Button bedIn(BED_IN_OUT_X + MLP_BUTTON_W_1 + MLP_BUTTON_DIS_2,BED_IN_OUT_Y,(const TCHAR*)_TEXT("0:/transB/manualAdjP/bedIn.bmp"),MLP_BUTTON_W_1,MLP_BUTTON_H_1);
Button conveyorOut(CONV_IN_OUT_X,CONV_IN_OUT_Y,(const TCHAR*)_TEXT("0:/transB/manualAdjP/conveyorOut.bmp"),MLP_BUTTON_W_1,MLP_BUTTON_H_1);
Button conveyorIn(CONV_IN_OUT_X + MLP_BUTTON_W_1 + MLP_BUTTON_DIS_2,CONV_IN_OUT_Y,(const TCHAR*)_TEXT("0:/transB/manualAdjP/conveyorIn.bmp"),MLP_BUTTON_W_1,MLP_BUTTON_H_1);

Button takeIn(MANUAL_CTRL_X,MANUAL_CTRL_Y,(const TCHAR*)_TEXT("0:/transB/manualAdjP/takeIn.bmp"),MLP_BUTTON_W_2,MLP_BUTTON_H_2);
Button sentOut(MANUAL_CTRL_X,MANUAL_CTRL_Y + MLP_BUTTON_H_2 + MLP_BUTTON_DIS_3,(const TCHAR*)_TEXT("0:/transB/manualAdjP/sentOut.bmp"),MLP_BUTTON_W_2,MLP_BUTTON_H_2);
Button back(MANUAL_CTRL_X,MANUAL_CTRL_Y + 2*(MLP_BUTTON_H_2 + MLP_BUTTON_DIS_3),(const TCHAR*)_TEXT("0:/transB/manualAdjP/back.bmp"),MLP_BUTTON_W_2,MLP_BUTTON_H_2);

Button * mAdjButtonPtr[MLP_BUTTON_NUM] = {&bedUp,&bedDown,&backUp,&backDown,&bedOut,&bedIn,&conveyorOut,&conveyorIn,&takeIn,&sentOut,&back};

//----------------------settingPage��ť-----------------------
Button bedOutSpeed(SPEED_SETTING_X,SPEED_SETTING_Y_1,(const TCHAR*)_TEXT("0:/transB/settingP/speedBar.bmp"),SPEED_BAR_LENGTH,SPEED_BAR_H);
Button bedInSpeed(SPEED_SETTING_X,SPEED_SETTING_Y_2,(const TCHAR*)_TEXT("0:/transB/settingP/speedBar.bmp"),SPEED_BAR_LENGTH,SPEED_BAR_H);
Button conveyorOutSpeed(SPEED_SETTING_X,SPEED_SETTING_Y_3,(const TCHAR*)_TEXT("0:/transB/settingP/speedBar.bmp"),SPEED_BAR_LENGTH,SPEED_BAR_H);
Button conveyorInSpeed(SPEED_SETTING_X,SPEED_SETTING_Y_4,(const TCHAR*)_TEXT("0:/transB/settingP/speedBar.bmp"),SPEED_BAR_LENGTH,SPEED_BAR_H);

Button save(SAVE_BUTTON_X,SAVE_BUTTON_Y,(const TCHAR*)_TEXT("0:/transB/settingP/save.bmp"),SAVE_BUTTON_H,SAVE_BUTTON_W);
Button cancel(CANCEL_BUTTON_X,CANCEL_BUTTON_Y,(const TCHAR*)_TEXT("0:/transB/settingP/cancel.bmp"),CANCEL_BUTTON_H,CANCEL_BUTTON_W);
//--------------------ҽ�ƴ�APP----------------------------
void TransferBed_APP()
{
	uint16_t tempBackcolor = BACK_COLOR;
	
	f_mount(&fs,(const TCHAR*) _TEXT("0:"), 0);
	TransBed_APPinit();
	
	
	
	while(currentApp == TRANSBED)
	{
		
		SwitchPage();
		
		switch (PageNum)
		{
			case MAIN_PAGE:
			{
				mainPageFun();
				TransBed_KeyAction();
				break;
			}
			case MANUAL_ADJUST:
			{
				manualAdjPageFun();
				break;
			}
			case SETTING:
			{
				settingPageFun();
				break;
			}
		}
		
		if(Period_Divide_Counter == 0)
			RefreshMoveState();
}
	BACK_COLOR = tempBackcolor;
	f_mount(0,(const TCHAR*) _TEXT("0:"), 0);
	Delay_ms(50);
}
//----------------------------������Ƴ�ʼ��-----------------------
void TransBed_APPinit(void)
{
	uint16_t i = 0;
	ShowTitle();
	BACK_COLOR = PAGE_BACK_COLOR ; //���ô�����ɫ
	LCD_CLearInterface(ShowTitleCmd,WHITE);
	LCD_ShowString(LONGP_STATE_X,MOVE_STATE_Y,15,15,12,(uint8_t*)"LP",1);
	LCD_ShowString(SHORTP_STATE_X,MOVE_STATE_Y,15,15,12,(uint8_t*)"SP",1);
	LCD_ShowString(CONVEYOR_STATE_X,MOVE_STATE_Y,15,15,12,(uint8_t*)"Cy",1);
	LCD_ShowString(BEDPLATE_STATE_X,MOVE_STATE_Y,15,15,12,(uint8_t*)"BP",1);
	LCD_FillSquare(LONGP_STATE_X+ICON_OFFSET_X,MOVE_STATE_Y+ICON_OFFSET_Y,ICON_SIZE,GREEN);//(70,231,5,1);
	LCD_FillSquare(SHORTP_STATE_X+ICON_OFFSET_X,MOVE_STATE_Y+ICON_OFFSET_Y,ICON_SIZE,GREEN);//(145,231,5,1);
	LCD_FillSquare(CONVEYOR_STATE_X+ICON_OFFSET_X,MOVE_STATE_Y+ICON_OFFSET_Y,ICON_SIZE,GREEN);//(220,231,5,1);
	LCD_FillSquare(BEDPLATE_STATE_X+ICON_OFFSET_X,MOVE_STATE_Y+ICON_OFFSET_Y,ICON_SIZE,GREEN);//(305,231,5,1);
		//�����
	LCD_DrawRectangle(FRAME_OFFSET,TITLE_HEIGHT + FRAME_OFFSET + 1,320-FRAME_OFFSET,BUTTON_TOP_Y);
	//��������
	for(i = 0;i<PAGE_NUM;i++)
	{
		LCD_DrawRectangle(FRAME_OFFSET+i*BUTTON_WIDTH,BUTTON_TOP_Y,FRAME_OFFSET+(i+1)*BUTTON_WIDTH,BUTTON_TOP_Y + BUTTON_HEIGHT);
		PageButtonPtr[i]->Show();
	}
	
	SetPage(MAIN_PAGE);
	mainPageInit();
}
//----------------------------�������Ƹ��˶�------------------------
void TransBed_KeyAction(void)
{

	if(key[S1].press_flag)
	{
		BedPlateMove(MOVE_OUT);
	}
	else if(key[S2].press_flag)
	{
		BedPlateMove(MOVE_IN);
	}
	else if(key[S3].press_flag)
	{
		ConveyorMove(MOVE_OUT);
	}
	else if(key[S4].press_flag)
	{
		
		ConveyorMove(MOVE_IN);
	}
	else
	{
		BedPlateMove(MOVE_STOP);
		ConveyorMove(MOVE_STOP);
	}
}


//-----------------����Ļ�·�ˢ�¸������˶�״̬-----------
void RefreshMoveState(void)
{
	LCD_FillSquare(LONGP_STATE_X+ICON_OFFSET_X,MOVE_STATE_Y+ICON_OFFSET_Y,ICON_SIZE,stateIconColor[BedHeight_State]);
	LCD_FillSquare(SHORTP_STATE_X+ICON_OFFSET_X,MOVE_STATE_Y+ICON_OFFSET_Y,ICON_SIZE,stateIconColor[Back_State]);
	LCD_FillSquare(CONVEYOR_STATE_X+ICON_OFFSET_X,MOVE_STATE_Y+ICON_OFFSET_Y,ICON_SIZE,stateIconColor[Conveyor_State]);
	LCD_FillSquare(BEDPLATE_STATE_X+ICON_OFFSET_X,MOVE_STATE_Y+ICON_OFFSET_Y,ICON_SIZE,stateIconColor[BedPlate_State]);
}
//------------------�л�ҳ��------------------------------
void SetPage(uint16_t num)
{
	PageNum = num;
	uint16_t tempPointcolor = POINT_COLOR;
	POINT_COLOR = BLACK;
	LCD_Fill(FRAME_OFFSET+1,TITLE_HEIGHT + FRAME_OFFSET + 2,320-FRAME_OFFSET - 1,BUTTON_TOP_Y - 1,BACK_COLOR);  //��������
	LCD_DrawLine(FRAME_OFFSET,BUTTON_TOP_Y,FRAME_OFFSET+PAGE_NUM*BUTTON_WIDTH,BUTTON_TOP_Y);
	//����ѡ�е�ҳ��ȥ����ť�ϱ߿�
	POINT_COLOR = BACK_COLOR;
	LCD_DrawLine(FRAME_OFFSET+num*BUTTON_WIDTH + 1,BUTTON_TOP_Y,FRAME_OFFSET+(num+1)*BUTTON_WIDTH - 1,BUTTON_TOP_Y);// ��1��1��ֹ������������
	POINT_COLOR = tempPointcolor;
}
//-------------�ж��Ƿ��л�ҳ��----------------------------
void SwitchPage(void)
{
	uint16_t i = 0;
	for(i = 0;i < PAGE_NUM;i++ )
	{
		if(PageButtonPtr[i] ->ButtonIfBeSelected() == 2)
		{
			PageNum = i;
			SetPage(i);
			PageButtonPtr[i] -> buttonFun();
		}
	}
}
//-------------mainPageҳ���ʼ��-------------------
void mainPageInit(void)
{
	LCD_ShowBMP(MESG_PAD_X,MESG_PAD_Y,(const TCHAR*)_TEXT("0:/transB/mainP/mesgPad.bmp"),NULL);
	POINT_COLOR = BLACK;
	LCD_ShowSymStr(lcddev.width/2,35,150,17,16,(u8*)("Auto Deliver"),1);
	LCD_DrawRectangle(MESG_PAD_X,MESG_PAD_Y,MESG_PAD_X + MESG_PAD_WIDTH,MESG_PAD_Y + MESG_PAD_HEIGHT);
	autoSent.Show();
	autoTake.Show();
	//autoNext.Show();
	//autoCancel.Show();
	if(settingData[0] != SET_DATA_EAXM_OK)
	{
		LCD_ShowString(FRAME_OFFSET + 2,30,80,15,12,(u8*)("Data error!!"),1);
	}
	
}
//-------------manualAdjPageҳ���ʼ��-------------------
void mAdjPageInit(void)
{
	uint16_t i = 0;

	POINT_COLOR = BLACK;
	for(i = 0;i<MLP_BUTTON_NUM;i ++ )
		mAdjButtonPtr[i]->Show();
	LCD_ShowSymStr(lcddev.width/2,35,150,17,16,(u8*)("Manual Adjust"),1);
	LCD_ShowSymStr(BED_UP_DOWN_X + MLP_BUTTON_W_1/2,BED_UP_DOWN_Y - 10,60,17,12,(u8*)("Height"),1);
	LCD_ShowSymStr(BACK_UP_DOWN_X + MLP_BUTTON_W_1/2,BACK_UP_DOWN_Y - 10,60,17,12,(u8*)("Back"),1);
	LCD_ShowSymStr(BED_IN_OUT_X + MLP_BUTTON_W_1 + MLP_BUTTON_DIS_2/2,BED_IN_OUT_Y - 10,60,17,12,(u8*)("Bedplate"),1);
	LCD_ShowSymStr(CONV_IN_OUT_X + MLP_BUTTON_W_1 + MLP_BUTTON_DIS_2/2,CONV_IN_OUT_Y - 10,60,17,12,(u8*)("Conveyor"),1);

}
//-------------SetiingPageҳ���ʼ��-------------------
void setPageInit(void)
{
	
	
	POINT_COLOR = BLACK;
	LCD_ShowSymStr(lcddev.width/2,35,150,17,16,(u8*)("Setting"),1);
	save.Show();
	cancel.Show();
	bedOutSpeed.Show();
	bedInSpeed.Show();
	conveyorOutSpeed.Show();
	conveyorInSpeed.Show();
	LCD_ShowString(SPEED_SETTING_X - 10,SPEED_SETTING_Y_1 - 15,80,13,12,(u8*)("Bedplate speed"),1);
	LCD_ShowString(SPEED_SETTING_X - 10,SPEED_SETTING_Y_3 - 15,80,13,12,(u8*)("Conveyor speed"),1);
	
	LCD_ShowString(SPEED_SETTING_X - 10,SPEED_SETTING_Y_1 + 4,80,13,12,(u8*)("O"),1);
	LCD_ShowString(SPEED_SETTING_X - 10,SPEED_SETTING_Y_2 + 4,80,13,12,(u8*)("I"),1);
	LCD_ShowString(SPEED_SETTING_X - 10,SPEED_SETTING_Y_3 + 4,80,13,12,(u8*)("O"),1);
	LCD_ShowString(SPEED_SETTING_X - 10,SPEED_SETTING_Y_4 + 4,80,13,12,(u8*)"I",1);
	
	LCD_ShowBMP(SPEED_SETTING_X + 10*(settingData[BED_OUT_SPEAD_LEVEL] - 1),SPEED_SETTING_Y_1,(const TCHAR*)_TEXT("0:/transB/settingP/speedBlock.bmp"),NULL);
	LCD_ShowBMP(SPEED_SETTING_X + 10*(settingData[BED_IN_SPEAD_LEVEL] - 1),SPEED_SETTING_Y_2,(const TCHAR*)_TEXT("0:/transB/settingP/speedBlock.bmp"),NULL);
	LCD_ShowBMP(SPEED_SETTING_X + 10*(settingData[CONVEYOR_OUT_SPEED_LEVEL] - 1),SPEED_SETTING_Y_3,(const TCHAR*)_TEXT("0:/transB/settingP/speedBlock.bmp"),NULL);
	LCD_ShowBMP(SPEED_SETTING_X + 10*(settingData[CONVEYOR_IN_SPEED_LEVEL] - 1),SPEED_SETTING_Y_4,(const TCHAR*)_TEXT("0:/transB/settingP/speedBlock.bmp"),NULL);
	
	LCD_ShowNum(SPEED_SETTING_X + SPEED_BAR_LENGTH + 5,SPEED_SETTING_Y_1 + 4,settingData[BED_OUT_SPEAD_LEVEL],2,12);
	LCD_ShowNum(SPEED_SETTING_X + SPEED_BAR_LENGTH + 5,SPEED_SETTING_Y_2 + 4,settingData[BED_IN_SPEAD_LEVEL],2,12);
	LCD_ShowNum(SPEED_SETTING_X + SPEED_BAR_LENGTH + 5,SPEED_SETTING_Y_3 + 4,settingData[CONVEYOR_OUT_SPEED_LEVEL],2,12);
	LCD_ShowNum(SPEED_SETTING_X + SPEED_BAR_LENGTH + 5,SPEED_SETTING_Y_4 + 4,settingData[CONVEYOR_IN_SPEED_LEVEL],2,12);
}	
//-------------mainPage����-------------------------
void mainPageFun(void)
{
	if(autoSent.ButtonIfBeSelected() == 2)
		AutoSentPatient();	
	else if(autoTake.ButtonIfBeSelected() == 2)
		AutoTakePatient();
}
//-----------manualAdj����--------------------------
void manualAdjPageFun(void)
{
	if(Period_Divide_Counter == 1) //����ÿ��ѭ����ִ�У�
	{
		//�߶ȵ��ڰ�ť
		if((bedUp.ButtonIfBeSelected() & 0x01)!=0)  //������ֵ��1��3ʱ�������ɿ�ǰ����Ч���۴�����������
		{
			BedHeightAdjust(MOVE_UP);
		}
		else if((bedDown.ButtonIfBeSelected()& 0x01)!=0)
		{
			BedHeightAdjust(MOVE_DOWN);
		}
		//�������ڰ�ť
		else if((backUp.ButtonIfBeSelected()& 0x01)!=0)
		{
			BackAdjust(MOVE_UP);
		}
		else if((backDown.ButtonIfBeSelected()& 0x01)!=0)
		{
			BackAdjust(MOVE_DOWN);
		}
		//��������ջذ�ť
		else if((bedOut.ButtonIfBeSelected()& 0x01)!=0)
		{
			BedPlateMove(MOVE_OUT);
		}
		else if((bedIn.ButtonIfBeSelected()& 0x01)!=0)
		{
			BedPlateMove(MOVE_IN);
		}
		//���ʹ����ư�ť
		else if((conveyorOut.ButtonIfBeSelected()& 0x01)!=0)
		{
			ConveyorMove(MOVE_OUT);
		}
		else if((conveyorIn.ButtonIfBeSelected()& 0x01)!=0)
		{
			ConveyorMove(MOVE_IN);
		}
		else if((takeIn.ButtonIfBeSelected()& 0x01)!=0)
		{
			BedPlateMove(MOVE_OUT);
			ConveyorMove(MOVE_IN);
		}
		else if((sentOut.ButtonIfBeSelected()& 0x01)!=0)
		{
			BedPlateMove(MOVE_IN);
			ConveyorMove(MOVE_OUT);
		}
		else if((back.ButtonIfBeSelected()& 0x01)!=0)
		{
			BedPlateMove(MOVE_IN);
		}
		else
		{
			BedHeightAdjust(MOVE_STOP);
			BackAdjust(MOVE_STOP);
			ConveyorMove(MOVE_STOP);
			BedPlateMove(MOVE_STOP);
		}
	}

}
//------------------------------settingPage����-------------------------------
void settingPageFun(void)
{
	uint16_t i = 0;
	if(Period_Divide_Counter == 1)
	{
		//�ٶ���
		if(bedOutSpeed.ButtonIfBeSelected() == 1)
		{
			settingData[BED_OUT_SPEAD_LEVEL] = uint16_t((TS_XY.x - SPEED_SETTING_X)/10) + 1;
			bedOutSpeed.Show();
			LCD_ShowBMP(SPEED_SETTING_X + 10*(settingData[BED_OUT_SPEAD_LEVEL] - 1),SPEED_SETTING_Y_1,(const TCHAR*)_TEXT("0:/transB/settingP/speedBlock.bmp"),NULL);
			LCD_ShowNum(SPEED_SETTING_X + SPEED_BAR_LENGTH + 5,SPEED_SETTING_Y_1 + 4,settingData[BED_OUT_SPEAD_LEVEL],2,12);
		}
		else if(bedInSpeed.ButtonIfBeSelected() == 1)
		{
			settingData[BED_IN_SPEAD_LEVEL] = uint16_t((TS_XY.x - SPEED_SETTING_X)/10) + 1;
			bedInSpeed.Show();
			LCD_ShowBMP(SPEED_SETTING_X + 10*(settingData[BED_IN_SPEAD_LEVEL] - 1),SPEED_SETTING_Y_2,(const TCHAR*)_TEXT("0:/transB/settingP/speedBlock.bmp"),NULL);
			LCD_ShowNum(SPEED_SETTING_X + SPEED_BAR_LENGTH + 5,SPEED_SETTING_Y_2 + 4,settingData[BED_IN_SPEAD_LEVEL],2,12);
		}
		else if(conveyorOutSpeed.ButtonIfBeSelected() == 1)
		{
			settingData[CONVEYOR_OUT_SPEED_LEVEL] = uint16_t((TS_XY.x - SPEED_SETTING_X)/10) + 1;
			conveyorOutSpeed.Show();
			LCD_ShowBMP(SPEED_SETTING_X + 10*(settingData[CONVEYOR_OUT_SPEED_LEVEL] - 1),SPEED_SETTING_Y_3,(const TCHAR*)_TEXT("0:/transB/settingP/speedBlock.bmp"),NULL);
			LCD_ShowNum(SPEED_SETTING_X + SPEED_BAR_LENGTH + 5,SPEED_SETTING_Y_3 + 4,settingData[CONVEYOR_OUT_SPEED_LEVEL],2,12);
		}
		else if(conveyorInSpeed.ButtonIfBeSelected() == 1)
		{
			settingData[CONVEYOR_IN_SPEED_LEVEL] = uint16_t((TS_XY.x - SPEED_SETTING_X)/10) + 1;		
			conveyorInSpeed.Show();
			LCD_ShowBMP(SPEED_SETTING_X + 10*(settingData[CONVEYOR_IN_SPEED_LEVEL] - 1),SPEED_SETTING_Y_4,(const TCHAR*)_TEXT("0:/transB/settingP/speedBlock.bmp"),NULL);
			LCD_ShowNum(SPEED_SETTING_X + SPEED_BAR_LENGTH + 5,SPEED_SETTING_Y_4 + 4,settingData[CONVEYOR_IN_SPEED_LEVEL],2,12);
		}
		
		//  ���水ť�������ݴ���Flash
		else if(save.ButtonIfBeSelected () == 2)
		{
			settingData[0] = SET_DATA_EAXM_OK;
			if(FLASH_Erase(BED_SPEED_DATA_ADDRESS,SET_DATA_NUM) == FLASH_COMPLETE)
			{
				if(FLASH_WriteData(BED_SPEED_DATA_ADDRESS,settingData,SET_DATA_NUM)== FLASH_COMPLETE)
					LCD_ShowString(240,40,80,13,12,(u8*)("Success!!"),1);
				else
					LCD_ShowString(240,40,80,13,12,(u8*)("Error!!"),1);
			}
			else
				LCD_ShowString(240,40,80,13,12,(u8*)("Error!!"),1);
		}
		// ȡ����ť�����´�Flash�ж������ݣ���ȻҪ����Ҫ�İ�ȫ�����ݼ��飩
		else if(cancel.ButtonIfBeSelected () == 2)
		{
			FLASH_Read(BED_SPEED_DATA_ADDRESS,settingData,1);
			if(settingData[0] == SET_DATA_EAXM_OK)
			{
				FLASH_Read(BED_SPEED_DATA_ADDRESS ,settingData,SET_DATA_NUM);
				for(i = BED_OUT_SPEAD_LEVEL; i <= CONVEYOR_IN_SPEED_LEVEL;i ++)
				{
					if((settingData[i] > MAX_SPPED_LEVEL)||(settingData[i] == 0))     //У���ٶȵ�λ����
					{
						settingData[i] = 1;
						settingData[0] = 0x00;
					}
					
				}

				bedOutSpeed.Show();
				bedInSpeed.Show();
				conveyorOutSpeed.Show();
				conveyorInSpeed.Show();
				LCD_ShowBMP(SPEED_SETTING_X + 10*(settingData[BED_OUT_SPEAD_LEVEL] - 1),SPEED_SETTING_Y_1,(const TCHAR*)_TEXT("0:/transB/settingP/speedBlock.bmp"),NULL);
				LCD_ShowBMP(SPEED_SETTING_X + 10*(settingData[BED_IN_SPEAD_LEVEL] - 1),SPEED_SETTING_Y_2,(const TCHAR*)_TEXT("0:/transB/settingP/speedBlock.bmp"),NULL);
				LCD_ShowBMP(SPEED_SETTING_X + 10*(settingData[CONVEYOR_OUT_SPEED_LEVEL] - 1),SPEED_SETTING_Y_3,(const TCHAR*)_TEXT("0:/transB/settingP/speedBlock.bmp"),NULL);
				LCD_ShowBMP(SPEED_SETTING_X + 10*(settingData[CONVEYOR_IN_SPEED_LEVEL] - 1),SPEED_SETTING_Y_4,(const TCHAR*)_TEXT("0:/transB/settingP/speedBlock.bmp"),NULL);
				
				LCD_ShowNum(SPEED_SETTING_X + SPEED_BAR_LENGTH + 5,SPEED_SETTING_Y_1 + 4,settingData[BED_OUT_SPEAD_LEVEL],2,12);
				LCD_ShowNum(SPEED_SETTING_X + SPEED_BAR_LENGTH + 5,SPEED_SETTING_Y_2 + 4,settingData[BED_IN_SPEAD_LEVEL],2,12);
				LCD_ShowNum(SPEED_SETTING_X + SPEED_BAR_LENGTH + 5,SPEED_SETTING_Y_3 + 4,settingData[CONVEYOR_OUT_SPEED_LEVEL],2,12);
				LCD_ShowNum(SPEED_SETTING_X + SPEED_BAR_LENGTH + 5,SPEED_SETTING_Y_4 + 4,settingData[CONVEYOR_IN_SPEED_LEVEL],2,12);
			}
			else 
				LCD_ShowString(240,40,80,13,12,(u8*)("Can't cancel!!"),1);
		}
	}
	
	Delay_ms(5);
}
//------------------------�Զ��Ӳ���-------------------------------------
Motor_Error AutoTakePatient(void)
{
	uint16_t message_X = MESG_PAD_X + 3;
	uint16_t message_Y = MESG_PAD_Y + 2;
	LCD_Fill(MESG_PAD_X+1,MESG_PAD_Y+1,MESG_PAD_X + MESG_PAD_WIDTH - 1,MESG_PAD_Y + MESG_PAD_HEIGHT - 1,WHITE);
	LCD_ShowString(message_X,message_Y,100,12,12,(u8*)("Safe Checking..."),1);
	message_Y += 14;
	LS_Read_State();
	autoCancel.Show();
	autoNext.Show();
	if((LS_State & LS_BACK_REACH_BOTTOM)!= 1)
	{
		
		LCD_ShowString(message_X,message_Y,150,12,12,(u8*)("Back haven't laid down"),1);
		message_Y += 14;
		LCD_ShowString(message_X,message_Y,150,12,12,(u8*)("Press next to lay down"),1);
		message_Y += 14;
		while(1)
		{
			if(autoNext.ButtonIfBeSelected() == 2)
			{
				LCD_ShowString(message_X,message_Y,150,12,12,(u8*)("laying down back..."),1);
				message_Y += 14;
				while(BackAdjust(MOVE_DOWN)!=REACH_BOTTOM)
				{
					if(autoCancel.ButtonIfBeSelected() == 2)
						{
							BackAdjust(MOVE_STOP);
							mainPageInit();
							return MOTOR_OK;
						}
				}
				LCD_ShowString(message_X,message_Y,150,12,12,(u8*)("Succeed!! Go on..."),1);
				message_Y += 14;
				break;
			}
			else if(autoCancel.ButtonIfBeSelected() == 2)
			{
				mainPageInit();
				return MOTOR_OK;
			}
		}
	}
	if((LS_State & LS_BED_REACH_IN)!= 1)
	{
		LCD_ShowString(message_X,message_Y,150,12,12,(u8*)("Bedplate is out"),1);
		message_Y += 14;
		LCD_ShowString(message_X,message_Y,150,12,12,(u8*)("Press next to take back"),1);
		message_Y += 14;
		while(1)
		{
			if(autoNext.ButtonIfBeSelected() == 2)
				{
					LCD_ShowString(message_X,message_Y,150,12,12,(u8*)("Taking back bedplate..."),1);
					message_Y += 14;
					while(BedPlateMove(MOVE_IN)!=REACH_INSIDE)
					{
						if(autoCancel.ButtonIfBeSelected() == 2)
						{
							BedPlateMove(MOVE_STOP);
							mainPageInit();
							return MOTOR_OK;
						}
					}
					LCD_ShowString(message_X,message_Y,150,12,12,(u8*)("Succeed!! Go on..."),1);
					message_Y += 14;
					break;
				}
				else if(autoCancel.ButtonIfBeSelected() == 2)
				{
					mainPageInit();
					return MOTOR_OK;
				}
			}
	}
	__DELAY_H
	Delay_ms(2000);
	message_Y = MESG_PAD_Y + 2;
	LCD_Fill(MESG_PAD_X+1,MESG_PAD_Y+1,MESG_PAD_X + MESG_PAD_WIDTH - 1,MESG_PAD_Y + MESG_PAD_HEIGHT - 1,WHITE);
	LCD_ShowString(message_X,message_Y,150,12,12,(u8*)("Check complete,start.."),1);
	message_Y += 14;
	while(BedPlateMove(MOVE_OUT)!=REACH_OUTSIDE)
	{
	//	ConveyorMove(MOVE_IN);
		if(autoCancel.ButtonIfBeSelected () == 2)
		{
			BedPlateMove(MOVE_STOP);
			ConveyorMove(MOVE_STOP);
			mainPageInit();
			return MOTOR_OK;
		}
	}
	LCD_ShowString(message_X,message_Y,150,12,12,(u8*)("Bedplate reach out"),1);
	message_Y += 14;
	LCD_ShowString(message_X,message_Y,150,12,12,(u8*)("Press next to continue"),1);
	message_Y += 14;
	if(message_Y > 140)
	{
		message_Y = MESG_PAD_Y + 2;
		LCD_Fill(MESG_PAD_X,MESG_PAD_Y,MESG_PAD_X + MESG_PAD_WIDTH,MESG_PAD_Y + MESG_PAD_HEIGHT,WHITE); // 
	}
	while(autoNext.ButtonIfBeSelected() != 2)
	{
		if(autoCancel.ButtonIfBeSelected () == 2)
		{
			mainPageInit();
			return MOTOR_OK;
		}
	}
	LCD_ShowString(message_X,message_Y,150,12,12,(u8*)("go on..."),1);
	message_Y += 14;
	while(BedPlateMove(MOVE_IN)!=REACH_INSIDE)
	{
		//ConveyorMove(MOVE_OUT);
		if(autoCancel.ButtonIfBeSelected () == 2)
		{
			BedPlateMove(MOVE_STOP);
			ConveyorMove(MOVE_STOP);
			mainPageInit();
			return MOTOR_OK;
		}
	}
	LCD_ShowString(message_X,message_Y,150,12,12,(u8*)("complate!!"),1);
	message_Y += 14;
	LCD_ShowString(message_X,message_Y,150,12,12,(u8*)("Press screen to return"),1);
	while(TS_XY.x == 0&&TS_XY.y == 0)
	{
	}
	mainPageInit();
	Delay_ms(100);
	return MOTOR_OK;
		
}
Motor_Error AutoSentPatient(void)
{
}