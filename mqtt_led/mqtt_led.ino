// ---------------------------------------------------------------
/*
	mqtt_led.ino

					Aug/13/2021
*/
// ---------------------------------------------------------------
#include <WioLTEforArduino.h>
#include <WioLTEClient.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <stdio.h>

// #define MQTT_SERVER_HOST  "broker.emqx.io"
#define MQTT_SERVER_HOST  "test.mosquitto.org"
#define MQTT_SERVER_PORT  (1883)

#define ID                "WioLTE"
#define OUT_TOPIC         "example/testTopic"
#define IN_TOPIC          "example/testTopic"

#define INTERVAL          (60000)

WioLTE Wio;
WioLTEClient WioClient(&Wio);
PubSubClient MqttClient;

DynamicJsonDocument doc(1024);

// ---------------------------------------------------------------
void callback(char* topic, byte* payload, unsigned int length) {
	SerialUSB.println("");
	payload[length] = '\0';
	String msg = String((char*) payload);
	SerialUSB.println(msg);
	deserializeJson(doc, msg);	
	const char* led = doc["led"];
	SerialUSB.println(led);
	
	if (strstr(led,"green")) {	
		SerialUSB.println("*** green ***");
		Wio.LedSetRGB(0, 1, 0); 
		}
	else if (strstr(led,"yellow")) {	
		SerialUSB.println("*** yellow ***");
		Wio.LedSetRGB(1, 1, 0); 
		}
	else if (strstr(led,"red")) {	
		SerialUSB.println("*** red ***");
		Wio.LedSetRGB(1, 0, 0);
		}
	else if (strstr(led,"white")) { 
		SerialUSB.println("*** white ***");
		Wio.LedSetRGB(1, 1, 1);
		}
}

// ---------------------------------------------------------------
void setup() {
	setupLTE();

	SerialUSB.println("### Connecting to MQTT server \""MQTT_SERVER_HOST"\"");
	MqttClient.setServer(MQTT_SERVER_HOST, MQTT_SERVER_PORT);
	MqttClient.setCallback(callback);
	MqttClient.setClient(WioClient);
	if (!MqttClient.connect(ID))
		{
		SerialUSB.println("### ERROR! connect ###");
		}
	else
		{
		MqttClient.subscribe(IN_TOPIC);
		Wio.LedSetRGB(1, 1, 1); 
	SerialUSB.println("*** Setup completed *** Aug/13/2021 AM 09:54 ***");
		}

}

// ---------------------------------------------------------------
void loop() {
	char data[100];
	sprintf(data, "{\"uptime\":%lu}", millis() / 1000);
	SerialUSB.print("Publish:");
	SerialUSB.print(data);
	SerialUSB.println("");
	MqttClient.publish(OUT_TOPIC, data);
	
	unsigned long next = millis();
	while (millis() < next + INTERVAL)
		{
		MqttClient.loop();
		SerialUSB.print(".");
		delay(500);
		}
}

// ---------------------------------------------------------------
