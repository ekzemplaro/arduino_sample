// ---------------------------------------------------------------
/*
	base64_test.ino

						Aug/14/2021
*/
// ---------------------------------------------------------------
#include <Base64.h>

// ---------------------------------------------------------------
void setup()
{
	delay (1000);
	SerialUSB.println("*** start ***");
	delay(500);
	SerialUSB.println("*** Base64 example ***");
	delay(500);
	
	char Buf[50];

	String str_array[7] = {"AB","ABC","ABCD","ABCDE","ABCDEF","ABCDEFG","AA"};

int jt = 0;
	for (int itt=0; itt<6; itt++)
		{
 //   int jt = itt;
		SerialUSB.println("*** aaa *** " + String(jt));
	
		str_array[itt].toCharArray(Buf, 50);	
//  		SerialUSB.println(Buf);
		String str_encoded = encode_proc(Buf);
		SerialUSB.println(str_encoded);
		SerialUSB.println("*** ccc ***");
   jt++;
   
		}

	delay(500);
	SerialUSB.println("*** setup *** end ***");
}

// ---------------------------------------------------------------
String encode_proc(char* input)
{
	SerialUSB.println(input);

	int inputLen = sizeof(input);
	
	int encodedLen = base64_enc_len(inputLen);
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
