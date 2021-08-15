// ---------------------------------------------------------------
/*
	harvest_temperature.ino

					Aug/08/2021
*/
// ---------------------------------------------------------------
#include <WioLTEforArduino.h>
#include <ArduinoJson.h>
#include <stdio.h>

// #define INTERVAL	(600000)
#define INTERVAL  (60000)

#define RECEIVE_TIMEOUT (10000)
#define SENSOR_PIN    (WIOLTE_D38)

WioLTE Wio;
DynamicJsonDocument doc(1024);
int TemperatureAndHumidityPin;
int count = 0;

// ---------------------------------------------------------------
void setup() {
	setupLTE();

	TemperatureAndHumidityBegin(SENSOR_PIN);

	SerialUSB.println("### Setup completed. *** Aug/08/2021 PM 13:30");
}

// ---------------------------------------------------------------
void loop() {
	char data_json[128];
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

	doc["temp"] = temp;
	doc["humi"] = humi;

	serializeJson(doc, data_json);

	int connectId = udp_open_proc();

	if (0 <= connectId)
		{
		boolean result = udp_send_proc(connectId,data_json);

		if (result)
			{
			result = udp_receive_proc(connectId);
			}
		}

	udp_close_proc(connectId);
	
	Wio.LedSetRGB(0, 0, 1); 
	delay(INTERVAL / 4);
	Wio.LedSetRGB(0, 1, 0); 
	delay(INTERVAL / 4);
	Wio.LedSetRGB(1, 1, 1); 
	delay(INTERVAL / 4);
	Wio.LedSetRGB(0, 0, 0); 
	delay(INTERVAL / 4);

	count++;
}

// ---------------------------------------------------------------
