#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>


const uint8_t MASK_D2 = (1 << PD2);
const uint8_t DEBOUNCE_DELAY = 10;  
const uint8_t AMBER_DELAY = 5;
const uint8_t INIT_B0 = (1 << PB0);
const uint8_t INIT_B1 = (1 << PB1);


void delay(float duration)
{   
    uint32_t usConversion = duration*1000000; 
    uint8_t delayLength = 50;
    uint32_t nIteration = usConversion/delayLength;
    for(uint32_t i = 0; i < nIteration; i++)
    {
        _delay_us(delayLength);
    }    

}

void PWM(uint16_t frequency, float percentage)
{
    uint32_t nSeconds = 2; 
    float periode = 1.0/frequency;
    float a = percentage*periode;
    float timeOff = periode - a;
    uint16_t nIteration = nSeconds/periode;
    
    for(uint16_t counter = 0; counter < nIteration; counter++)
    {
        PORTB |= INIT_B0; // turnOnWheel
        delay(a);
        PORTB &= ~(INIT_B0); //turnOffWheel
        delay(timeOff);
    }        
}

void ControlMotor()
{

    PWM(60,0);
    PWM(60, 0.25); // pourcentage = dutycycle
    PWM(60, 0.50);
    PWM(60, 0.75);
    PWM(60, 1);

    PWM(400,0);
    PWM(400, 0.25);
    PWM(400, 0.50);
    PWM(400, 0.75);
    PWM(400, 1);
}


int main()    
{    
    DDRB |= INIT_B0 | INIT_B1;   
        
    ControlMotor();             
}