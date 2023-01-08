#ifndef DISPLAY_H
#define DISPLAY_H

void initDisp(void);

void idleDisp(void);

void sumDisp(void);

void selDisp(int selPos, int dist, bool atTop, bool atBot);

void chargeDisp(int dist);

void discrgDisp(int dist);

void brakeDisp(void);

#endif