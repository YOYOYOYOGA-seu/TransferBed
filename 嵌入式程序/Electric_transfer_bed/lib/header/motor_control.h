#ifndef __MOTOR_CONTROL_H
#define __MOTOR_CONTROL_H
#endif
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x_conf.h"
#define PUSHROD_PORT GPIOG
#define PUSHROD_LONG_UP_PIN GPIO_Pin_4
#define PUSHROD_LONG_DOWN_PIN GPIO_Pin_2
#define PUSHROD_SHORT_UP_PIN GPIO_Pin_6
#define PUSHROD_SHORT_DOWN_PIN GPIO_Pin_8
#define PUSHROD_PIN_CLK RCC_APB2Periph_GPIOG

#define CONVEYOR_PORT GPIOB
#define CONVEYOR_OUT_PIN GPIO_Pin_6
#define CONVEYOR_IN_PIN GPIO_Pin_8
#define CONVEYOR_TIM TIM4
#define CONVEYOR_PIN_CLK RCC_APB2Periph_GPIOB
#define CONVEYOR_TIM_CLK RCC_APB1Periph_TIM4
#define CONVEYOR_TIM_PRESCALER  64
#define CONVEYOR_PERIOD TIM_CLK/(CONVEYOR_TIM_PRESCALER * 1000) //PWMÖÜÆÚÎª1ms

#define BED_MOVE_PORT GPIOA
#define BED_MOV_ENABLE_PIN GPIO_Pin_5
#define BED_PWM_PIN GPIO_Pin_6
#define BED_DIR_PIN GPIO_Pin_7
#define BED_MOVE_TIM TIM3
#define BED_MOVE_PIN_CLK RCC_APB2Periph_GPIOA
#define BED_MOVE_TIM_CLK RCC_APB1Periph_TIM3
#define BED_TIM_PRESCALER  64


typedef enum 
{
	MOTOR_OK =0,
	REACH_TOP,
	REACH_BOTTOM,
	REACH_OUTSIDE,
	REACH_INSIDE,
	BACK_IS_UP
}Motor_Error;

typedef enum
{
	MOVE_STOP = 0,
	MOVE_OUT = 1,
	MOVE_UP = 1,
	MOVE_IN = 2,
	MOVE_DOWN = 2
}Motion_State;

extern uint32_t BED_PWM_Period_us;
extern uint32_t BED_PWM_Period;
extern uint16_t Conveyor_PWM_Duty;
extern Motion_State Conveyor_State;
extern Motion_State BedPlate_State;
extern Motion_State Back_State;
extern Motion_State BedHeight_State;

void MOTOR_init(void);
Motor_Error BackAdjust(Motion_State motion);
Motor_Error BedHeightAdjust(Motion_State motion);
Motor_Error BedPlateMove(Motion_State motion);
Motor_Error ConveyorMove(Motion_State motion);


Motor_Error BedSafetyCheck(void);



#ifdef __cplusplus
 }
#endif
