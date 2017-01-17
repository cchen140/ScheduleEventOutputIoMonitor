#include "Arduino.h"

bool lastScheduleEventOutputSignal;

// bit 0 1 2 3 4 => task number
// bit 5 6 => event type
// bit 7 => signal

void setup()
{
	DDRF = 0x00;
	PORTF = 0x00; // disable pull-ups.

	lastScheduleEventOutputSignal = (PINF & 0x80)>>7;

	Serial1.begin(57600);
	Serial1.println("Serial port starts.");
}

void loop()
{
	uint8_t portValue = PINF;
	//if(1) {
	if ((portValue & 0x80)>>7 != lastScheduleEventOutputSignal) {
		lastScheduleEventOutputSignal = !lastScheduleEventOutputSignal;
		Serial1.print(micros()/1000.0);
		Serial1.print("\ttask=");
		Serial1.print(portValue & 0x1F);
		Serial1.print("\tevent=");
		Serial1.print( (portValue & 0x60) >> 5);
		Serial1.println("");
		//delay(10);
	}
}
