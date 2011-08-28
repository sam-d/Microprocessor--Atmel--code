/* Blinker Demo */

/* Include useful pre-defined functions */
#include <avr/interrupt.h>    // Defines pins, ports, etc to make programs easier to read
#define F_CPU 100000UL        // Sets up the default speed for delay.h
#include <util/delay.h>

int main(void){

        DDRD |= _BV(PD4);              /* enable output on port D, pin 4 */
            
        while(1){

                PORTD |= _BV(PD4); 
                _delay_ms(1000);
                PORTD &= ~_BV(PD4); 
                _delay_ms(1000);
        }

}
