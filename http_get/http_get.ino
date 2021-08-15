// ---------------------------------------------------------------
/*
	http_test.ino

						Aug/08/2021
*/
// ---------------------------------------------------------------
#include <WioLTEforArduino.h>
#include <stdio.h>

#define URL	"https://httpbin.org/get?user=jiro&password=123456"

#define INTERVAL          (10000)

WioLTE Wio;
	
// ---------------------------------------------------------------
void setup() {
	setupLTE();

	SerialUSB.println("### Setup completed.");
}

// ---------------------------------------------------------------
void loop() {
	char data[1024];
	int dataSize;
	dataSize=sizeof(data);
	
	SerialUSB.println("### Get.");
	SerialUSB.println(URL);
	SerialUSB.println("Aug/07/2021 PM 14:08");

	int rvalue;
	rvalue = Wio.HttpGet(URL, data, dataSize);
	if (!rvalue) {
		SerialUSB.println("### ERROR! HttpGet ###");
	}
	else
		{
		SerialUSB.print("dataSize: ");
		SerialUSB.println(dataSize);
		SerialUSB.println(String(data));
		SerialUSB.print("rvalue: ");
		SerialUSB.println(rvalue);
		}

	SerialUSB.println("*** Wait *** aaa ***");
	Wio.LedSetRGB(0, 0, 1); 
	delay(INTERVAL / 2);
	SerialUSB.println("*** Wait *** bbb ***");
	Wio.LedSetRGB(0, 0, 0); 
	delay(INTERVAL / 2);
}

// ---------------------------------------------------------------
