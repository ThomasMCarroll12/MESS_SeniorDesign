#include <Arduino.h>

// User inputs through select and continue push buttons
int SB = PIN_PA22; // D0 select
int CB = PIN_PA11; // D3 continue  D1 & D2 are for shield relays 

// Proximity sensor control signals
int Trig = PIN_PB10; // D4 trigger
int Echo = PIN_PB11; // D5 echo

// Brake & Pawl solenoids + Motor & Generator clutch
int relay_1_PS = PIN_PA17; // D9 Pawl solenoid
int relay_2_BS = PIN_PA16; // D8 Brake solenoid
int relay_3_MC = PIN_PA21; // D7 Motor clutch
int relay_4_GC = PIN_PA20; // D6 Generator clutch

// Declare variables used for calculations or state changes
long duration;
int distance;


void setup() {
  pinMode(SB, INPUT_PULLUP);
  pinMode(CB, INPUT_PULLUP);

  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT_PULLUP);

  pinMode(relay_1_PS, OUTPUT);
  pinMode(relay_2_BS, OUTPUT);
  pinMode(relay_3_MC, OUTPUT);
  pinMode(relay_4_GC, OUTPUT);

  Serial.begin(9600);
  while(!Serial);
}

void loop() {
  Serial.println("HELP ME");
}