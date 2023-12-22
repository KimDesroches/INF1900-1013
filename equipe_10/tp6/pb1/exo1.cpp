/*
Auteurs : Ghadi Falouh et ALi Yacoubi
Date : 17 octobre 2023
But: Quand le bouton est enfoncé, un compteur qui incrémente 10 fois par seconde est activé. 
Quand le bouton est relâché ou lorsque le compteur atteint 120, la lumière clignote vert 
pendant 1/2 seconde. Ensuite, la carte mère ne fait rien. Puis, deux secondes plus tard, 
la lumière rouge s'allume. Elle devra clignoter (compteur / 2) fois au rythme de 2 fois 
par seconde. Ensuite, la lumière tourne au vert pendant une seconde. Finalement, elle 
s'éteint et le robot revient à son état original. Cela peut être representé avec une
machine de Moore selon la table d'états suivante: 

+--------------+----------------+-----------------+--------------+------------+
| currentState | isTimerExpired | isButtonPressed |  nextState   |   output   |
+--------------+----------------+-----------------+--------------+------------+
| INITIAL      | X              | 0               | INITIAL      | OFF        |
| INITIAL      | X              | 1               | COUNT        | OFF        |
| COUNT        | X              | 0               | COUNTER_DONE | OFF        |
| COUNT        | 0              | 1               | COUNT        | OFF        |
| COUNT        | 1              | X               | COUNTER_DONE | OFF        |
| COUNTER_DONE | X              | X               | WAITING      | BlinkGreen |
| WAITING      | X              | X               | RESULT       | OFF        |
| RESULT       | X              | X               | FINAL        | BlinkRed   |
| FINAL        | X              | X               | INITIAL      | GREEN      |
+--------------+----------------+-----------------+--------------+------------+

Dans ce programme, on a initialisé les broches B0 et B1 comme étants outputs et la
     broche D2 comme etant input. 
If faut brancher B0 avec la broche - de la DEL libre et B1 avec sa broche +. De plus,
    le breadboard avec le boutton poussoir est branché avec le VCC et GND des broches A,
    il est aussi branché avec la broche D2 pour la gestion des interuptions.    

*/

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
const uint8_t LED_GREEN = (1 << PB0);
const uint8_t LED_RED = (1 << PB1);
const uint8_t SET_LED_OFF = (LED_GREEN | LED_RED);
const uint8_t MASK_D2 = (1 << PD2);
const uint8_t DEBOUNCE_DELAY = 30;
const uint8_t COUNTER_INCREMENT = 10;
const uint8_t DELAY_BLINK = 50;
const uint16_t DURATION = 500;
const uint8_t DELAY_BLINK_RED = 250;
const uint16_t PRESCALER = 1024; 
const uint16_t DELAY_OFF = 2000;
const uint16_t TIMER_DURATION = 1;
const uint8_t MAX_COUNTER = 120;
const uint16_t DELAY_GREEN = 1000;
volatile uint8_t counter = 0; 
volatile bool isTimerExpired = true;
volatile bool isButtonPressed = false;
enum class State{INITIAL, COUNT, COUNTER_DONE, WAITING, RESULT, FINAL};
State currentState = State:: INITIAL;
enum class Color{RED, GREEN, OFF};


ISR ( TIMER1_COMPA_vect )
{   
    counter += COUNTER_INCREMENT;   
    isTimerExpired = true;        

}

ISR ( INT0_vect) 
{    
    _delay_ms (DEBOUNCE_DELAY);
    if(isButtonPressed == true)
    {        
        isButtonPressed = false;
    }        
    else if(isButtonPressed == false)
    {
        isButtonPressed = true;
    }             
    EIFR |= (1 << INTF0) ;
}

void update()
{
    switch(currentState)
    {
        case State::INITIAL:
            if(isButtonPressed)
            {
                currentState = State::COUNT;   
            }            
            break;            
        case State:: COUNT:
            if(counter >= MAX_COUNTER || !isButtonPressed) 
            {
                currentState = State::COUNTER_DONE;
            }            
            break;
        case State::COUNTER_DONE:
            currentState = State::WAITING;
            break;
        case State::WAITING:
            currentState = State::RESULT;
            break;
        case State::RESULT:
            currentState = State::FINAL;
            break;
        case State::FINAL:
            currentState = State::INITIAL;
    }
}

void setColor(Color color)
{    
    uint8_t ledOn = 0;
    uint8_t ledOff = 0;
    switch(color)
    {
        case Color::GREEN:            
            ledOff = LED_RED;
            ledOn = LED_GREEN;            
        break;
        case Color::RED:      
            ledOff = LED_GREEN;
            ledOn = LED_RED;      
        break;
        case Color::OFF:
            ledOff = SET_LED_OFF;
        break;        
    }

    PORTB &= ~(ledOff);
    PORTB |= ledOn;
}

void initialize ( void ) 
{
    cli ();
    DDRB |= LED_GREEN | LED_RED;        
    DDRD &= ~MASK_D2;
    EIMSK |= (1 << INT0) ;    
    EICRA |= (0 << ISC01) | (1 << ISC00) ;    
    sei ();
}

void startTimer (uint16_t duree) 
{    
    isTimerExpired =false;    

    TCNT1 = 0 ;
    OCR1A = duree;
    TCCR1A = 0 ;
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10) ;
    TCCR1C = 0;
    TIMSK1 |= (1 << OCIE1A) ;
}

void blinkGreen()
{
    uint8_t counterBlink = 0;
    while(counterBlink <= DURATION/DELAY_BLINK)
    {        
        setColor(Color::GREEN);
        _delay_ms(DELAY_BLINK);        
        setColor(Color::OFF);
        _delay_ms(DELAY_BLINK);        
        counterBlink++;
    }
}

void blinkRed()
{        
    uint8_t nBlinks = counter / 2;        
    for(int i = 0; i < nBlinks; i++)
    {        
        setColor(Color::RED);
        _delay_ms(DELAY_BLINK_RED);        
        setColor(Color::OFF);
        _delay_ms(DELAY_BLINK_RED);
    }    
}

uint16_t convertSecondes(uint8_t nSecondes)
{   
    uint16_t nCycles = (nSecondes*F_CPU)/PRESCALER;
    return nCycles;
}

void excute()
{           
    switch(currentState)
    {                     
        case State::INITIAL:  
             sei();
             counter = 0;                    
             break;       
        case State:: COUNT:                       
            if(isTimerExpired && isButtonPressed)
            {                
                startTimer(convertSecondes(TIMER_DURATION)); 
            }            
            break;            
        case State::COUNTER_DONE:            
            blinkGreen();                                               
            break;
        case State::WAITING:     
            cli();       
            _delay_ms(DELAY_OFF);                              
            break;
        case State::RESULT:                                                     
            if(counter > MAX_COUNTER)
            {
               counter = MAX_COUNTER;
            }
            blinkRed();                 
            isTimerExpired = true;        
            isButtonPressed = false;                                                      
            break;    
        case State::FINAL:            
            setColor(Color::GREEN);
            _delay_ms(DELAY_GREEN);            
            setColor(Color::OFF);
    }    
}

int main()
{        
    initialize();
    while(true)
    {            
        excute();
        update();                  
    }    
}  