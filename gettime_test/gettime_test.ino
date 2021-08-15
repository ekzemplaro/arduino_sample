// ---------------------------------------------------------------
/*
	gettime_test.ino

					Aug/07/2021
*/
// ---------------------------------------------------------------
#include <WioLTEforArduino.h>

#define INTERVAL	(5000)

WioLTE Wio;

// ---------------------------------------------------------------
void setup() {
	delay(200);

	SerialUSB.println("");
	SerialUSB.println("*** START ***");
	
	SerialUSB.println("### I/O Initialize.");
	Wio.Init();
	
	SerialUSB.println("### Power supply ON.");
	Wio.PowerSupplyLTE(true);
	delay(500);

	SerialUSB.println("### Turn on or reset.");
	if (!Wio.TurnOnOrReset()) {
	  SerialUSB.println("### ERROR! TurnOnOrReset ###");
	  return;
	}
	delay(3000);
	


	SerialUSB.println("### Setup completed.");
}

// ---------------------------------------------------------------
void loop() {
	SerialUSB.println("*** loop start ***");
	SerialUSB.println("### Get time. ***");
	struct tm now;
	
	if (!Wio.GetTime(&now)) {
	  SerialUSB.println("### ERROR! ###");
	}
	else
		{
	SerialUSB.print("UTC:");
	SerialUSB.println(asctime(&now));
	SerialUSB.println("*** check bbb ***");
	}

	Wio.LedSetRGB(0, 0, 1); 
	delay(INTERVAL / 2);
	Wio.LedSetRGB(0, 0, 0); 
	delay(INTERVAL / 2);	
//	delay(INTERVAL);
	  SerialUSB.println("*** check ccc ***");
}

// ---------------------------------------------------------------
