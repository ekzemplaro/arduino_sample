// ---------------------------------------------------------------
/*
	mqtt_client.ino

					Aug/12/2021
*/
// ---------------------------------------------------------------
#include <WioLTEforArduino.h>
#include <WioLTEClient.h>
#include <PubSubClient.h>
#include <stdio.h>

#define MQTT_SERVER_HOST  "broker.emqx.io"
#define MQTT_SERVER_PORT  (1883)

#define ID                "WioLTE"
#define OUT_TOPIC         "example/testTopic"
#define IN_TOPIC          "example/testTopic"

#define INTERVAL          (60000)

WioLTE Wio;
WioLTEClient WioClient(&Wio);
PubSubClient MqttClient;

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
		return;
	}
	MqttClient.subscribe(IN_TOPIC);

	SerialUSB.println("*** Setup completed *** Aug/12/2021 AM 09:20 ***");
}

// ---------------------------------------------------------------
void loop()
{
	char data[100];
	sprintf(data, "{\"uptime\":%lu}", millis() / 1000);
	SerialUSB.print("Publish:");
	SerialUSB.print(data);
	SerialUSB.println("");
	MqttClient.publish(OUT_TOPIC, data);
	
	unsigned long next = millis();
	while (millis() < next + INTERVAL)
	{
	Wio.LedSetRGB(1, 1, 0); 
		MqttClient.loop();
		SerialUSB.println("*** check ***");

	Wio.LedSetRGB(0, 0, 1); 
	delay(1000);
	Wio.LedSetRGB(0, 1, 0); 
	delay(1000);
	Wio.LedSetRGB(1, 1, 1); 
	delay(1000);
	Wio.LedSetRGB(0, 0, 0); 
	delay(1000);
	}
}

// ---------------------------------------------------------------
