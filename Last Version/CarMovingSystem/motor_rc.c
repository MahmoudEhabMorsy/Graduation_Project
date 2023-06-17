#include "motor_rc.h"
//static uint8 g_direction_current_state = "S" ;
//static uint8 g_direction_previous_state = "S" ;

uint8 u8_speedIsLimited = SPEED_IS_NOT_LIMITED;


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
	/*setup the direction for REAR_RIGHT_MOTOR pins through the GPIO driver.*/
	GPIO_setupPinDirection(DC_MOTOR_PORT, REAR_RIGHT_MOTOR_PIN1, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT, REAR_RIGHT_MOTOR_PIN2, PIN_OUTPUT);
	/*setup the direction for REAR_LEFT_MOTOR pins through the GPIO driver.*/
	GPIO_setupPinDirection(DC_MOTOR_PORT, REAR_LEFT_MOTOR_PIN1, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT, REAR_LEFT_MOTOR_PIN2, PIN_OUTPUT);
	/*setup the direction for FRONT_RIGHT_MOTOR pins through the GPIO driver.*/
	GPIO_setupPinDirection(DC_MOTOR_PORT, FRONT_RIGHT_MOTOR_PIN1, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT, FRONT_RIGHT_MOTOR_PIN2, PIN_OUTPUT);
	/*setup the direction for FRONT_LEFT_MOTOR pins through the GPIO driver.*/
	GPIO_setupPinDirection(DC_MOTOR_PORT, FRONT_LEFT_MOTOR_PIN1, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT, FRONT_LEFT_MOTOR_PIN2, PIN_OUTPUT);

	/*Stop at the DC-Motor at the beginning through the GPIO driver.*/
	set_car_direction(BRAKE);
}
void set_motor_direction(Motor_ID motor, Wheel_directions direction) {
		switch (motor) {
	case REAR_RIGHT_MOTOR:
		switch (direction) {
		case CLOCKWISE:
			DC_MOTOR_PORT |= (1 << REAR_RIGHT_MOTOR_PIN1);
			DC_MOTOR_PORT &= ~(1 << REAR_RIGHT_MOTOR_PIN2);
			break;
		case ANTI_CLOCKWISE:
			DC_MOTOR_PORT &= ~(1 << REAR_RIGHT_MOTOR_PIN1);
			DC_MOTOR_PORT |= (1 << REAR_RIGHT_MOTOR_PIN2);
			break;
		default:
			DC_MOTOR_PORT &= ~(1 << REAR_RIGHT_MOTOR_PIN1);
			DC_MOTOR_PORT &= ~(1 << REAR_RIGHT_MOTOR_PIN2);
			break;
		}
		break;

	case REAR_LEFT_MOTOR:
		switch (direction) {
		case CLOCKWISE:
			DC_MOTOR_PORT |= (1 << REAR_LEFT_MOTOR_PIN1);
			DC_MOTOR_PORT &= ~(1 << REAR_LEFT_MOTOR_PIN2);
			break;
		case ANTI_CLOCKWISE:
			DC_MOTOR_PORT &= ~(1 << REAR_LEFT_MOTOR_PIN1);
			DC_MOTOR_PORT |= (1 << REAR_LEFT_MOTOR_PIN2);
			break;
		default:
			DC_MOTOR_PORT &= ~(1 << REAR_LEFT_MOTOR_PIN1);
			DC_MOTOR_PORT &= ~(1 << REAR_LEFT_MOTOR_PIN2);
			break;
		}
		break;

	case FRONT_RIGHT_MOTOR:
		switch (direction) {
		case CLOCKWISE:
			DC_MOTOR_PORT |= (1 << FRONT_RIGHT_MOTOR_PIN1);
			DC_MOTOR_PORT &= ~(1 << FRONT_RIGHT_MOTOR_PIN2);
			break;
		case ANTI_CLOCKWISE:
			DC_MOTOR_PORT &= ~(1 << FRONT_RIGHT_MOTOR_PIN1);
			DC_MOTOR_PORT |= (1 << FRONT_RIGHT_MOTOR_PIN2);
			break;
		default:
			DC_MOTOR_PORT &= ~(1 << FRONT_RIGHT_MOTOR_PIN1);
			DC_MOTOR_PORT &= ~(1 << FRONT_RIGHT_MOTOR_PIN2);
			break;
		}
		break;

	case FRONT_LEFT_MOTOR:
		switch (direction) {
		case CLOCKWISE:
			DC_MOTOR_PORT |= (1 << FRONT_LEFT_MOTOR_PIN1);
			DC_MOTOR_PORT &= ~(1 << FRONT_LEFT_MOTOR_PIN2);
			break;
		case ANTI_CLOCKWISE:
			DC_MOTOR_PORT &= ~(1 << FRONT_LEFT_MOTOR_PIN1);
			DC_MOTOR_PORT |= (1 << FRONT_LEFT_MOTOR_PIN2);
			break;
		default:
			DC_MOTOR_PORT &= ~(1 << FRONT_LEFT_MOTOR_PIN1);
			DC_MOTOR_PORT &= ~(1 << FRONT_LEFT_MOTOR_PIN2);
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
	case FORWARD: {
		set_motor_direction(REAR_RIGHT_MOTOR, CLOCKWISE);
		set_motor_direction(REAR_LEFT_MOTOR, CLOCKWISE);
		set_motor_direction(FRONT_RIGHT_MOTOR, CLOCKWISE);
		set_motor_direction(FRONT_LEFT_MOTOR, CLOCKWISE);
		break;
	}

	case BACKWARD: {
		set_motor_direction(REAR_RIGHT_MOTOR, ANTI_CLOCKWISE);
		set_motor_direction(REAR_LEFT_MOTOR, ANTI_CLOCKWISE);
		set_motor_direction(FRONT_RIGHT_MOTOR, ANTI_CLOCKWISE);
		set_motor_direction(FRONT_LEFT_MOTOR, ANTI_CLOCKWISE);
		break;
	}
	case RIGHT: {
		set_motor_direction(REAR_RIGHT_MOTOR, CLOCKWISE);
		set_motor_direction(REAR_LEFT_MOTOR, CLOCKWISE);
		set_motor_direction(FRONT_LEFT_MOTOR, CLOCKWISE);
		set_motor_direction(FRONT_RIGHT_MOTOR, STOP);
		break;
	}
	case LEFT: {
		set_motor_direction(REAR_RIGHT_MOTOR, CLOCKWISE);
		set_motor_direction(REAR_LEFT_MOTOR, CLOCKWISE);
		set_motor_direction(FRONT_LEFT_MOTOR, STOP);
		set_motor_direction(FRONT_RIGHT_MOTOR, CLOCKWISE);
		break;
	}
	case LEFT_BACK: {
		set_motor_direction(REAR_RIGHT_MOTOR, ANTI_CLOCKWISE);
		set_motor_direction(REAR_LEFT_MOTOR, ANTI_CLOCKWISE);
		set_motor_direction(FRONT_LEFT_MOTOR, STOP);
		set_motor_direction(FRONT_RIGHT_MOTOR, ANTI_CLOCKWISE);
		
		break;
	}
	case RIGHT_BACK: {
			set_motor_direction(REAR_RIGHT_MOTOR, ANTI_CLOCKWISE);
			set_motor_direction(REAR_LEFT_MOTOR, ANTI_CLOCKWISE);
			set_motor_direction(FRONT_RIGHT_MOTOR, STOP);
			set_motor_direction(FRONT_LEFT_MOTOR, ANTI_CLOCKWISE);
			break;
		}
	case BRAKE: {
		set_motor_direction(REAR_RIGHT_MOTOR, STOP);
		set_motor_direction(REAR_LEFT_MOTOR, STOP);
		set_motor_direction(FRONT_RIGHT_MOTOR, STOP);
		set_motor_direction(FRONT_LEFT_MOTOR, STOP);
		break;
	}
	}
}

carState move_car(void) {
	carState state;
	uint8 car_info = HC05_receiveByte();
	switch (car_info)
	{
	case 'S':
	case 'D':
		set_car_direction(BRAKE);
		state.gearState = BRAKE;
		break;

	case 'F':
		set_car_direction(FORWARD);
		state.gearState = FORWARD;
		break;

	case 'B':
		set_car_direction(BACKWARD);
		state.gearState = BACKWARD;
		break;

	case 'H':
		set_car_direction(LEFT_BACK);
		state.gearState = LEFT_BACK;
		break;

	case 'J':
		set_car_direction(RIGHT_BACK);
		state.gearState = RIGHT_BACK;
		break;

	case 'L':
	case 'G':
		set_car_direction(LEFT);
		state.gearState = LEFT;
		break;

	case 'R':
	case 'I':
		set_car_direction(RIGHT);
		state.gearState = RIGHT;
		break;

	case '0':
		PWM_Timer0_Init(SPEED_0);
		state.carSpeed = SPEED_0;
		break;

	case '1':
		PWM_Timer0_Init(SPEED_10);
		state.carSpeed = SPEED_10;
		break;
	case '2':
		PWM_Timer0_Init(SPEED_20);
		state.carSpeed = SPEED_20;
		break;

	case '3':
		PWM_Timer0_Init(SPEED_30);
		state.carSpeed = SPEED_30;
		break;

	case '4':
		PWM_Timer0_Init(SPEED_40);
		state.carSpeed = SPEED_40;
		break;

	case '5':
		PWM_Timer0_Init(SPEED_50);
		state.carSpeed = SPEED_50;
		break;

	case '6':
		if(u8_speedIsLimited == SPEED_IS_LIMITED)
		{
			PWM_Timer0_Init(SPEED_SAFE_LIMIT);
			state.carSpeed = SPEED_SAFE_LIMIT;
		}
		else
		{
			PWM_Timer0_Init(SPEED_60);
			state.carSpeed = SPEED_60;
		}
		break;

	case '7':
		if(u8_speedIsLimited == SPEED_IS_LIMITED)
		{
			PWM_Timer0_Init(SPEED_SAFE_LIMIT);
			state.carSpeed = SPEED_SAFE_LIMIT;
		}
		else
		{
			PWM_Timer0_Init(SPEED_70);
			state.carSpeed = SPEED_70;
		}
		break;

	case '8':
		if(u8_speedIsLimited == SPEED_IS_LIMITED)
		{
			PWM_Timer0_Init(SPEED_SAFE_LIMIT);
			state.carSpeed = SPEED_SAFE_LIMIT;
		}
		else
		{
			PWM_Timer0_Init(SPEED_80);
			state.carSpeed = SPEED_80;
		}
		break;

	case '9':
		if(u8_speedIsLimited == SPEED_IS_LIMITED)
		{
			PWM_Timer0_Init(SPEED_SAFE_LIMIT);
			state.carSpeed = SPEED_SAFE_LIMIT;
		}
		else
		{
			PWM_Timer0_Init(SPEED_90);
			state.carSpeed = SPEED_90;
		}
		break;

	case 'q':
		if(u8_speedIsLimited == SPEED_IS_LIMITED)
		{
			PWM_Timer0_Init(SPEED_SAFE_LIMIT);
			state.carSpeed = SPEED_SAFE_LIMIT;
		}
		else
		{
			PWM_Timer0_Init(SPEED_100);
			state.carSpeed = SPEED_100;
		}
		break;

	}
	return state;
}


void set_Car_State(carState state)
{
	set_car_direction(state.gearState);
	PWM_Timer0_Init(state.carSpeed);
}
