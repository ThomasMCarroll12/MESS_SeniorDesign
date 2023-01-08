#include <Arduino.h>
#include "proxSensor.h"

// Proximity sensor control signals
int Trig = 26; // 26 trigger
int Echo = 27; // 27 echo

void initProx(void){
    // set trigger as output and echo as input
    pinMode(Trig, OUTPUT);
    pinMode(Echo, INPUT);
}

int getDistanceCM(){
    // send out pulse series over course of 12 us
    digitalWrite(Trig, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig, LOW);

    // get pulse echo lenght and calculate distance in cm
    long tempDist = pulseIn(Echo, HIGH);
    tempDist = tempDist * 0.034 / 2;

    if (tempDist > 183){ // distance limit is 6 feet, well beyond out use fr the device
        tempDist = 999; // set an out of range error boundary
    }

    //Serial.println(tempDist);

    return tempDist;
}
