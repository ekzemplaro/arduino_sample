// ---------------------------------------------------------------
/*
	setupLTE.ino

					Aug/09/2021
*/
// ---------------------------------------------------------------


#define APN		"soracom.io"
#define USERNAME	"sora"
#define PASSWORD	"sora"

// ---------------------------------------------------------------
void setupLTE() {
	delay(200);

	SerialUSB.println("");
	SerialUSB.println("*** start *** seupLTE ***");

	SerialUSB.println("### I/O Initialize.");
	Wio.Init();

	SerialUSB.println("### Power supply ON.");
	Wio.PowerSupplyLTE(true);
	delay(500);

	SerialUSB.println("### Turn on or reset.");
	if (!Wio.TurnOnOrReset()) {
		SerialUSB.println("### ERROR! TurnOnOrReset ###");
//	return;
	}
	delay(500);

	SerialUSB.println("*** Connecting to \"soracom.io\" ***");
	if (!Wio.Activate(APN, USERNAME, PASSWORD))
		{
		SerialUSB.println("### ERROR! Activate ###");
		}
	else
		{
		SerialUSB.println("*** SetupLTE completed ***");
		}

	SerialUSB.println("*** end *** seupLTE ***");
}

// ---------------------------------------------------------------
