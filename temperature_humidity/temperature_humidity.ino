// ---------------------------------------------------------------
/*
	temperature_humidity.ino

					Apr/08/2021
*/
// ---------------------------------------------------------------
#include <WioLTEforArduino.h>

#define SENSOR_PIN    (WIOLTE_D38)
WioLTE Wio;
int TemperatureAndHumidityPin;

int count = 0;
// ---------------------------------------------------------------
void setup()
{
	Wio.Init(); 
	TemperatureAndHumidityBegin(SENSOR_PIN);
}

// ---------------------------------------------------------------
void loop()
{
	float temp;
	float humi;

	SerialUSB.println("*** loop *** aaa *** count = " + String(count));

	if (!TemperatureAndHumidityRead(&temp, &humi))
		{
		SerialUSB.println("ERROR! *** TemperatureAndHumidityRead");
		}
	else
		{
	SerialUSB.print("Current humidity = ");
	SerialUSB.print(humi);
	SerialUSB.print("%	");
	SerialUSB.print("temperature = ");
	SerialUSB.print(temp);
	SerialUSB.println("C");
		}

	delay(2000);

	if (count == 0)
		{
		SerialUSB.println("*** temperature_humidity *** Aug/08/2021 ***");
		}

	if ((count % 2) == 0)
		{
		Wio.LedSetRGB(0, 0, 1);
		}
	else
		{
		Wio.LedSetRGB(0, 0, 0);
		}

	count++;
}

// ---------------------------------------------------------------
