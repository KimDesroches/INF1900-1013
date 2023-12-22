#define F_CPU 8000000

#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

const uint8_t MASK_D2 = (1 << PD2);
const uint8_t DEBOUNCE_DELAY = 10;  
const uint8_t AMBER_DELAY = 10;
const uint8_t LED_GREEN = (1 << PA0);
const uint8_t LED_RED = (1 << PA1);



volatile bool isButtonPressed = false;

volatile uint8_t gMinuterieExpiree;
volatile uint8_t gBoutonPoussoir;

void turnGreen()
{
    PORTA &= ~(LED_RED);
    PORTA |= LED_GREEN;
}   

void turnRed()
{
    PORTA &= ~(LED_GREEN);
    PORTA |= LED_RED;
}

void turnOff()
{
    PORTA &= ~(LED_GREEN);
    PORTA &= ~(LED_RED);
}


void delay10S()
{
    _delay_ms(10000);
}

void blink()
{    
    for(int i = 0; i < 10; i++)
    {
        turnRed();    
        _delay_ms(5);
        turnOff();
        _delay_ms(5);
    }        
}


ISR ( TIMER1_COMPA_vect )
 {
    gMinuterieExpiree = 1;
}

void partirMinuterie ( uint16_t duree ) 
{

    gMinuterieExpiree = 0;

    // mode CTC du timer 1 avec horloge divisée par 1024

    // interruption après la durée spécifiée

    TCNT1 = 0 ;

    OCR1A = duree;

    TCCR1A = 0 ;

    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10) ;

    TCCR1C = 0;

    TIMSK1 |= (1 << OCIE1A) ;

}

ISR ( INT0_vect ) 
{

    gBoutonPoussoir = 1;

    // anti-rebond
    _delay_ms ( 30 );
    //'modifier ici'     
    EIFR |= (1 << INTF0) ;

}



void initialisation ( void ) 
{
    // cli est une routine qui bloque toutes les interruptions.
    // Il serait bien mauvais d'être interrompu alors que
    // le microcontrôleur n'est pas prêt...
    cli ();
    // configurer et choisir les ports pour les entrées
    // et les sorties. DDRx... Initialisez bien vos variables

    DDRA |= LED_GREEN | LED_RED;    
    DDRD &= ~MASK_D2;    
    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes

    EIMSK |= (1 << INT0) ;
    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    EICRA |= (0 << ISC01) | (1 << ISC00) ;
    // sei permet de recevoir à nouveau des interruptions.
    sei ();
}



int main()
{

    initialisation();    

    delay10S();
    blink();  
    gBoutonPoussoir = 0;            
    partirMinuterie(7812); // 7812 = 1 sec = (1 sec * 8MHz)/1024
    do 
    {
        // attendre qu'une des deux variables soit modifiée
        // par une ou l'autre des interruptions.        
    } while ( gMinuterieExpiree == 0 && gBoutonPoussoir == 0 );


    // Une interruption s'est produite. Arrêter toute

    // forme d'interruption. Une seule réponse suffit.

    cli ();

    // Verifier la réponse

    if(gBoutonPoussoir)   
    {
        turnGreen();
    }
    else
    {
        turnRed();
    }
}