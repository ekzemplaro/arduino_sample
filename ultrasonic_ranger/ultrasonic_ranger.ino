// ---------------------------------------------------------------
/*
	ultrasonic_ranger.ino

					Aug/06/2021
*/
// ---------------------------------------------------------------
#include <WioLTEforArduino.h>
#include <Ultrasonic.h>

#define ULTRASONIC_PIN	(WIOLTE_D38)
#define INTERVAL	(500)

Ultrasonic UltrasonicRanger(ULTRASONIC_PIN);

WioLTE Wio;

// ---------------------------------------------------------------
void setup()
{
	Wio.Init();
}

// ---------------------------------------------------------------
void loop()
{
	long distance;
	distance = UltrasonicRanger.MeasureInCentimeters();
	SerialUSB.print(distance);
	SerialUSB.println("[cm]");

	if (100 <= distance)
		{
		Wio.LedSetRGB(0, 0, 1);
		}
	else if (30 <= distance)
		{
		Wio.LedSetRGB(1, 1, 0);
		}	
	else
		{
		Wio.LedSetRGB(1, 0, 0);
		}
	
	delay(INTERVAL);
}

// ---------------------------------------------------------------
