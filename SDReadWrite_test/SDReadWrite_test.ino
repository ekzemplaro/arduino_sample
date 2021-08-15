// #if defined ARDUINO_ARCH_STM32F4
// #include <SD.h>                    // https://github.com/Seeed-Studio/SD
// #elif defined ARDUINO_ARCH_STM32
#include <SDforWioLTE.h>           // https://github.com/SeeedJP/SDforWioLTE
// #endif

#define FILE_NAME "test_bb.txt"

void setup()
{
  // delay(200);
    delay(1000);

  SerialUSB.println("");
  SerialUSB.println("*** START *** Aug/09/2021");

  SerialUSB.println("### Initialize SD card.");
  if (!SD.begin()) {
    SerialUSB.println("### ERROR! ###");
    return;
  }

  File myFile;
  
  SerialUSB.println("### Writing to "FILE_NAME".");
  myFile = SD.open(FILE_NAME, FILE_WRITE);
  if (!myFile) {
    SerialUSB.println("### ERROR! SD.open ###");
    return;
  }
  myFile.println("testing 1, 2, 3, 4, 5, 6.");
  myFile.close();

  SerialUSB.println("### Reading from "FILE_NAME".");
  myFile = SD.open(FILE_NAME);
  if (!myFile) {
    SerialUSB.println("### ERROR! SD.open ###");
    return;
  }
  SerialUSB.println(FILE_NAME":");
  while (myFile.available()) {
    SerialUSB.write(myFile.read());
  }
  myFile.close();

  SerialUSB.println("### Setup completed.");
}

void loop()
{
  SerialUSB.println("*** loop *** aaa ***");
  delay(1000);
    SerialUSB.println("*** loop *** bbb ***");
  delay(1000);
}
