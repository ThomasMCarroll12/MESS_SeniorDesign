#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "display.h"

LiquidCrystal_I2C lcd(0x27,20,4); // default i2c address 

void initDisp(void){
    lcd.init();
    lcd.setBacklight(HIGH);
}

void idleDisp(void){
    lcd.noBlink();
    lcd.setCursor(0,0);
    lcd.print("Press CB to charge  ");
    lcd.setCursor(0,1);
    lcd.print("discharge the system");
    lcd.setCursor(0,2);
    lcd.print("Press SB to view the");
    lcd.setCursor(0,3);
    lcd.print("previous cycle stats");
}

void sumDisp(void){  // FIX ME TO ADD POWER READINGS
    lcd.noBlink();
    lcd.setCursor(0,0);
    lcd.print("Energy:  ####.## KWH");
    lcd.setCursor(0,1);
    lcd.print("Avg Power: ####.## W");
    lcd.setCursor(0,2);
    lcd.print("Cycle Length: #### S");
    lcd.setCursor(0,3);
    lcd.print("Press S|CB to return");
}

void selDisp(int selPos, int dist, bool atTop, bool atBot){
    lcd.setCursor(0,0);
    lcd.print(" Press SB to select ");
    lcd.setCursor(0,1);
    lcd.print(" and CB to confirm  ");
    lcd.setCursor(0,2);
    // depending on distance limit the options
    if (atBot) lcd.print("       Charge       ");
    else if (atTop) lcd.print("     Discharge      ");
    else lcd.print("  Charge  Discharge ");

    lcd.setCursor(0,3);
    lcd.print("        Back        "); 
    
    lcd.blink();
    switch (selPos){
        case 0: // cancel is alwasy the same position
        lcd.setCursor(8,3);
        break;
        case 1: // charge 
        if (atBot) lcd.setCursor(7,2);
        else lcd.setCursor(2,2);
        break;
        case 2: // discharge
        if (atTop) lcd.setCursor(5,2);
        else lcd.setCursor(10,2);
        break;
    }
}

void chargeDisp(int dist){ // FIX ME TO ADD POWER READINGS
    lcd.noBlink();
    lcd.setCursor(0,0);
    lcd.print("Consumed P: ###.## W");
    lcd.setCursor(0,1);
    lcd.print("V:  ###.##  A: ###.##"); // FIX HERE
    lcd.setCursor(0,2);

    char temp[21];
    sprintf(temp, "Distance: %6d CM", dist);
    lcd.print(temp);

    lcd.setCursor(0,3);
    lcd.print("Press CB to cancel  ");
}

void discrgDisp(int dist){ // FIX ME TO ADD POWER READINGS
    lcd.noBlink();
    lcd.setCursor(0,0);
    lcd.print("Generated P: ###.##W");
    lcd.setCursor(0,1);
    lcd.print("V:  ###.##  A: ###.##"); // FIX HERE
    lcd.setCursor(0,2);

    char temp[21];
    sprintf(temp, "Distance: %6d CM", dist);
    lcd.print(temp);

    lcd.setCursor(0,3);
    lcd.print("Press CB to cancel  ");
}

void brakeDisp(void){
    lcd.noBlink();
    lcd.setCursor(0,0);
    lcd.print("  Ending Discharge  ");
    lcd.setCursor(0,1);
    lcd.print("       Cycle        ");
    lcd.setCursor(0,2);
    lcd.print("                    ");
    lcd.setCursor(0,3);
    lcd.print("     Please Wait    ");
}