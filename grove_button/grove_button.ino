// ---------------------------------------------------------------
/*
	grove_button.ino

					Aug/08/2021
*/
// ---------------------------------------------------------------
#include <WioLTEforArduino.h>

#define BUTTON_PIN	(WIOLTE_D38)
#define INTERVAL	  (100)

WioLTE Wio;

int icount = 0;
// ---------------------------------------------------------------
void setup()
{
	Wio.Init();	
	pinMode(BUTTON_PIN, INPUT);
}

// ---------------------------------------------------------------
void loop()
{
	int buttonState = digitalRead(BUTTON_PIN);
	SerialUSB.print(buttonState ? '*' : '.');

	if ((icount % 40) == 0)
		{
		SerialUSB.println("");
		}

	if (buttonState)
		{
		Wio.LedSetRGB(0, 0, 1);
		}
	else
		{
		Wio.LedSetRGB(0, 0, 0);
		}
		

	delay(INTERVAL);

	icount++;
}

// ---------------------------------------------------------------
