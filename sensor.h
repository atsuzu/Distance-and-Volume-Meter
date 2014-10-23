#ifndef SENSOR_H_
#define SENSOR_H_

#include <avr/io.h>
#include <avr/delay.h>

#include "avr.h"
#include "helper.h"
#include "lcd.h"

void HCSR04InitDist();
void HCSR04TriggerDist();

void HCSR04Init();
void HCSR04Trigger();

void HCSR04Init1();
void HCSR04Trigger1();

void HCSR04Init2();
void HCSR04Trigger2();


#endif 