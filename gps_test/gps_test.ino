// ---------------------------------------------------------------
/*
	gps_test.ino


					Aug/06/2021
*/
// ---------------------------------------------------------------
#include <WioLTEforArduino.h>
#define INTERVAL    (500)

WioLTE Wio;

// ---------------------------------------------------------------
void setup()
{
	delay(200);

	SerialUSB.println("");
	SerialUSB.println("*** START ***");
	
	SerialUSB.println("### I/O Initialize.");
	GpsBegin(&SerialUART);
	Wio.Init();
	
	SerialUSB.println("### Power supply ON.");
	Wio.PowerSupplyGrove(true);
	delay(500);
	SerialUSB.println("*** Setup *** ddd");
	delay(500); 
	SerialUSB.println("*** Setup *** eee");
	delay(500);
	SerialUSB.println("*** Setup *** fff");
	delay(500);
	SerialUSB.println("*** Setup completed ***");
}

// ---------------------------------------------------------------
void loop()
{
  	const char* data = GpsRead();

	if (data != NULL)
		{
		if (strncmp(data, "$GPGGA,", 7) == 0) {
			SerialUSB.println(data);
			}
		else if (strncmp(data, "$GPGSA,", 7) == 0) {
			SerialUSB.println(data);
			}
		else if (strncmp(data, "$GPGSV,", 7) == 0) {
			SerialUSB.println(data);
			}
		else if (strncmp(data, "$GPRMC,", 7) == 0) {
			SerialUSB.println(data);
			}
		else
			{
			SerialUSB.print("   : ");
			SerialUSB.println(data);
			}
		}
	else
		{
//		SerialUSB.println("*** error GpsRead ***");
		}


	Wio.LedSetRGB(0, 0, 1); 
	delay(INTERVAL / 2);
	Wio.LedSetRGB(0, 0, 0); 
	delay(INTERVAL / 2);
}

// ---------------------------------------------------------------

#define GPS_OVERFLOW_STRING "OVERFLOW"

HardwareSerial* GpsSerial;
// char GpsData[100];
char GpsData[256];
char GpsDataLength;

// ---------------------------------------------------------------
void GpsBegin(HardwareSerial* serial)
{
	GpsSerial = serial;
	GpsSerial->begin(9600);
	GpsDataLength = 0;
}

// ---------------------------------------------------------------
const char* GpsRead()
{
	while (GpsSerial->available()) {
		char data = GpsSerial->read();
		if (data == '\r') continue;
		if (data == '\n') {
			GpsData[GpsDataLength] = '\0';
			GpsDataLength = 0;
			return GpsData;
		}
		
		if (GpsDataLength > sizeof (GpsData) - 1) { // Overflow
			GpsDataLength = 0;
			return GPS_OVERFLOW_STRING;
		}
		GpsData[GpsDataLength++] = data;
	}

	return NULL;
}

// ---------------------------------------------------------------
