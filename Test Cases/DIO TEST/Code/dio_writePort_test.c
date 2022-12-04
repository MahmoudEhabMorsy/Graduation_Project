#include"dio_writePort_test.h"

void DIO_writePort_test(void) {
	DIO_setupPortDirection(PORTA_ID, PORT_OUTPUT);
	DIO_setupPortDirection(PORTB_ID, PORT_OUTPUT);
	DIO_setupPortDirection(PORTC_ID, PORT_OUTPUT);
	DIO_setupPortDirection(PORTD_ID, PORT_OUTPUT);
	while (1) {
		DIO_writePort(PORTA_ID, 0xff);
		DIO_writePort(PORTB_ID, 0xff);
		DIO_writePort(PORTC_ID, 0xff);
		DIO_writePort(PORTD_ID, 0xff);
		_delay_ms(1000);
		DIO_writePort(PORTA_ID, 0);
		DIO_writePort(PORTB_ID, 0);
		DIO_writePort(PORTC_ID, 0);
		DIO_writePort(PORTD_ID, 0);
		_delay_ms(1000);

	}
}