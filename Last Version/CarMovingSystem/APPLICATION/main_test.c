#include "../ECUAL/MOTOR/motor_rc.h"
#include "../ECUAL/HC05/hc05.h"
#include <avr/interrupt.h>

void keep_Car_Safe(void);

volatile uint8 u8_severeTiresStateFlag = 0;
carState t_carState = {BRAKE,SPEED_0};

ISR(INT1_vect)
{
	u8_severeTiresStateFlag = 1;
}



int main(void) {
	delay(1);
	HC05_init(SLAVE);
	_delay_ms(300);

	/*INT1 init Function*/
	DDRD  &= (~(1<<PD3));  // Configure INT1/PD3 as input pin
	PORTD &=~(1<<PD3); //Initially LOW
	/*Trigger INT1 with the rising edge*/
	MCUCR |= (1<<ISC11) | (1 << ISC10);
	GICR  |= (1<<INT1);    // Enable external interrupt pin INT1
	/* End of INT1 init Function*/

	DC_Motor_Init();
	PWM_Timer0_Init(SPEED_50);

	SREG |= (1 << 7);
	while (1)
	{
		if(u8_severeTiresStateFlag)
		{
			keep_Car_Safe();
		}
		else
		{
			t_carState = move_car();
		}
	}

}

void keep_Car_Safe(void)
{
	switch(t_carState.gearState)
	{
	case FORWARD:
	case LEFT:
	case RIGHT:
		// Set Gear: FORWARD
		t_carState.gearState = FORWARD;
		set_Car_State(t_carState);
		// Limit the speed to 50%.
		break;
	case BACKWARD:
	case LEFT_BACK:
	case RIGHT_BACK:
		t_carState.gearState = BACKWARD;
		set_Car_State(t_carState);
		// Limit the speed to 50%.
		break;
	case BRAKE:
	default:
		// Only Limit The Car Speed Until return to Safe or Moderate State.
		break;
	}

	switch(t_carState.carSpeed)
	{
	case SPEED_100:
		t_carState.carSpeed = SPEED_90;
		set_Car_State(t_carState);
		_delay_ms(250);
		_delay_ms(250);
	case SPEED_90:
		t_carState.carSpeed = SPEED_80;
		set_Car_State(t_carState);
		_delay_ms(250);
		_delay_ms(250);
	case SPEED_80:
		t_carState.carSpeed = SPEED_70;
		set_Car_State(t_carState);
		_delay_ms(250);
		_delay_ms(250);
	case SPEED_70:
		t_carState.carSpeed = SPEED_60;
		set_Car_State(t_carState);
		_delay_ms(250);
		_delay_ms(250);
	case SPEED_60:
		t_carState.carSpeed = SPEED_50;
		set_Car_State(t_carState);
		_delay_ms(250);
		_delay_ms(250);
	case SPEED_50:
		t_carState.carSpeed = SPEED_40;
		set_Car_State(t_carState);
		_delay_ms(250);
		_delay_ms(250);
	case SPEED_40:
		t_carState.carSpeed = SPEED_30;
		set_Car_State(t_carState);
		_delay_ms(250);
		_delay_ms(250);
	case SPEED_30:
		t_carState.carSpeed = SPEED_20;
		set_Car_State(t_carState);
		_delay_ms(250);
		_delay_ms(250);
	case SPEED_20:
		t_carState.carSpeed = SPEED_10;
		set_Car_State(t_carState);
		_delay_ms(250);
		_delay_ms(250);
	case SPEED_10:
		t_carState.carSpeed = SPEED_0;
		set_Car_State(t_carState);
		_delay_ms(250);
		_delay_ms(250);
	case SPEED_0:
	default:
		// Do Nothing.
		break;
	}
	u8_speedIsLimited = SPEED_IS_LIMITED;
	u8_severeTiresStateFlag = 0;
}
