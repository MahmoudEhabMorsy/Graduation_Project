#include"dio_readPort_test.h"

void DIO_readPort_test(void) {
	DIO_setupPortDirection(PORTA_ID, PORT_INPUT);
	DIO_setupPortDirection(PORTB_ID, PORT_INPUT);
	DIO_setupPortDirection(PORTC_ID, PORT_INPUT);
	DIO_setupPortDirection(PORTD_ID, PORT_INPUT);
	/*activating internal pull up circuit*/
	DIO_writePort(PORTA_ID, 0xff);
	DIO_writePort(PORTA_ID, 0xff);
	DIO_writePort(PORTA_ID, 0xff);
	DIO_writePort(PORTA_ID, 0xff);
	while (1) {
		/*needs LCD to display outputs(inputs to CPU)*/
	}
}