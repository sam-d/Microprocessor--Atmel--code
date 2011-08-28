/* program to control a servo motor, second try */

/* Include useful pre-defined functions */
//#include <stdint.h>
#include <avr/interrupt.h>    // Defines pins, ports, etc to make programs easier to read
#define F_CPU 100000UL        // Sets up the default speed for delay. 1MHz
#include <util/delay.h>

/* ATtiny2313 internal system clock is 8 MHz with CKDIV8 Fuse programmed
 * meaning a system clock of 1MHz
 * we will thus use a prescale of 1 and ICR1 = 10000*/

void init(void){
/* set up counter 1 (16 bit) to act as a dual channel PWM generator
 * in phase and frequency correct mode (mode 8)
 *we want OC1A and B to be set on reaching BOTTOM, clear on reaching
 *compare match, use ICR1 as TOP and have a prescale of 1.*/

 /*note: since timer1 hast 16bit, both TCCR1A and B (each 8 bits need to
  * be addressed */
TCCR1A = _BV(COM1A1); // (Clear OC1A/B on compare match, set OC1A/B at TOP)

TCCR1B = _BV(WGM13)     // see page 110, when WGM11 13 set then mode 8
        | _BV(CS10); // timer uses main system clock with prescale 1

ICR1 = 10000; //used for TOP, makes for 50Hz PWM since ATtiny 2313 is 1MHz

DDRB |= _BV(PB3); // have to set up Port B pin 3(OC1A) as output

}

int main(void){
    
    init(); //set up timer1
    
    PORTB &= ~_BV(PB3); //set pin 3  low
   /* Conrad TopLine servo ES-030 ~180 +-2 degrees
    * Torque: ?
    * Stellmoment 0,19ms for 1 degree
    *
    * (with 5-10% duty cycle) allowed values for OCR1A are 250-1250 
    * */

    OCR1A = 250;//left position
    
    _delay_ms(100);

    //oscillation from one end to the other
    while(1){
        for(OCR1A=250;OCR1A<=1250;OCR1A+=1){
            _delay_ms(20); //cf Stellmoment
        }

           _delay_ms(1000); 
           _delay_ms(1000); 

        for(OCR1A=1250;OCR1A>=250;OCR1A -= 1){
            _delay_ms(20); //cf. Stellmoment
        }

           _delay_ms(1000); 
           _delay_ms(1000); 
    }

    return 0;

}
