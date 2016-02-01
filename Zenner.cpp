#include "Arduino.h"
#include "Zenner.h"

ZENNER *ZENNER::__zenner = 0;

ZENNER::ZENNER(int pin,int f,int t_on,int t_off) {
    beepPin = pin;
    frequency = f;
    __t_on = t_on;
    __t_off = t_off;
    //--
    pinMode(beepPin, OUTPUT);
    //--
    __zenner = this;
    clearValues();
    zennerEnabled = FALSE;
    //--
    TCCR1B = (0<<CS12)|(1<<CS11)|(1<<CS10);
    TIMSK1 |= (1<<TOIE1);
    TCNT1 = _teekCount;
    sei();
}

void ZENNER::Start(void) {
    clearValues();
    zennerEnabled = TRUE;
}

void ZENNER::Stop(void) {
    clearValues();
    zennerEnabled = FALSE;
}

ISR(TIMER1_OVF_vect) {
    TCNT1 = _teekCount;
    ZENNER::handle_interrupt();
}

inline void ZENNER::handle_interrupt() {
    if (__zenner->zennerEnabled==1) {
        __zenner->clockTick++;
        __zenner->clockBeep++;
        
        if (__zenner->clockBeep>(_sec/(__zenner->frequency*2)) ) {
            __zenner->clockBeep = 0;
            if (__zenner->clockSec<__zenner->__t_on) {
                __zenner->Beep();
            }
        }
        
        if (__zenner->clockTick>_sec) { //1 sec
            __zenner->clockTick = 0;
            __zenner->clockSec++;
            if (__zenner->clockSec>=(__zenner->__t_on + __zenner->__t_off)) {
                __zenner->clockSec = 0;
            }
        }
    }
}

//-------------------------------
//-- Private
//-------------------------------
void ZENNER::clearValues() {
    clockTick = 0;
    clockSec = 0;
    clockBeep = 0;
}

void ZENNER::Beep() {
    beepVal++;
    digitalWrite(beepPin, beepVal&0x01);
}