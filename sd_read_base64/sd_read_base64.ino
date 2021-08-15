// ---------------------------------------------------------------
/*
	sd_read_base64.ino

					Aug/09/2021
*/
// ---------------------------------------------------------------
#include <SDforWioLTE.h>
#include <Base64.h>

// #define FILE_NAME "test_cc.txt"
#define FILE_NAME "image00.txt"

// ---------------------------------------------------------------
void setup()
{
char mydata[8192];

//	char encoded[512];

	delay(1000);
	SerialUSB.println("*** sd_read_base64 *** setup *** aaa ***");
	delay(1000);
	SerialUSB.println("*** sd_read_base64 *** setup *** bbb ***");
	delay(1000);
	SerialUSB.println("*** sd_read_base64 *** setup *** ccc ***");

	SerialUSB.println("");
	SerialUSB.println("*** START ***");

	SerialUSB.println("### Initialize SD card.");
	if (!SD.begin()) {
		SerialUSB.println("### ERROR! SD.begin ###");
		}
	else
		{
		file_read_proc(mydata);
//		SerialUSB.println(buffer);
		SerialUSB.println("-----");
//		int inputLen = sizeof(buffer);
//		SerialUSB.println("inputLen = " + String(inputLen));
//		base64_encode(encoded, buffer, inputLen);
//		SerialUSB.println(encoded);
// sprintf(mydata,"%s\0",buffer);
SerialUSB.println(mydata);
		SerialUSB.println("-----");
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
void file_read_proc(char mydata[])
{
	File myFile_in;
 char* buffer;
 // char mydata[8192];

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
buffer = (char *)malloc(file_size + 1);
		myFile_in.read(buffer,file_size);
		buffer[file_size] = '\0';
int inputLen = sizeof(buffer);
    SerialUSB.println("inputLen = " + String(inputLen));	 
		myFile_in.close();

    sprintf(mydata,"%s\0",buffer);
SerialUSB.println(mydata);
		}
}

// ---------------------------------------------------------------
