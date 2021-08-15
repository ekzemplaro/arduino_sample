// ---------------------------------------------------------------
/*
	sd_test.ino

					Aug/09/2021
*/
// ---------------------------------------------------------------
#include <SDforWioLTE.h>

#define FILE_NAME "test_cc.txt"

// ---------------------------------------------------------------
void setup()
{
	delay(1000);
	SerialUSB.println("*** sd_test *** setup *** aaa ***");
	delay(1000);
	SerialUSB.println("*** sd_test *** setup *** bbb ***");
	delay(1000);
	SerialUSB.println("*** sd_test *** setup *** ccc ***");

	SerialUSB.println("");
	SerialUSB.println("*** START ***");

	SerialUSB.println("### Initialize SD card.");
	if (!SD.begin()) {
		SerialUSB.println("### ERROR! SD.begin ###");
		}
	else
		{
//	file_write_proc();
	file_read_proc();
		}

	SerialUSB.println("*** Setup completed ***");
}

// ---------------------------------------------------------------
void loop()
{
	SerialUSB.println("*** loop *** aaa ***");
	delay(3000);
	SerialUSB.println("*** loop *** bbb ***");
	delay(3000);
}

// ---------------------------------------------------------------
void file_write_proc()
{
	File myFile_out;
  
	SerialUSB.println("### Writing to "FILE_NAME".");

	if (SD.exists(FILE_NAME))
		{
		SD.remove(FILE_NAME);
		}

	myFile_out = SD.open(FILE_NAME, FILE_WRITE);
	if (!myFile_out)
		{
		SerialUSB.println("### ERROR! SD.open ###");
		}
	else
		{
		myFile_out.println("testing 1, 2, 3, 4, 5.");
		myFile_out.println("Good Morning.");
		myFile_out.println("Good Afternoon.");
		myFile_out.println("Good Night.");
		myFile_out.println("Aug/09/2021 PM 18:00");
		myFile_out.close();
		}
}

// ---------------------------------------------------------------
void file_read_proc()
{
	File myFile_in;

	SerialUSB.println("*** Reading from "FILE_NAME".");
	myFile_in = SD.open(FILE_NAME,FILE_READ);
	if (!myFile_in) {
		SerialUSB.println("### ERROR! SD.open ###");
	}
	else
		{
		SerialUSB.println(FILE_NAME":");
    int file_size = myFile_in.size();
    SerialUSB.println("file_size = " + String(file_size));

    char* buffer;
    buffer = (char *)malloc(file_size +1);
    myFile_in.read(buffer,file_size);
    buffer[file_size] = '\0';
    SerialUSB.println(buffer);
    SerialUSB.println("-----");

    /*
		while (myFile_in.available()) {
//			String str_in = myFile_in.read();
 //     SerialUSB.write(str_in);
 SerialUSB.write(myFile_in.read());
 // SerialUSB.println("-----");
			}
     */
     
		myFile_in.close();
    free(buffer);
		}
}

// ---------------------------------------------------------------
