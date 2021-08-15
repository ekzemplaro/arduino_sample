// ---------------------------------------------------------------
/*
	accelerometer_adxl.ino

					Aug/06/2021
*/
// ---------------------------------------------------------------
#include <WioLTEforArduino.h>
#include <ADXL345.h>

#define INTERVAL    (5000)

WioLTE Wio;
ADXL345 Accel;

// ---------------------------------------------------------------
void setup()
{
	delay(200);

	SerialUSB.println("");
	SerialUSB.println("*** START ***");
	
	SerialUSB.println("### I/O Initialize.");
	Wio.Init();
	
	SerialUSB.println("### Power supply ON.");
	Wio.PowerSupplyGrove(true);
	delay(500);
	Accel.powerOn();
	
	SerialUSB.println("### Setup completed.");
}

// ---------------------------------------------------------------
void loop()
{
	int value[3];
	Accel.readXYZ(&value[0], &value[1], &value[2]);

	SerialUSB.print("ADXL: X: ");
	SerialUSB.print(value[0]);
	SerialUSB.print(" Y: ");
	SerialUSB.print(value[1]);
	SerialUSB.print(" Z: ");
	SerialUSB.println(value[2]);

	Wio.LedSetRGB(0, 0, 1);	
	delay(INTERVAL / 2);
	Wio.LedSetRGB(0, 0, 0);	
	delay(INTERVAL / 2);
}

// ---------------------------------------------------------------
