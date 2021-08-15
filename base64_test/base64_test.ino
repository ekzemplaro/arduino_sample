// ---------------------------------------------------------------
/*
	base64_test.ino

						Aug/15/2021
*/
// ---------------------------------------------------------------
#include <Base64.h>

// ---------------------------------------------------------------
void setup()
{
  Serial.begin(19200);
	delay (1000);
	Serial.println("*** start ***");
	delay(500);
	Serial.println("*** Base64 example ***");
	delay(500);
	
	char Buf[50];

	int llx = 8;
	String str_array[] = {"A","AB","ABC","ABCD","ABCDE","ABCDEF","ABCDEFG",
		"ABCDEFGH"};


Serial.println ("llx = " + String(llx));
delay(1000);

 for (int itt=0; itt < llx; itt++)
 {
		str_array[itt].toCharArray(Buf, 50);	
		String str_encoded = encode_proc(Buf);
		Serial.println(str_encoded);

   delay(300);
		}

	delay(500);
	Serial.println("*** setup *** end ***");
}

// ---------------------------------------------------------------

String encode_proc(char* input)
{
	Serial.println(input);

	int inputLen = strlen(input);
	
	int encodedLen = Base64.encodedLength(inputLen);
	char encoded[encodedLen];

	Base64.encode(encoded, input, inputLen); 
	

	return String(encoded);
}

// ---------------------------------------------------------------
void loop()
{
	Serial.println("*** loop ***");
	delay (3000); 
}

// ---------------------------------------------------------------
