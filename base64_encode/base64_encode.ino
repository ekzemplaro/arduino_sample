// ---------------------------------------------------------------
/*
	base64_encode.ino

						Aug/15/2021
*/
// ---------------------------------------------------------------
#include <Base64.h>

// ---------------------------------------------------------------
void setup()
{
	SerialUSB.begin(19200);
	delay (1000);
	SerialUSB.println("*** base64_encode.ino *** start ***");
	delay(500);
	SerialUSB.println("*** Base64 example ***");
	delay(500);
	
	char Buf[50];

	int llx = 8;
	String str_array[] = {"ABCDA","ABCDAB","ABCDABC","ABCDABCD","ABCDABCDE","ABCDABCDEF","ABCDABCDEFG",
		"ABCDABCDEFGH"};


SerialUSB.println ("llx = " + String(llx));
delay(1000);

 for (int itt=0; itt < llx; itt++)
 	{
	str_array[itt].toCharArray(Buf, 50);	
	String str_encoded = encode_proc(Buf);
	SerialUSB.println(str_encoded);

	delay(300);
	SerialUSB.println("*** dddd *** itt = " + String(itt));
	}

	delay(500);
	SerialUSB.println("*** setup *** end ***");
}

// ---------------------------------------------------------------
String encode_proc(char* input)
{
	SerialUSB.println(input);
	int inputLen = strlen(input);
 SerialUSB.println("inputLen = " + String(inputLen));
	
//	int encodedLen = Base64.encodedLength(inputLen);
  int encodedLen = base64_enc_len(inputLen);
 SerialUSB.println("encodedLen = " + String(encodedLen));
//	char encoded[100];
	char encoded[encodedLen];

	base64_encode(encoded, input, inputLen); 

	return String(encoded);
}

// ---------------------------------------------------------------
void loop()
{
	SerialUSB.println("*** loop ***");
	delay (3000); 
}

// ---------------------------------------------------------------
