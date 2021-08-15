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

	String str_array[6] = {"AB","ABC","ABCD","ABCDE","ABCDEF","ABCDEFG"};

	for (int it=0; it<6; it++)
		{	
		str_array[it].toCharArray(Buf, 50);	
		char* encoded_aa = encode_proc(Buf);
		SerialUSB.println(encoded_aa);
		}

	delay(500);
	SerialUSB.println("*** setup *** end ***");
}

// ---------------------------------------------------------------
char* encode_proc(char* input)
{
	int inputLen = sizeof(input);
	
	int encodedLen = base64_enc_len(inputLen);
	char encoded[encodedLen];
	char encoded_tmp[10];
/*
	int quotient = inputLen / 3;
	SerialUSB.println("*** encode_proc *** start ***");
	SerialUSB.println("inputLen = " + String(inputLen));
	SerialUSB.println("encodedLen = " + String(encodedLen));
	SerialUSB.println(input);

	int limit = 0;
	int count = 0;
	int ipos = 0;

	while (ipos <= inputLen)
		{ 
		if (count <= quotient)
			{
			limit = 3;
			count++;
			}
		else if ((inputLen %3) == 1)
			{
			limit = 1;
			}
		else if ((inputLen %3) == 2)
			{
			limit = 2;
			}
		base64_encode(encoded_tmp, &input[ipos], limit); 
		ipos += limit;
		int ix = sizeof(encoded_tmp);

		strcpy(encoded,encoded_tmp);
		}
*/
	// note input is consumed in this step: it will be empty afterwards
	base64_encode(encoded, input, inputLen); 
	
	SerialUSB.println(encoded);

	return encoded;
}

// ---------------------------------------------------------------
char* decode_proc(char* input_in)
{
	int input2Len = sizeof(input_in);
	
	int decodedLen = base64_dec_len(input_in, input2Len);
	char decoded[decodedLen];
	
	SerialUSB.println("*** decode_proc *** start ***");
	SerialUSB.println("input2Len = " + String(input2Len));
	SerialUSB.println("decodedLen = " + String(decodedLen));

	base64_decode(decoded, input_in, input2Len);
	
	SerialUSB.println(input_in);
	SerialUSB.println(decoded);

	return	decoded;
}

// ---------------------------------------------------------------
void loop()
{
	SerialUSB.println("*** loop ***");
	delay (3000); 
}

// ---------------------------------------------------------------
