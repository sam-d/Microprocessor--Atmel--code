/* First try at using a seven digit display 
 * Display is a Vishay TDS0 5150 Orange Red, with 
 * common anode (pin 3 and 8), so to turn a segment
 * on, we pull the pin to ground (0)
 * Pinout:  1 e PB6
 *          2 d PB7
 *          3 anode   
 *          4 c PB5  
 *          5 decimal point PB4
 *          6 b PB2
 *          7 a PB1
 *          8 anode 
 *          9 f PB0
 *         10 g PB3
 * I've connected them all to PORTB in random order
 * */

/* Include useful pre-defined functions */
#include <avr/interrupt.h>    // Defines pins, ports, etc to make programs easier to read
#define F_CPU 100000UL        // Sets up the default speed for delay.h
#include <util/delay.h>


int main(void){

    unsigned int i = 0; //counter var for for loop
    unsigned char input;

    DDRB = 255; //enable all pins on port B as output
    
    DDRD &= ~_BV(PD4); //port PD4 is input (switch)

    const static int digit[] = {
       // Bit value for PortB: dec1gbaf
        8, //0
        95, //1
        49, //2
        113, //3
        82, //4
        84, //5
        4, //6
        217, //7
        16, //8
        81, //9
    };

    while(1){
        
        //cycle through all numbers
        //_delay_ms(1000);

        //for(i=0; i<10; i++){
        //    PORTB = digit[i];
        //    _delay_ms(1000);
        //}
        
        //use switch as input to cycle through number
        //on command
        input = PIND; //read value of PORTD
        if((input & _BV(PD4)) == _BV(PD4)){ //switch pressed
            if(i < 10){
                PORTB = digit[i];
            }else{
                i = 0;
                PORTB = digit[i];
            }
        }
    }

return 0;
}

