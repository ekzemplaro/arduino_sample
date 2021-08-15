// ---------------------------------------------------------------
/*
	harvest_http.ino

					Aug/08/2021
*/
// ---------------------------------------------------------------
#include <WioLTEforArduino.h>
#include <ArduinoJson.h>
#include <stdio.h>

#define URL	"http://harvest.soracom.io"
#define SENSOR_PIN	(WIOLTE_D38)
#define INTERVAL	(10000)

DynamicJsonDocument doc(1024);

WioLTE Wio;
int TemperatureAndHumidityPin;

int icount = 0;

// ---------------------------------------------------------------
void setup() {
	setupLTE();

	TemperatureAndHumidityBegin(SENSOR_PIN);

	SerialUSB.println("*** Setup completed *** Aug/08/2021 PM 18:20");
}

// ---------------------------------------------------------------
void loop() {
	char data_json[128];
	int status;
	float temp;
	float humi;
	
	SerialUSB.println("*** loop ***");

	SerialUSB.println("icount = " + String(icount));
	
	if (!TemperatureAndHumidityRead(&temp, &humi))
		{
		SerialUSB.println("ERROR! *** TemperatureAndHumidityRead");
		}
	else
		{
		SerialUSB.print("Current humidity = ");
		SerialUSB.print(humi);
		SerialUSB.print("%  ");
		SerialUSB.print("temperature = ");
		SerialUSB.print(temp);
		SerialUSB.println("C");
		}

	doc["temp"] = temp;
	doc["humi"] = humi;

	serializeJson(doc, data_json);	
	 
	SerialUSB.print("Post:");
	SerialUSB.print(data_json);
	SerialUSB.println("");

	if (!Wio.HttpPost(URL, data_json, &status))
		{
		SerialUSB.println("### ERROR! HttpPost ###");
		}
	else
		{
		SerialUSB.print("Status: ");
		SerialUSB.println(status);
 		}
 
	SerialUSB.println("### Wait.");

	Wio.LedSetRGB(0, 0, 1); 
	delay(INTERVAL / 4);
	Wio.LedSetRGB(0, 1, 0); 
	delay(INTERVAL / 4);
	Wio.LedSetRGB(1, 1, 1); 
	delay(INTERVAL / 4);
	Wio.LedSetRGB(0, 0, 0); 
	delay(INTERVAL / 4);

	icount++;
}

// ---------------------------------------------------------------
