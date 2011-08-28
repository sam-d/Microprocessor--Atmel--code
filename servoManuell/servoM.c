#include <avr/interrupt.h>    // Defines pins, ports, etc to make programs easier to read
#define F_CPU 100000UL        // Sets up the default speed for delay. 1MHz
#include <util/delay.h>

#define SERVO_MIN 250
#define SERVO_MAX 1250
#define SERVO_MIDDLE 750

#define MASK_SWITCH1 1 //bit 0
#define MASK_SWITCH2 8 //bit 3

/* ATtiny2313 internal system clock is 8 MHz with CKDIV8 Fuse programmed
 * meaning a system clock of 1MHz
 * we will thus use a prescale of 1 and ICR1 = 10000*/
void init_pwm(void){
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

    init_pwm(); //set up PWM on PB3/OCR1A
    PORTB &= ~_BV(PB3); //set pin 3  low
    OCR1A = SERVO_MIDDLE; //set servo to middle position

    //Set up signaling LED on port B0
    DDRB |= _BV(PB0); //Port PB0 is output (LED)
    PORTB &= ~_BV(PB0); //set pin B0 to low
    
    //Set up inputs on ports D0 and D3
    DDRD &= ~_BV(PD0); //Port PD0 as intput (Switch1)
    DDRD &= ~_BV(PD3); //Port PD3 as input (switch2)
    PORTD |= _BV(PD0); // internal pull-up resistor
    PORTD |= _BV(PD3); //on the input ports 

    unsigned char input ; //input goes here

    while(1){
        
        //PORTB &= ~_BV(PB0); //LED out

        input = PIND; //read input

        if((input & MASK_SWITCH1) == MASK_SWITCH1){
            PORTB |= _BV(PB0); //light LED
            if(OCR1A != SERVO_MIN){
                 OCR1A--;
                _delay_ms(10);
            }
        }
        if((input & MASK_SWITCH2) == MASK_SWITCH2){
            PORTB |= _BV(PB0); //light LED
            if(OCR1A != SERVO_MAX){
                OCR1A++; 
                _delay_ms(10);
            }     
        }


    }

    return 0;
}
