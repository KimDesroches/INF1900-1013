#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>


bool isButtonPressed()
{
    uint8_t lecture1 = PIND & 0x04;;
    _delay_ms(10);
    uint8_t lecture2 = PIND & 0x04;
    bool signalIsHigh = (lecture1 == 0x04);
    bool signIsStable = lecture1 == lecture2;

    if (signalIsHigh && signIsStable){
        return true;
    }
    else{
        return false;
    }
    
    
}


int main()
{
    //ON ne met jamais des registre = a qqc
    DDRA = 0xFF; // a changer 
    DDRD = 0x00; 

//bool ambree = false;
int etat = 0; // 0 -> etaint, 1 ->rouge, 2 ->vert, 3->ambree

while (true)
{
 

    if (isButtonPressed() && (etat == 0 || etat == 3)){
        etat = 1;
        PORTA = 0x02;    
        _delay_ms(1000);       
    }
    if (isButtonPressed() && etat == 1){
        etat = 2;
        PORTA = 0x01;
        _delay_ms(1000);
    }
    
    if (isButtonPressed()&& etat == 2){
        etat = 3;                      
        _delay_ms(1000);
        while(!isButtonPressed()){
            PORTA = 0x02;
            _delay_ms(100);
            PORTA = 0x01;
            _delay_ms(100);                  
        }
        
    }
    
}
}