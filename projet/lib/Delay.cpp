#include "Delay.h"

void delayMs(uint16_t duration){    
    uint8_t delayInterval = 50;
    uint8_t nLoop = duration/delayInterval;
    for(uint8_t i = 0; i < nLoop; i++){
        _delay_ms(FUNCTION_DELAY);
    }
}