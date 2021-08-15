// ---------------------------------------------------------------------
/*
	hello_world.ino

						Aug/15/2021
*/
// ---------------------------------------------------------------------
int count = 0;

void setup()
{
	// put your setup code here, to run once:

	Serial.begin(19200);
	Serial.println("*** start ***");
}

// ---------------------------------------------------------------------
void loop() 
{
	Serial.println("Hello World! " + String(count));
	delay(1000);
	Serial.println("Good Morning! " + String(count));
	delay(1000);
	Serial.println("こんにちは " + String(count));
	delay(1000);
	count++;
}

// ---------------------------------------------------------------------
