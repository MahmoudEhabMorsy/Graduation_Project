#include"dio_writePort_test.h"

void DIO_writePort_test(void) {
	DIO_setupPortDirection(PORTA_ID, PORT_OUTPUT);
	DIO_setupPortDirection(PORTB_ID, PORT_OUTPUT);
	DIO_setupPortDirection(PORTC_ID, PORT_OUTPUT);
	DIO_setupPortDirection(PORTD_ID, PORT_OUTPUT);
	while (1) {
		DIO_writePort(PORTA_ID, LOGIC_HIGH);
		DIO_writePort(PORTA_ID, LOGIC_HIGH);
		DIO_writePort(PORTA_ID, LOGIC_HIGH);
		DIO_writePort(PORTA_ID, LOGIC_HIGH);
		_ms_delay(1000);
		DIO_writePort(PORTA_ID, LOGIC_LOW);
		DIO_writePort(PORTA_ID, LOGIC_LOW);
		DIO_writePort(PORTA_ID, LOGIC_LOW);
		DIO_writePort(PORTA_ID, LOGIC_LOW);
		_ms_delay(1000);

	}
}