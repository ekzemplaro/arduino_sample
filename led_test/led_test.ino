// ---------------------------------------------------------------
/*
	led_test.ino

					Aug/04/2021
*/
// ---------------------------------------------------------------
 
#include <WioLTEforArduino.h>

WioLTE Wio;

void setup() {
	delay(1000);

	SerialUSB.println("");
	SerialUSB.println("*** START ***");  
	SerialUSB.println("### I/O Initialize.");
	Wio.Init();
	delay(1000);
	SerialUSB.println("### Setup completed.");
	SerialUSB.println("");
}

// ---------------------------------------------------------------
void loop() {
	led_delay_proc(0,0,1,1000,"blue");
	led_delay_proc(0,1,0,1000,"lime");
	led_delay_proc(1,0,0,1000,"red"); 
	led_delay_proc(1,1,0,1000,"yellow");    
	led_delay_proc(0,1,1,1000,"cyan");
	led_delay_proc(0,0,0,2000,"black"); 
	SerialUSB.println("");
}

// ---------------------------------------------------------------
void led_delay_proc(int rr,int gg,int bb,int msec,String mesg){
	Wio.LedSetRGB(rr, gg, bb);
	SerialUSB.println("*** "+ mesg + " ***");
	delay(msec);
}

// ---------------------------------------------------------------
