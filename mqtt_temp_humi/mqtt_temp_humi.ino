// ---------------------------------------------------------------
/*
	mqtt_temp_humi.ino

					Aug/12/2021
*/
// ---------------------------------------------------------------
#include <WioLTEforArduino.h>
#include <WioLTEClient.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <stdio.h>

#define MQTT_SERVER_HOST  "test.mosquitto.org"
#define MQTT_SERVER_PORT  (1883)

#define ID		"WioLTE"
#define OUT_TOPIC	"example/testTopic"
#define IN_TOPIC	"example/testTopic"

// #define INTERVAL	(60000)
#define INTERVAL	(5000)
#define SENSOR_PIN	(WIOLTE_D38)

WioLTE Wio;
WioLTEClient WioClient(&Wio);
PubSubClient MqttClient;

int TemperatureAndHumidityPin;

int	count = 0;
// ---------------------------------------------------------------
void callback(char* topic, byte* payload, unsigned int length)
{
	SerialUSB.println("");
	payload[length] = '\0';
	String msg = String((char*) payload);
	SerialUSB.println(msg);
}

// ---------------------------------------------------------------
void setup()
{
	setupLTE();

	SerialUSB.println("### Connecting to MQTT server \""MQTT_SERVER_HOST"\"");
	MqttClient.setServer(MQTT_SERVER_HOST, MQTT_SERVER_PORT);
	MqttClient.setCallback(callback);
	MqttClient.setClient(WioClient);
	if (!MqttClient.connect(ID)) {
		SerialUSB.println("### ERROR! connect() ###");
	}
	else
		{
		MqttClient.subscribe(IN_TOPIC);

		TemperatureAndHumidityBegin(SENSOR_PIN);
		}

	SerialUSB.println("*** Setup completed *** Aug/12/2021 PM 12:20 ***");
}

// ---------------------------------------------------------------
void loop()
{
	Wio.LedSetRGB(1, 1, 0); 
	MqttClient.loop();
	SerialUSB.println("*** check *** " + String(count));

	mqtt_temp_humi_send_proc(count);

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
void mqtt_temp_humi_send_proc(int count)
{
	DynamicJsonDocument doc(1024);
	char data_json[128];
	float temp;
	float humi;

	if (!TemperatureAndHumidityRead(&temp, &humi))
		{
		SerialUSB.println("ERROR! *** TemperatureAndHumidityRead");
		}
	else
		{
		SerialUSB.print("count = ");
		SerialUSB.print(count);
		SerialUSB.print(" temperature = ");
		SerialUSB.print(temp);
		SerialUSB.print("C ");
		SerialUSB.print("Current humidity = ");
		SerialUSB.print(humi);
		SerialUSB.println("%  ");

		doc["count"] = count;
		doc["temp"] = temp;
		doc["humi"] = humi;

		serializeJson(doc, data_json);
		SerialUSB.println(data_json);

		MqttClient.publish(OUT_TOPIC, data_json);
		}
}

// ---------------------------------------------------------------
