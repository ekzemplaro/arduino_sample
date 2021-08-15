// ---------------------------------------------------------------
/*
	get_phone_number.io

					Aug/08/2021
*/
// ---------------------------------------------------------------
#include <WioLTEforArduino.h>
#define INTERVAL    (2000)

WioLTE Wio;

// ---------------------------------------------------------------
void setup() {
	char num[20];

	setupLTE();

	SerialUSB.println("*** Setup bbb ***");
	delay(1000);
	SerialUSB.println("*** Setup ccc ***");
	delay(1000);
	SerialUSB.println("*** Setup ddd ***");
	delay(1000);
	SerialUSB.println("*** Setup eee ***");

	int numberSize = sizeof(num);

	int vv =  Wio.GetPhoneNumber(num,numberSize);

	if(0 < vv)
		{
		SerialUSB.println(num);
		}
	else
		{
		SerialUSB.println("*** error *** GetPhoneNumber ***");
		SerialUSB.println("vv = " + String(vv));
		}

	SerialUSB.println("*** setup completed *** Aug/08/2021 ***");
}

// ---------------------------------------------------------------
void loop() {
	SerialUSB.println("*** loop *** aaa ***");
	Wio.LedSetRGB(0, 0, 1); 
	delay(INTERVAL / 2);
	SerialUSB.println("*** loop *** bbb ***");
	Wio.LedSetRGB(0, 0, 0); 
	delay(INTERVAL / 2);
}

// ---------------------------------------------------------------
