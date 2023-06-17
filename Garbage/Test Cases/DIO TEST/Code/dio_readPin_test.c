#include"dio_readPin_test.h"

void DIO_readPin_test(void) {
	DIO_setupPinDirection(PORTA_ID, PIN0_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTA_ID, PIN1_ID, PIN_OUTPUT);

	DIO_setupPinDirection(PORTB_ID, PIN0_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTB_ID, PIN1_ID, PIN_OUTPUT);

	DIO_setupPinDirection(PORTC_ID, PIN0_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTC_ID, PIN1_ID, PIN_OUTPUT);

	DIO_setupPinDirection(PORTD_ID, PIN0_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTD_ID, PIN1_ID, PIN_OUTPUT);

	/*activating internal pull up circuit*/

	DIO_writePin(PORTA_ID, PIN0_ID, LOGIC_HIGH);

	DIO_writePin(PORTB_ID, PIN0_ID, LOGIC_HIGH);

	DIO_writePin(PORTC_ID, PIN0_ID, LOGIC_HIGH);

	DIO_writePin(PORTD_ID, PIN0_ID, LOGIC_HIGH);

	while (1) {
		if(!DIO_readPin(PORTA_ID,PIN0_ID)){
			DIO_writePin(PORTA_ID,PIN1_ID,LOGIC_HIGH);

		}
		if(!DIO_readPin(PORTB_ID,PIN0_ID)){
			DIO_writePin(PORTB_ID,PIN1_ID,LOGIC_HIGH);

		}
		if(!DIO_readPin(PORTC_ID,PIN0_ID)){
			DIO_writePin(PORTC_ID,PIN1_ID,LOGIC_HIGH);

		}
		if(!DIO_readPin(PORTD_ID,PIN0_ID)){
			DIO_writePin(PORTD_ID,PIN1_ID,LOGIC_HIGH);

		}
	}

}
