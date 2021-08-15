// ---------------------------------------------------------------
/*
	grove_buzzer.ino

					Aug/08/2021
*/
// ---------------------------------------------------------------
#include <WioLTEforArduino.h>

#define BUZZER_PIN      (WIOLTE_D38)
#define BUZZER_ON_TIME  (100)
#define BUZZER_OFF_TIME (500)

WioLTE Wio;

int led[5][3] = {{0,0,1},{0,1,0},{1,0,0},{1,1,0},{0,0,0}};

// ---------------------------------------------------------------
void setup()
{
	pinMode(BUZZER_PIN, OUTPUT);
	delay(500);
	Wio.Init();
}

// ---------------------------------------------------------------
void loop()
{
	for (int it=0; it<5; it++)
		{
		digitalWrite(BUZZER_PIN, HIGH);
		Wio.LedSetRGB(led[it][0],led[it][1],led[it][2]);
		delay(BUZZER_ON_TIME);

		digitalWrite(BUZZER_PIN, LOW);

		int time_delay = BUZZER_OFF_TIME * (it + 1);
		delay(time_delay);
		}
}

// ---------------------------------------------------------------
