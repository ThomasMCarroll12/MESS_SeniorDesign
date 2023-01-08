#include <Arduino.h>
#include "pushButton.h"
#include "proxSensor.h"
#include "relay.h"
#include "display.h"

// Declare variables used for calculations or state changes
int distance, prevDistance;
int TOPLIM = 10;
int BOTLIM = 100;

int selPos = 0;
unsigned int state = 1;

long debouncing_time = 15; // debounce time in ms
volatile unsigned long last_micros;
volatile int SBpress, CBpress = 0;

void SBInt(void);
void CBInt(void);
void idleToDis(void);

void setup() {
  initButtons();
  initProx();
  initRelay();

  attachInterrupt(digitalPinToInterrupt(3), SBInt, RISING);
  attachInterrupt(digitalPinToInterrupt(2), CBInt, RISING);

  initDisp();
  idleDisp();

  /*Serial.begin(9600);
  while(!Serial);
  Serial.println("Setup Complete\n"); */
}

void loop() {

  distance = getDistanceCM();

  // first check if button pressed
  switch(state){
    case 0: {//summary state
      //Serial.println("Summary State");
      if (SBpress || CBpress){ // return to idle
        idleDisp();
        state = 1;
      }
    break;}

    case 1: {//idle state
      // set all outputs off
      setRelay(0,0,0,0); 
      //Serial.println("Idle State");
      // handle the state change depending on button pressed
      if (SBpress){ // to summary
        sumDisp();
        state = 0; 
      }
      if (CBpress){ // to select
        selPos = 0;
        selDisp(selPos, distance, (distance < TOPLIM), (distance > BOTLIM));
        state = 2;
      }
    break;}

    case 2: {//select state
      //Serial.println("Select State");
      switch(selPos){
        case 0:
          //Serial.println("cancel");
          if (CBpress){ 
            state = 1;
            selPos = 0;
            idleDisp();
          }
        break;
        case 1:
          //Serial.println("charge");
          if (CBpress){
            state = 3;
            selPos = 0;
            chargeDisp(distance);
          } 
        break;
        case 2:
          //Serial.println("discharge");
          if (CBpress){
            state = 4;
            selPos = 0;
            discrgDisp(distance);
            idleToDis();
          }
        break;
        default:
          selPos = 0;
      }
      if (SBpress){
        selPos = selPos + 1;
        if ((selPos == 1) && (distance < TOPLIM)) selPos = selPos + 1;
        if ((selPos == 2) && (distance > BOTLIM)) selPos = selPos + 1;
        if (selPos>2) selPos = 0;

        selDisp(selPos, distance, (distance < TOPLIM), (distance > BOTLIM));
      }
    break;}

    case 3: {//charge state
      setRelay(0,0,1,0);
      chargeDisp(distance);
      //Serial.println("Charge State");
      if ((distance <= TOPLIM) || CBpress){
        state = 1;
        idleDisp();
      }
    break;}

    case 4: {//discharge state
      setRelay(1,0,0,1);
      discrgDisp(distance);
      //Serial.println("Discharge State");
      if (((distance >= BOTLIM) && (distance != 999)) || CBpress){
        state = 5;
        brakeDisp();
      }
    break;}

    case 5: {//braking state
      setRelay(1,1,0,1);
      //Serial.println("Braking State");
      if (abs(distance - prevDistance) < 2){
        state = 1;
        idleDisp();
      }

    break;}

    default:
      state = 1; //you shouldnt be here >:|
  }

  SBpress = 0;
  CBpress = 0;
  prevDistance = distance;
  //Serial.println(distance);

  delay(200);
}

void SBInt(){
  if((long)(micros() - last_micros) >= debouncing_time * 100){ // if the button was pressed than debounce time accept value
    SBpress = 1;
    last_micros = micros();
  }
}

void CBInt(){
  if((long)(micros() - last_micros) >= debouncing_time * 100){ // if the button was pressed than debounce time accept value
    CBpress = 1;
    last_micros = micros();
  }
}

void idleToDis(){
  delay(50);
  setRelay(0,0,1,1);
  // turn on motor here
  delay(400);
  setRelay(1,0,1,1);
  delay(200);
  setRelay(1,0,0,1);
}