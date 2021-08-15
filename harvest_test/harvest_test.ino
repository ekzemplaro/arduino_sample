// ---------------------------------------------------------------
/*
	harvest_test.ino

					Aug/08/2021
*/
// ---------------------------------------------------------------
#include <WioLTEforArduino.h>
#include <ArduinoJson.h>
#include <stdio.h>

DynamicJsonDocument doc(1024);

#define INTERVAL	(6000)
#define RECEIVE_TIMEOUT (10000)

WioLTE Wio;

float tt_aa[] = {20.1, 22.3, 24.8, 25.6, 26.7, 26.1, 26.2, 25.3, 24.8, 22.6, 21.7, 21.0, 20.5, 20.4, 20.2, 20.1};
float hh_aa[] = {50.2, 62.4, 64.8, 75.6, 76.7, 75.9, 74.3, 72.3, 64.6, 60.5, 56.2, 53.2, 51.8, 51.2, 50.9, 50.4};
int ll_aa[] = {10,50,100,140,220,218,215,200, 180,140,110,70,40,35,25,15};
int mm_aa[] = {15,35,75,90,125,120,115,100, 80,70,65,45,35,30,28,26};

int icount = 0;

// ---------------------------------------------------------------
void setup() {
	setupLTE();

	SerialUSB.println("### Setup completed. *** Aug/09/2021 PM 13:35");
}

// ---------------------------------------------------------------
void loop() {
	char data_json[128];

	int index = icount % 16;

	SerialUSB.println("icount = " + String(icount));

doc["temp"] = tt_aa[index];
doc["humi"] = hh_aa[index];
doc["light"] = ll_aa[index];
doc["moist"] = mm_aa[index];

serializeJson(doc, data_json);

int connectId = udp_open_proc();

if (0 <= connectId) {

	boolean result = udp_send_proc(connectId,data_json);

	if (result)
	 {
		result = udp_receive_proc(connectId);
	}

}

		udp_close_proc(connectId);
	
	delay(INTERVAL);
	icount++;
}

// ---------------------------------------------------------------
