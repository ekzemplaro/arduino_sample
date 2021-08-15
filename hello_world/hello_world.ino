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

	SerialUSB.begin(19200);
 delay(1000);
 SerialUSB.println("*** start ***");
delay(500);
 SerialUSB.println("*** setup *** aaa ***");
  delay(500);
 SerialUSB.println("*** setup *** bbb ***");
   delay(500);
 SerialUSB.println("*** setup *** ccc ***");
}

// ---------------------------------------------------------------------
void loop() 
{
	SerialUSB.println("Hello World! " + String(count));
	delay(1000);
	SerialUSB.println("Good Morning! " + String(count));
	delay(1000);
	SerialUSB.println("こんにちは " + String(count));
	delay(2000);
	count++;
}

// ---------------------------------------------------------------------
