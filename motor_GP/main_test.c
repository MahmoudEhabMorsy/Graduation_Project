#include "motor_rc.h"
#include "hc05.h"




int main(void) {
	delay(1);
	HC05_init(SLAVE);
	_delay_ms(300);

	DC_Motor_Init();
	PWM_Timer0_Init(speed_50);
	while (1) {
		move_car();
	}

}
