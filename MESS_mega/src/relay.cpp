#include <Arduino.h>
#include "relay.h"

// Brake & Pawl solenoids + Motor & Generator clutch
int relay_1_PS = 22; // 22 Pawl solenoid
int relay_2_BS = 23; // 23 Brake solenoid
int relay_3_MC = 24; // 24 Motor clutch
int relay_4_GC = 25; // 25 Generator clutch

void initRelay(void){
    // set all relay signals as outputs
    pinMode(relay_1_PS, OUTPUT);
    pinMode(relay_2_BS, OUTPUT);
    pinMode(relay_3_MC, OUTPUT);
    pinMode(relay_4_GC, OUTPUT);
}

void setRelay(bool PS, bool BS, bool MC, bool GC){
    // write each signal that that of its corresponding relay signal
    digitalWrite(relay_1_PS, PS);
    digitalWrite(relay_2_BS, BS);
    digitalWrite(relay_3_MC, MC);
    digitalWrite(relay_4_GC, GC);
}