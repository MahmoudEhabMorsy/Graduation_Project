#include "motor_rc.h"
//static uint8 g_direction_current_state = "S" ;
//static uint8 g_direction_previous_state = "S" ;

void PWM_Timer0_Init(unsigned char set_duty_cycle) {
	TCNT0 = 0; //Set Timer Initial v	alue

	OCR0 = set_duty_cycle; // Set Compare Value

	DDRB = DDRB | (1 << PB3); //set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS01);
}

void DC_Motor_Init(void) {
	/*setup the direction for motor1 pins through the GPIO driver.*/
	GPIO_setupPinDirection(DC_MOTOR_PORT, MOTOR1_PIN1, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT, MOTOR1_PIN2, PIN_OUTPUT);
	/*setup the direction for motor2 pins through the GPIO driver.*/
	GPIO_setupPinDirection(DC_MOTOR_PORT, MOTOR2_PIN1, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT, MOTOR2_PIN2, PIN_OUTPUT);
	/*setup the direction for motor3 pins through the GPIO driver.*/
	GPIO_setupPinDirection(DC_MOTOR_PORT, MOTOR3_PIN1, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT, MOTOR3_PIN2, PIN_OUTPUT);
	/*setup the direction for motor4 pins through the GPIO driver.*/
	GPIO_setupPinDirection(DC_MOTOR_PORT, MOTOR4_PIN1, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT, MOTOR4_PIN2, PIN_OUTPUT);

	/*Stop at the DC-Motor at the beginning through the GPIO driver.*/
	set_car_direction(Brake);
}
void set_motor_direction(Motor_ID motor, Wheel_directions direction) {
		switch (motor) {
	case MOTOR1:
		switch (direction) {
		case CLOCKWISE:
			DC_MOTOR_PORT |= (1 << MOTOR1_PIN1);
			DC_MOTOR_PORT &= ~(1 << MOTOR1_PIN2);
			break;
		case ANTI_CLOCKWISE:
			DC_MOTOR_PORT &= ~(1 << MOTOR1_PIN1);
			DC_MOTOR_PORT |= (1 << MOTOR1_PIN2);
			break;
		default:
			DC_MOTOR_PORT &= ~(1 << MOTOR1_PIN1);
			DC_MOTOR_PORT &= ~(1 << MOTOR1_PIN2);
			break;
		}
		break;

	case MOTOR2:
		switch (direction) {
		case CLOCKWISE:
			DC_MOTOR_PORT |= (1 << MOTOR2_PIN1);
			DC_MOTOR_PORT &= ~(1 << MOTOR2_PIN2);
			break;
		case ANTI_CLOCKWISE:
			DC_MOTOR_PORT &= ~(1 << MOTOR2_PIN1);
			DC_MOTOR_PORT |= (1 << MOTOR2_PIN2);
			break;
		default:
			DC_MOTOR_PORT &= ~(1 << MOTOR2_PIN1);
			DC_MOTOR_PORT &= ~(1 << MOTOR2_PIN2);
			break;
		}
		break;

	case MOTOR3:
		switch (direction) {
		case CLOCKWISE:
			DC_MOTOR_PORT |= (1 << MOTOR3_PIN1);
			DC_MOTOR_PORT &= ~(1 << MOTOR3_PIN2);
			break;
		case ANTI_CLOCKWISE:
			DC_MOTOR_PORT &= ~(1 << MOTOR3_PIN1);
			DC_MOTOR_PORT |= (1 << MOTOR3_PIN2);
			break;
		default:
			DC_MOTOR_PORT &= ~(1 << MOTOR3_PIN1);
			DC_MOTOR_PORT &= ~(1 << MOTOR3_PIN2);
			break;
		}
		break;

	case MOTOR4:
		switch (direction) {
		case CLOCKWISE:
			DC_MOTOR_PORT |= (1 << MOTOR4_PIN1);
			DC_MOTOR_PORT &= ~(1 << MOTOR4_PIN2);
			break;
		case ANTI_CLOCKWISE:
			DC_MOTOR_PORT &= ~(1 << MOTOR4_PIN1);
			DC_MOTOR_PORT |= (1 << MOTOR4_PIN2);
			break;
		default:
			DC_MOTOR_PORT &= ~(1 << MOTOR4_PIN1);
			DC_MOTOR_PORT &= ~(1 << MOTOR4_PIN2);
			break;
		}
		break;

	default:
		/* Do Nothing */
		break;
}
}

void set_car_direction(Car_directions Car_direction) {
	switch (Car_direction) {
	case Forward: {
		set_motor_direction(MOTOR1, CLOCKWISE);
		set_motor_direction(MOTOR2, CLOCKWISE);
		set_motor_direction(MOTOR3, CLOCKWISE);
		set_motor_direction(MOTOR4, CLOCKWISE);
		break;
	}

	case Backward: {
		set_motor_direction(MOTOR1, ANTI_CLOCKWISE);
		set_motor_direction(MOTOR2, ANTI_CLOCKWISE);
		set_motor_direction(MOTOR3, ANTI_CLOCKWISE);
		set_motor_direction(MOTOR4, ANTI_CLOCKWISE);
		break;
	}
	case Right: {
		set_motor_direction(MOTOR1, CLOCKWISE);
		set_motor_direction(MOTOR2, CLOCKWISE);
		set_motor_direction(MOTOR3, CLOCKWISE);
		set_motor_direction(MOTOR4, STOP);
		break;
	}
	case Left: {
		set_motor_direction(MOTOR1, CLOCKWISE);
		set_motor_direction(MOTOR2, CLOCKWISE);
		set_motor_direction(MOTOR4, CLOCKWISE);
		set_motor_direction(MOTOR3, STOP);
		
		break;
	}
	case Left_Back: {
		set_motor_direction(MOTOR1, ANTI_CLOCKWISE);
		set_motor_direction(MOTOR2, ANTI_CLOCKWISE);
		set_motor_direction(MOTOR4, ANTI_CLOCKWISE);
		set_motor_direction(MOTOR3, STOP);
		
		break;
	}
	case Right_Back: {
			set_motor_direction(MOTOR1, ANTI_CLOCKWISE);
			set_motor_direction(MOTOR2, ANTI_CLOCKWISE);
			set_motor_direction(MOTOR3, ANTI_CLOCKWISE);
			set_motor_direction(MOTOR4, STOP);
			break;
		}
	case Brake: {
		set_motor_direction(MOTOR1, STOP);
		set_motor_direction(MOTOR2, STOP);
		set_motor_direction(MOTOR3, STOP);
		set_motor_direction(MOTOR4, STOP);
		break;
	}
	}
}

void move_car(void) {
	uint8 car_info = HC05_receiveByte();
	switch (car_info) {
	case 'S':
	case 'D':
	{
		set_car_direction(Brake);
		//g_direction_current_state = g_direction_previous_state;

	}
		break;
	case 'F': {
		set_car_direction(Forward);
		//g_direction_current_state = "F";
	}
		break;
	case 'B': {
		set_car_direction(Backward);
		//g_direction_current_state = "B";
	}
		break;
	case 'H': {
			set_car_direction(Left_Back);
		}
		break;
	case 'J': {
				set_car_direction(Right_Back);
				//g_direction_current_state = "B";
			}
			break;
	case 'L':
	case 'G':
	{
		set_car_direction(Left);
		//g_direction_current_state = "L";
	}
		break;
	case 'R':
	case 'I':{
		set_car_direction(Right);
		//g_direction_current_state = "L";
	}
		break;
	case '0': {
		PWM_Timer0_Init(speed_0);
	}
		break;
	case '1': {
		PWM_Timer0_Init(speed_10);
	}
		break;
	case '2': {
		PWM_Timer0_Init(speed_20);
	}
		break;
	case '3': {
		PWM_Timer0_Init(speed_30);
	}
		break;
	case '4': {
		PWM_Timer0_Init(speed_40);
	}
		break;
	case '5': {
		PWM_Timer0_Init(speed_50);
	}
		break;
	case '6': {
		PWM_Timer0_Init(speed_60);
	}
		break;
	case '7': {
		PWM_Timer0_Init(speed_70);
	}
		break;
	case '8': {
		PWM_Timer0_Init(speed_80);
	}
		break;
	case '9': {
		PWM_Timer0_Init(speed_90);
	}
		break;
	case 'q': {
		PWM_Timer0_Init(speed_100);
	}
		break;
	}

}
