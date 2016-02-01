/*
*/

#ifndef __Zenner_h__
#define __Zenner_h__

#include "Arduino.h"
#include <Wire.h>

#define _sec 960 //440
#define _teekCount 65535
#define FALSE 0
#define TRUE 1

class ZENNER {
    public:
        ZENNER(int pin,int f,int t_on,int t_off);
        void Start(void);
        void Stop(void);
        static inline void handle_interrupt();;
    private:
        void Beep();
        void clearValues();
        //--Values
        static ZENNER *__zenner;
        int clockTick;
        int clockSec;
        int clockBeep;
        uint8_t beepVal;
        int zennerEnabled;
        //--Init Values
        int frequency;
        int __t_on;
        int __t_off;
        int beepPin;
};

#endif /* __Zenner_h__ */
