// ---------------------------------------------------------------
/*
	magnetic_switch.ino

					Aug/05/2021
*/
// ---------------------------------------------------------------
#include <WioLTEforArduino.h>

#define MAGNETIC_SWITCH_PIN (WIOLTE_D38)
#define INTERVAL            (100)

WioLTE Wio;
int icount = 0;
// ---------------------------------------------------------------
void setup()
{
	Wio.Init(); 
  
	pinMode(MAGNETIC_SWITCH_PIN, INPUT);
}

// ---------------------------------------------------------------
void loop()
{
	int switchState = digitalRead(MAGNETIC_SWITCH_PIN);
	SerialUSB.print(switchState ? '*' : '.');

	if (switchState)
		{
		Wio.LedSetRGB(1, 0, 0);
		}
	else
		{
		Wio.LedSetRGB(0, 0, 1);
		}
	
	delay(INTERVAL);

	if ((icount % 40) == 0)
		{
		SerialUSB.println("");
		}
	icount++;
}

// ---------------------------------------------------------------
