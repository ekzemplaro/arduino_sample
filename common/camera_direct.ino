// ---------------------------------------------------------------
/*
	camera_dicrect.ino

				Aug/16/2021 AM 08:00
*/
// ---------------------------------------------------------------
// [4]:
void camera_direct_proc()
{
	char data_encoded[10000 + DATA_SIZE];
	char data_jpg[10000 + DATA_SIZE];

	SerialUSB.println("*** camera_direct_proc *** start ***");

	int length_jpg = image_retrieve_proc(data_jpg);
	SerialUSB.println("length_jpg =  " + String(length_jpg));

//	int encodedLen = Base64.encodedLength(length_jpg);
	int encodedLen = base64_enc_len(length_jpg);
	SerialUSB.println("encodedLen =  " + String(encodedLen));

	SerialUSB.println("*** before base64_encode ***");
//	Base64.encode(data_encoded,data_jpg,encodedLen);
	base64_encode(data_encoded,data_jpg,encodedLen);
	SerialUSB.println("*** after base64_encode ***");

	Wio.LedSetRGB(1, 1, 0);

	image_upload_proc(data_encoded);

	Wio.LedSetRGB(1, 1, 1);
}

// ---------------------------------------------------------------
// [4-4]:
int image_retrieve_proc(char data_jpg[])
{
	SerialUSB.println("*** image_retrieve_proc ***");

	take_picture_proc();

	// Get the size of the image (frame) taken	
	uint16_t jpglen = cam.frameLength();
	SerialUSB.println("*** jpglen = " + String(jpglen));
	int rvalue = jpglen;
	SerialUSB.print("Storing ");
	SerialUSB.print(jpglen, DEC);
	SerialUSB.print(" byte image.");

	int ipos = 0;
	while (jpglen > 0) {
		// read 64 bytes at a time;
		uint8_t *buffer;
		uint8_t bytesToRead = min((uint16_t)64, jpglen); // change 32 to 64 for a speedup but may not work with all setups!

		buffer = cam.readPicture(bytesToRead);

//		strncpy(&data_jpg[ipos],(const char *)buffer,bytesToRead);

		for (int it=0; it<bytesToRead; it++)
			{
			data_jpg[ipos+it] = buffer[it];
			}

		ipos += bytesToRead;
		jpglen -= bytesToRead;
	}

	data_jpg[ipos] = '\0';
	SerialUSB.println("*** ipos = " + String(ipos));

	delay(500);

	SerialUSB.println("*** image_retrieve_proc *** end ***");

	return rvalue;
}

// ---------------------------------------------------------------
// [4-4-2]:
void take_picture_proc()
{
	// Try to locate the camera
	if (cam.begin()) {
		SerialUSB.println("*** Camera Found. ***");
	} else {
		SerialUSB.println("No camera found?");
		return;
	}

	get_camera_version_proc();

	// Set the picture size - you can choose one of 640x480, 320x240 or 160x120 
	// Remember that bigger pictures take longer to transmit!
	
//	cam.setImageSize(VC0706_640x480);	// biggest
//	cam.setImageSize(VC0706_320x240);	// medium
	cam.setImageSize(VC0706_160x120);	// small

	Wio.PowerSupplyGrove(false);

	delay(500);
	
	Wio.PowerSupplyGrove(true);
	
	// You can read the size back from the camera (optional, but maybe useful?)
	uint8_t imgsize = cam.getImageSize();
	SerialUSB.print("Image size: ");
	if (imgsize == VC0706_640x480) SerialUSB.println("640x480");
	if (imgsize == VC0706_320x240) SerialUSB.println("320x240");
	if (imgsize == VC0706_160x120) SerialUSB.println("160x120");

	SerialUSB.println("Snap in 0.2 secs...");
	delay(200);

	if (! cam.takePicture()) 
		SerialUSB.println("*** Failed to snap! ***");
	else 
		SerialUSB.println("*** Picture taken! ***");
		uint16_t jpglen = cam.frameLength();
		SerialUSB.print("cam.frameLength: ");
		SerialUSB.print(jpglen, DEC);
		SerialUSB.println(" byte image.");
}

// ---------------------------------------------------------------
// [4-4-2-4]:
void get_camera_version_proc()
{
	char *reply = cam.getVersion();
	if (reply == 0)
		{
		SerialUSB.println("*** Failed to get version ***");
		}
	else
		{
		SerialUSB.println("-----------------");
		SerialUSB.print(reply);
		SerialUSB.println("-----------------");
		}
}

// ---------------------------------------------------------------
// [6-4]:
void image_upload_proc(char data_in[])
{
	SerialUSB.println("*** image_upload_proc *** start ***");

	DynamicJsonDocument doc_camera(10512);

	char str_json[8192];
	int status;

	doc_camera["base64"] = String(data_in);
	doc_camera["aa"] = "Hello";
	doc_camera["version"] = "Aug/16/2021 AM 07:40";
	doc_camera["device"] = device;
	doc_camera["sizeofdata"] = strlen(data_in);

	serializeJson(doc_camera, str_json);

	SerialUSB.print(str_json);
	delay(200);
	SerialUSB.println("");

	delay(200);

	if (!Wio.HttpPost(URL, str_json, &status))
		{
		SerialUSB.println("### ERROR! HttpPost ###");
		}
	else
		{
		SerialUSB.print("Status: ");
		SerialUSB.println(status);
		}

	SerialUSB.println("*** image_upload_proc *** dddd ***");

	delay(500);

	SerialUSB.println("*** image_upload_proc *** end ***");
}

// ---------------------------------------------------------------
