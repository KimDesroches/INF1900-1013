#include <Timer.h>

Timer::Timer(uint16_t time, uint16_t prescaler, uint32_t frequency){        
    _time = time; 
    _prescaler = prescaler;
    _frequency = frequency;
}

void Timer::startTimer(volatile bool& isTimerExpired){
    isTimerExpired = false;   
    TCNT1 = 0;
    OCR1A = (_frequency / _prescaler)*_time;
    TCCR1A = 0;
    TCCR1B = (1 << WGM12);
    if (_prescaler == 1024){
        TCCR1B |= (1 << CS12) | (1 << CS10);
    }
    else if (_prescaler == 256){
        TCCR1B |= (1 << CS12);
    }
    else if (_prescaler == 64)
    {
        TCCR1B |= (1 << CS11) | (1 << CS10);
    }
    else if (_prescaler == 8)
    {
        TCCR1B |= (1 << CS11);
    }    
    TIMSK1 |= (1 << OCIE1A);
    sei();
}