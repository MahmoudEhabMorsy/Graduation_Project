#ifndef RC_MOTOR_H_
#define RC_MOTOR_H_

#include "gpio.h"
#include "std_types.h"
#include "common_macros.h"
#include "avr/io.h"
#include "uart.h"




#define DC_MOTOR_PORT PORTA
#define MOTOR1_PIN1 PIN0_ID
#define MOTOR1_PIN2 PIN1_ID
#define MOTOR2_PIN1 PIN0_ID
#define MOTOR2_PIN2 PIN1_ID
#define MOTOR3_PIN1 PIN4_ID
#define MOTOR3_PIN2 PIN5_ID
#define MOTOR4_PIN1 PIN6_ID
#define MOTOR4_PIN2 PIN7_ID

#define speed_0 0
#define speed_10 16
#define speed_20 32
#define speed_30 64
#define speed_40 80
#define speed_50 128
#define speed_60 144
#define speed_70 176
#define speed_80 208
#define speed_90 224
#define speed_100 255




typedef enum{
	STOP, CLOCKWISE, ANTI_CLOCKWISE
}Wheel_directions;
typedef enum{
	MOTOR1, MOTOR2, MOTOR3 ,MOTOR4
}Motor_ID;

typedef enum{
	Forward, Backward, Right ,Left,Left_Back,Right_Back , Brake
}Car_directions;


void PWM_Timer0_Init(unsigned char set_duty_cycle);
void DC_Motor_Init(void);
void set_motor_direction(uint8_t motor, uint8_t direction);
void set_car_direction(Car_directions Car_direction);
void move_car(void);

#endif 
