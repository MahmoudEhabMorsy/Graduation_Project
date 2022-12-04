#include"dio_readPin_test.h"

void DIO_readPin_test(void) {
	DIO_setupPinDirection(PORTA_ID, PIN0_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTA_ID, PIN1_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTA_ID, PIN2_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTA_ID, PIN3_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTA_ID, PIN4_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTA_ID, PIN5_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTA_ID, PIN6_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTA_ID, PIN7_ID, PIN_INPUT);

	DIO_setupPinDirection(PORTB_ID, PIN0_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTB_ID, PIN1_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTB_ID, PIN2_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTB_ID, PIN4_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTB_ID, PIN5_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTB_ID, PIN6_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTB_ID, PIN7_ID, PIN_INPUT);

	DIO_setupPinDirection(PORTC_ID, PIN0_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTC_ID, PIN1_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTC_ID, PIN2_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTC_ID, PIN3_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTC_ID, PIN4_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTC_ID, PIN5_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTC_ID, PIN6_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTC_ID, PIN7_ID, PIN_INPUT);

	DIO_setupPinDirection(PORTD_ID, PIN0_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTD_ID, PIN1_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTD_ID, PIN2_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTD_ID, PIN3_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTD_ID, PIN4_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTD_ID, PIN5_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTD_ID, PIN6_ID, PIN_INPUT);
	DIO_setupPinDirection(PORTD_ID, PIN7_ID, PIN_INPUT);

	/*activating internal pull up circuit*/
	DIO_writePin(PORTA_ID, PIN0_ID, LOGIC_HIGH);
	DIO_writePin(PORTA_ID, PIN1_ID, LOGIC_HIGH);
	DIO_writePin(PORTA_ID, PIN2_ID, LOGIC_HIGH);
	DIO_writePin(PORTA_ID, PIN3_ID, LOGIC_HIGH);
	DIO_writePin(PORTA_ID, PIN4_ID, LOGIC_HIGH);
	DIO_writePin(PORTA_ID, PIN5_ID, LOGIC_HIGH);
	DIO_writePin(PORTA_ID, PIN6_ID, LOGIC_HIGH);
	DIO_writePin(PORTA_ID, PIN7_ID, LOGIC_HIGH);

	DIO_writePin(PORTB_ID, PIN0_ID, LOGIC_HIGH);
	DIO_writePin(PORTB_ID, PIN1_ID, LOGIC_HIGH);
	DIO_writePin(PORTB_ID, PIN2_ID, LOGIC_HIGH);
	DIO_writePin(PORTB_ID, PIN3_ID, LOGIC_HIGH);
	DIO_writePin(PORTB_ID, PIN4_ID, LOGIC_HIGH);
	DIO_writePin(PORTB_ID, PIN5_ID, LOGIC_HIGH);
	DIO_writePin(PORTB_ID, PIN6_ID, LOGIC_HIGH);
	DIO_writePin(PORTB_ID, PIN7_ID, LOGIC_HIGH);

	DIO_writePin(PORTC_ID, PIN0_ID, LOGIC_HIGH);
	DIO_writePin(PORTC_ID, PIN1_ID, LOGIC_HIGH);
	DIO_writePin(PORTC_ID, PIN2_ID, LOGIC_HIGH);
	DIO_writePin(PORTC_ID, PIN3_ID, LOGIC_HIGH);
	DIO_writePin(PORTC_ID, PIN4_ID, LOGIC_HIGH);
	DIO_writePin(PORTC_ID, PIN5_ID, LOGIC_HIGH);
	DIO_writePin(PORTC_ID, PIN6_ID, LOGIC_HIGH);
	DIO_writePin(PORTC_ID, PIN7_ID, LOGIC_HIGH);

	DIO_writePin(PORTD_ID, PIN0_ID, LOGIC_HIGH);
	DIO_writePin(PORTD_ID, PIN1_ID, LOGIC_HIGH);
	DIO_writePin(PORTD_ID, PIN2_ID, LOGIC_HIGH);
	DIO_writePin(PORTD_ID, PIN3_ID, LOGIC_HIGH);
	DIO_writePin(PORTD_ID, PIN4_ID, LOGIC_HIGH);
	DIO_writePin(PORTD_ID, PIN5_ID, LOGIC_HIGH);
	DIO_writePin(PORTD_ID, PIN6_ID, LOGIC_HIGH);
	DIO_writePin(PORTD_ID, PIN7_ID, LOGIC_HIGH);

	while (1) {
		/*needs LCD to display outputs(inputs to CPU)*/
	}

}