#include "common.h"

uint32_t BED_PWM_Period_ms = 1; //�����������
uint32_t BED_PWM_Period = 0;//����������ڻ���Ϊ�ļĴ���ֵ
uint16_t Conveyor_PWM_Duty = 50;//���ʹ�ռ�ձ�

//������״̬
Motion_State Conveyor_State = MOVE_STOP;
Motion_State BedPlate_State = MOVE_STOP;
Motion_State Back_State = MOVE_STOP;
Motion_State BedHeight_State = MOVE_STOP;
//--------------------------�����ʼ��-----------------------------
void MOTOR_init()
{
	uint16_t i= 0;
	//��ȡ��������
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
	}
	//��ʱ��
	RCC_APB2PeriphClockCmd(PUSHROD_PIN_CLK|BED_MOVE_PIN_CLK|CONVEYOR_PIN_CLK,ENABLE);
	RCC_APB1PeriphClockCmd(CONVEYOR_TIM_CLK|BED_MOVE_TIM_CLK,ENABLE);
	//GPIO�ڳ�ʼ��
	GPIO_InitTypeDef MOTOR_GPIO_init;
	MOTOR_GPIO_init.GPIO_Mode = GPIO_Mode_Out_PP;
	MOTOR_GPIO_init.GPIO_Pin = PUSHROD_LONG_UP_PIN|PUSHROD_LONG_DOWN_PIN|PUSHROD_SHORT_UP_PIN|PUSHROD_SHORT_DOWN_PIN;
	MOTOR_GPIO_init.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(PUSHROD_PORT,&MOTOR_GPIO_init);
	
	MOTOR_GPIO_init.GPIO_Mode = GPIO_Mode_AF_PP;
	MOTOR_GPIO_init.GPIO_Pin = CONVEYOR_OUT_PIN|CONVEYOR_IN_PIN;
	GPIO_Init(CONVEYOR_PORT,&MOTOR_GPIO_init);
	
	
	MOTOR_GPIO_init.GPIO_Pin = BED_PWM_PIN;
	GPIO_Init(BED_MOVE_PORT,&MOTOR_GPIO_init);
	MOTOR_GPIO_init.GPIO_Mode = GPIO_Mode_Out_PP;
	MOTOR_GPIO_init.GPIO_Pin = BED_DIR_PIN|BED_MOV_ENABLE_PIN;
	GPIO_Init(BED_MOVE_PORT,&MOTOR_GPIO_init);
	
	//�������PWM��ʼ��
	TIM_OCInitTypeDef MOTOR_PWM_Out_init;
	TIM_TimeBaseInitTypeDef MOTOR_PWM_Time_init;
	
	BED_PWM_Period = BED_PWM_Period_ms * (TIM_CLK/(BED_TIM_PRESCALER*settingData[BED_OUT_SPEAD_LEVEL]*1000));
	MOTOR_PWM_Out_init.TIM_OCMode = TIM_OCMode_PWM2;
	MOTOR_PWM_Out_init.TIM_OCPolarity = TIM_OCPolarity_High;
	MOTOR_PWM_Out_init.TIM_Pulse = 0;
	MOTOR_PWM_Out_init.TIM_OutputState = TIM_OutputState_Enable;
	
	MOTOR_PWM_Time_init.TIM_CounterMode = TIM_CounterMode_Up;
	MOTOR_PWM_Time_init.TIM_ClockDivision = 0;
	MOTOR_PWM_Time_init.TIM_Period = BED_PWM_Period - 1;
	MOTOR_PWM_Time_init.TIM_Prescaler = BED_TIM_PRESCALER - 1;
	TIM_TimeBaseInit(BED_MOVE_TIM,&MOTOR_PWM_Time_init);
	TIM_OC1Init(BED_MOVE_TIM,&MOTOR_PWM_Out_init);
	TIM_OC1PreloadConfig(BED_MOVE_TIM,TIM_OCPreload_Enable);
	//���ʹ����PWM��ʼ��
	MOTOR_PWM_Out_init.TIM_OCPolarity = TIM_OCPolarity_Low; //PWM2ģʽ��������>CRRxʱΪ��Ч��ƽ��TIM_OCPolarity������Ч��ƽΪ�ף�
	MOTOR_PWM_Out_init.TIM_Pulse = 0;
	MOTOR_PWM_Out_init.TIM_OutputState = TIM_OutputState_Enable;
	
	MOTOR_PWM_Time_init.TIM_Period = CONVEYOR_PERIOD - 1;
	MOTOR_PWM_Time_init.TIM_Prescaler = CONVEYOR_TIM_PRESCALER - 1;
	TIM_TimeBaseInit(CONVEYOR_TIM,&MOTOR_PWM_Time_init);
	TIM_OC1Init(CONVEYOR_TIM,&MOTOR_PWM_Out_init);
	TIM_OC3Init(CONVEYOR_TIM,&MOTOR_PWM_Out_init);
	TIM_OC1PreloadConfig(CONVEYOR_TIM,TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(CONVEYOR_TIM,TIM_OCPreload_Enable);
	
	//ʹ�ܶ˿�
	TIM_Cmd(CONVEYOR_TIM,ENABLE);
	TIM_Cmd(BED_MOVE_TIM,ENABLE);
	
}

//---------------------�������/�ջؿ���----------------------------
Motor_Error BedPlateMove(Motion_State motion)
{
	if(motion == MOVE_OUT)
	{
		if(GPIO_ReadInputDataBit(LIMIT_SWITCH_PORT,LS_BED_OUTSIDE_PIN))         //��λ
		{
			BedPlate_State = MOVE_STOP;
			GPIO_SetBits(BED_MOVE_PORT,BED_MOV_ENABLE_PIN);
			TIM_SetCompare1(BED_MOVE_TIM,0);
			return REACH_OUTSIDE;
		}
		else
		{
			if(BedPlate_State != MOVE_OUT)
			{
				BedPlate_State = MOVE_OUT;
				GPIO_ResetBits(BED_MOVE_PORT,BED_MOV_ENABLE_PIN);
				TIM_Cmd(BED_MOVE_TIM,DISABLE);
				BED_PWM_Period = BED_PWM_Period_ms * (TIM_CLK/(BED_TIM_PRESCALER*settingData[BED_OUT_SPEAD_LEVEL]*1000));
				TIM_SetAutoreload(BED_MOVE_TIM,BED_PWM_Period);
				TIM_SetCompare1(BED_MOVE_TIM,BED_PWM_Period/2-1);
				GPIO_ResetBits(BED_MOVE_PORT,BED_DIR_PIN);
				TIM_Cmd(BED_MOVE_TIM,ENABLE);
			}
			else 
			{
			}
		}
	}
	else if(motion == MOVE_IN)
	{
		if(GPIO_ReadInputDataBit(LIMIT_SWITCH_PORT,LS_BED_INSIDE_PIN))     //��λ
		{
			BedPlate_State = MOVE_STOP;
			GPIO_SetBits(BED_MOVE_PORT,BED_MOV_ENABLE_PIN);
			TIM_SetCompare1(BED_MOVE_TIM,0);
			return REACH_INSIDE;
		}
		else
		{
			if(BedPlate_State != MOVE_IN)
			{
				BedPlate_State = MOVE_IN;
				GPIO_ResetBits(BED_MOVE_PORT,BED_MOV_ENABLE_PIN);
				TIM_Cmd(BED_MOVE_TIM,DISABLE);
				BED_PWM_Period = BED_PWM_Period_ms * (TIM_CLK/(BED_TIM_PRESCALER * settingData[BED_IN_SPEAD_LEVEL] * 1000));
				TIM_SetAutoreload(BED_MOVE_TIM,BED_PWM_Period);
				TIM_SetCompare1(BED_MOVE_TIM,BED_PWM_Period/2-1);
				GPIO_SetBits(BED_MOVE_PORT,BED_DIR_PIN);
				TIM_Cmd(BED_MOVE_TIM,ENABLE);
			}
		}
	}
	else
	{
		BedPlate_State = MOVE_STOP;
		GPIO_SetBits(BED_MOVE_PORT,BED_MOV_ENABLE_PIN);
		TIM_SetCompare1(BED_MOVE_TIM,0);

	}
	return MOTOR_OK;
}

//--------------------���ʹ��˶�����-----------------------------
Motor_Error ConveyorMove(Motion_State motion)//�������٣�����㶨ռ�ձ�
{
	uint32_t Conveyor_Duty_temp = (Conveyor_PWM_Duty*CONVEYOR_PERIOD/100) -1;
	if(motion == MOVE_OUT)
	{
		if(Conveyor_State != MOVE_OUT)
		{
			Conveyor_State = MOVE_OUT;
			TIM_SetCompare1(CONVEYOR_TIM,Conveyor_Duty_temp);
			TIM_SetCompare3(CONVEYOR_TIM,0);
		}
	}
	else if(motion == MOVE_IN)
	{
		if(Conveyor_State != MOVE_IN)
		{
			Conveyor_State = MOVE_IN;
			TIM_SetCompare3(CONVEYOR_TIM,Conveyor_Duty_temp);
			TIM_SetCompare1(CONVEYOR_TIM,0);
		}
	}
	else
	{
		Conveyor_State = MOVE_STOP;
		TIM_SetCompare3(CONVEYOR_TIM,0);
		TIM_SetCompare1(CONVEYOR_TIM,0);
	}
	return MOTOR_OK;
}

//--------------------�������ڿ���--------------------------------
Motor_Error BackAdjust(Motion_State motion)
{
	if(motion == MOVE_UP)
	{
		if(GPIO_ReadInputDataBit(LIMIT_SWITCH_PORT,LS_BACK_TOP_PIN))     //��λ
		{
			Back_State = MOVE_STOP;
			GPIO_ResetBits(PUSHROD_PORT,PUSHROD_SHORT_DOWN_PIN);
			GPIO_ResetBits(PUSHROD_PORT,PUSHROD_SHORT_UP_PIN);
			return REACH_TOP;
		}
		Back_State = MOVE_UP;
		GPIO_SetBits(PUSHROD_PORT,PUSHROD_SHORT_UP_PIN);
		GPIO_ResetBits(PUSHROD_PORT,PUSHROD_SHORT_DOWN_PIN);
	}
	else if(motion == MOVE_DOWN)
	{
		if(GPIO_ReadInputDataBit(LIMIT_SWITCH_PORT,LS_BACK_BOTTOM_PIN))     //��λ
		{
			Back_State = MOVE_STOP;
			GPIO_ResetBits(PUSHROD_PORT,PUSHROD_SHORT_DOWN_PIN);
			GPIO_ResetBits(PUSHROD_PORT,PUSHROD_SHORT_UP_PIN);
			return REACH_BOTTOM;
		}
		Back_State = MOVE_DOWN;
		GPIO_SetBits(PUSHROD_PORT,PUSHROD_SHORT_DOWN_PIN);
		GPIO_ResetBits(PUSHROD_PORT,PUSHROD_SHORT_UP_PIN);
	}
	else
	{
		Back_State = MOVE_STOP;
		GPIO_ResetBits(PUSHROD_PORT,PUSHROD_SHORT_DOWN_PIN);
		GPIO_ResetBits(PUSHROD_PORT,PUSHROD_SHORT_UP_PIN);
	}
	return MOTOR_OK;
}


//-----------------------����߶ȿ���--------------------------------
Motor_Error BedHeightAdjust(Motion_State motion)
{
	if(motion == MOVE_UP)
	{
		if(GPIO_ReadInputDataBit(LIMIT_SWITCH_PORT,LS_BED_TOP_PIN))     //��λ
		{
			BedHeight_State = MOVE_STOP;
			GPIO_ResetBits(PUSHROD_PORT,PUSHROD_LONG_DOWN_PIN);
			GPIO_ResetBits(PUSHROD_PORT,PUSHROD_LONG_UP_PIN);
			return REACH_TOP;
		}
		BedHeight_State = MOVE_UP;
		GPIO_SetBits(PUSHROD_PORT,PUSHROD_LONG_UP_PIN);
		GPIO_ResetBits(PUSHROD_PORT,PUSHROD_LONG_DOWN_PIN);
	}
	else if(motion == MOVE_DOWN)
	{
		if(GPIO_ReadInputDataBit(LIMIT_SWITCH_PORT,LS_BED_BOTTOM_PIN))     //��λ
		{
			BedHeight_State = MOVE_STOP;
			GPIO_ResetBits(PUSHROD_PORT,PUSHROD_LONG_DOWN_PIN);
			GPIO_ResetBits(PUSHROD_PORT,PUSHROD_LONG_UP_PIN);
			return REACH_BOTTOM;
		}
		BedHeight_State = MOVE_DOWN;
		GPIO_SetBits(PUSHROD_PORT,PUSHROD_LONG_DOWN_PIN);
		GPIO_ResetBits(PUSHROD_PORT,PUSHROD_LONG_UP_PIN);
	}
	else
	{
		BedHeight_State = MOVE_STOP;
		GPIO_ResetBits(PUSHROD_PORT,PUSHROD_LONG_DOWN_PIN);
		GPIO_ResetBits(PUSHROD_PORT,PUSHROD_LONG_UP_PIN);
	}
	return MOTOR_OK;
}

