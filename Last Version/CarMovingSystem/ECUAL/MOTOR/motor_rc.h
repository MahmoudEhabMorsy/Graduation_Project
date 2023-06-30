#ifndef RC_MOTOR_H_
#define RC_MOTOR_H_

/*******************************************************************************
*                               File Dependency                                *
*******************************************************************************/
#include "../HC05/hc05.h"
#include "../../MCAL/DIO/dio.h"
#include "../../MCAL/UART/uart.h"
#include "../../MCAL/INTERRUPTS/interrupts.h"

/*******************************************************************************
*                              Memory Mapping                                  *
*******************************************************************************/
			/*--TIMER0 PWM--*/
#define TCNT0 (*(volatile uint8*)(0x52))
#define OCR0 (*(volatile uint8*)(0x5C))

#define TCCR0 (*(volatile uint8_t *)(0x53))
#define WGM00 6
#define WGM01 3
#define COM01 5
#define CS01 1


/*******************************************************************************
*                                  Definitions                                 *
*******************************************************************************/
#define DC_MOTOR_PORT PORTA
#define REAR_RIGHT_MOTOR_PIN1 PIN0_ID
#define REAR_RIGHT_MOTOR_PIN2 PIN1_ID
#define REAR_LEFT_MOTOR_PIN1 PIN2_ID
#define REAR_LEFT_MOTOR_PIN2 PIN3_ID
#define FRONT_RIGHT_MOTOR_PIN1 PIN4_ID
#define FRONT_RIGHT_MOTOR_PIN2 PIN5_ID
#define FRONT_LEFT_MOTOR_PIN1 PIN6_ID
#define FRONT_LEFT_MOTOR_PIN2 PIN7_ID
#define INTERRUPT_TESTCASE_PORT PORTD		//Will change later
#define INTERRUPT_TESTCASE_PIN PIN2_ID		//will change later

#define SPEED_0 0
#define SPEED_10 16
#define SPEED_20 32
#define SPEED_30 64
#define SPEED_40 80
#define SPEED_50 128
#define SPEED_60 144
#define SPEED_70 176
#define SPEED_80 208
#define SPEED_90 224
#define SPEED_100 255
#define SPEED_SAFE_LIMIT SPEED_70

#define SPEED_IS_LIMITED 1
#define SPEED_IS_NOT_LIMITED 0

/*******************************************************************************
*                  Variables Sharing and Data Types definitions                *
*******************************************************************************/
extern uint8 u8_speedIsLimited;
extern volatile uint8 u8_severeTiresStateFlag;

typedef struct
{
	uint8 gearState;
	uint8 carSpeed;
}carState;

extern carState t_carState;


typedef enum{
	STOP, CLOCKWISE, ANTI_CLOCKWISE
}Wheel_directions;

typedef enum{
	REAR_RIGHT_MOTOR, REAR_LEFT_MOTOR, FRONT_RIGHT_MOTOR ,FRONT_LEFT_MOTOR
}Motor_ID;

typedef enum{
	FORWARD, BACKWARD, RIGHT, LEFT, LEFT_BACK, RIGHT_BACK, BRAKE
}Car_directions;

/*******************************************************************************
*                             Functions Prototypes                             *
*******************************************************************************/
void PWM_Timer0_Init(unsigned char set_duty_cycle);

void DC_Motor_Init(void);

void set_motor_direction(uint8_t motor, uint8_t direction);

void set_car_direction(Car_directions Car_direction);

carState move_car(void);

void set_Car_State(carState state);

void keep_Car_Safe(void);

#endif 
