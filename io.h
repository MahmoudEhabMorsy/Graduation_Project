#ifndef IO_H_
#define IO_H_

 /*-----------------------------------------------------------------------*
 |                                  DIO                                   |
 *-----------------------------------------------------------------------*/
#define PORTA _SFR_IO8(0x1B)
#define DDRA _SFR_IO8(0x1A)
#define PINA _SFR_IO8(0x19)

#define PORTB _SFR_IO8(0x18)
#define DDRB _SFR_IO8(0x17)
#define PINB _SFR_IO8(0x16)

#define PORTC _SFR_IO8(0x15)
#define DDRC _SFR_IO8(0x14)
#define PINC _SFR_IO8(0x13)

#define PORTD _SFR_IO8(0x12)
#define DDRD _SFR_IO8(0x11)
#define PIND _SFR_IO8(0x10)

 /*-----------------------------------------------------------------------*
 |                                   ADC                                  |
 *-----------------------------------------------------------------------*/
#define ADMUX   _SFR_IO8(0x07)

#define MUX0      0
#define MUX1      1
#define MUX2      2
#define MUX3      3
#define MUX4      4
#define ADLAR     5
#define REFS0     6
#define REFS1     7


#define ADCSRA  _SFR_IO8(0x06)

#define ADPS0     0
#define ADPS1     1
#define ADPS2     2
#define ADIE      3
#define ADIF      4
#define ADATE     5
#define ADSC      6
#define ADEN      7


#define ADCH    _SFR_IO8(0x05)

#define ADCL    _SFR_IO8(0x04)

 /*-----------------------------------------------------------------------*
 |                           Interrupt vectors                            |
 *-----------------------------------------------------------------------*/

/* ADC Conversion Complete */
#define ADC_vect_num			16
#define ADC_vect				_VECTOR(16)
#define SIG_ADC					_VECTOR(16)

#endif
