#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>


const uint8_t MASK_D2 = (1 << PD2);
const uint8_t DEBOUNCE_DELAY = 10;  
const uint8_t AMBER_DELAY = 5;
const uint8_t LED_GREEN = (1 << PA0);
const uint8_t LED_RED = (1 << PA1);


void delay(uint16_t duration)
{    
    int nloop = duration/50;

    for( int i =0; i < nloop; i++)
    {
        _delay_us(50);
    }    

}



int main()    
{    
    DDRA |= LED_GREEN | LED_RED;    
    //DDRD &= ~MASK_D2;    
    double a;
    double b;
    

    //double frequency = 1/double(b);
    //PORTA |= LED_GREEN;    
    while(true)
    {                  
        a = 3000;
        b = 3000;
        
        for(int i = 0; i<1000; i++)
        {                                
            PORTA |= LED_GREEN;
            delay(a);
            PORTA &= ~(LED_GREEN);
            delay(b-a);            
            a = a-3;
        }

    }
}