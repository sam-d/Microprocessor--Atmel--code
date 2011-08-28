/* Include useful pre-defined functions */
#include <avr/interrupt.h>    // Defines pins, ports, etc to make programs easier to read
#define F_CPU 100000UL        // Sets up the default speed for delay.h
#include <util/delay.h>

#define MASK 1 //bit coded by input pin

int main(void){

    unsigned char i;
    unsigned char schalter = 0;

    DDRB |= _BV(PB0); //Port PB0 is output (LED)

    DDRD &= ~_BV(PD0); //Port PD0 is intput (Switch)

    PORTB &= ~_BV(PB0); //set pin B0 to low

    while(1){

        i = PIND;

         //synchronize

        if( (i & MASK) == MASK){
            PORTB |= _BV(PB0); //set high (LED on)
        }else{
            PORTB &= ~_BV(PB0); //set low (LED off)
        }
        
    }

    return 0;

}
