// ---------------------------------------------------------------
/*
	mqtt_buzzer.ino

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

// #define INTERVAL          (60000)

#define BUZZER_PIN      (WIOLTE_D38)
#define BUZZER_ON_TIME  (100)
#define BUZZER_OFF_TIME (2000)


WioLTE Wio;
WioLTEClient WioClient(&Wio);
PubSubClient MqttClient;

DynamicJsonDocument doc(1024);

int icount = 0;
int status_buzzer = false;
// ---------------------------------------------------------------
void callback(char* topic, byte* payload, unsigned int length) {
	SerialUSB.println("");
	payload[length] = '\0';
	String msg = String((char*) payload);
	SerialUSB.println(msg);
	deserializeJson(doc, msg);

	const char* buzzer = doc["buzzer"];

	if (strstr(buzzer,"on"))
		{
		status_buzzer = true;
		SerialUSB.println("*** callback *** on ***");
		Wio.LedSetRGB(0, 1, 0);
		digitalWrite(BUZZER_PIN, HIGH);
		delay(BUZZER_ON_TIME);
		digitalWrite(BUZZER_PIN, LOW);
		}
	else if (strstr(buzzer,"off"))
		{	
		status_buzzer = false;
		SerialUSB.println("*** callback *** off ***");
		Wio.LedSetRGB(1, 0, 0);
		digitalWrite(BUZZER_PIN, LOW);
		}
}

// ---------------------------------------------------------------
void setup() {
	setupLTE();

	pinMode(BUZZER_PIN, OUTPUT);	

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
	SerialUSB.println("*** Setup completed *** Aug/13/2021 PM 13:40 ***");
		}
}

// ---------------------------------------------------------------
void loop()
{
	char data[100];

	if ((icount % 20) == 0)
		{
		sprintf(data, "{\"uptime\":%lu}", millis() / 1000);
		SerialUSB.print("Publish:");
		SerialUSB.print(data);
		SerialUSB.println("");
		MqttClient.publish(OUT_TOPIC, data);
		}

	MqttClient.loop();
	SerialUSB.print(".");

	if (status_buzzer)
		{
		SerialUSB.println("*** loop *** on ***");
		digitalWrite(BUZZER_PIN, HIGH);
		delay(BUZZER_ON_TIME);
		SerialUSB.println("*** loop *** off ***");
		digitalWrite(BUZZER_PIN, LOW);
		}

	for (int it=0; it<4; it++)
		{
		delay(BUZZER_OFF_TIME / 4);
		MqttClient.loop();
		}

	icount++;
}

// ---------------------------------------------------------------
