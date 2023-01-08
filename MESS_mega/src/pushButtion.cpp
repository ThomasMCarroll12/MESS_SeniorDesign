#include <Arduino.h>
#include "pushButton.h"

// User inputs through select and continue push buttons
int SB = 3; // 3 select
int CB = 2; // 2 continue 

void initButtons(void){
  // set buttions to input with pullup to reduce input current
  pinMode(SB, INPUT_PULLUP);
  pinMode(CB, INPUT_PULLUP);
}