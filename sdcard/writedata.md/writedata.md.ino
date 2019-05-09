/*
  SD Card: Write Sensor data
*/
//--------------------------------------------------------------------------------
#include <SPI.h>
#include <SD.h>
//--------------------------------------------------------------------------------
File myFile;
//--------------------------------------------------------------------------------
void setup()
{
  //------------------------------------------------------------------------------
  Serial.begin(9600);
  while (!Serial) {} // program won't continue until you open Serial Monitor (macOS ⇧⌘M / Windows CTRL⇧M)
  //------------------------------------------------------------------------------
  setupSdCardShield()
  //------------------------------------------------------------------------------
  myFile = SD.open("data.csv", FILE_WRITE); // you will have to close this one before opening another.

  if (!myFile) // check file opens
  {
    Serial.println("error opening test.txt");
    while (1);
  }
}
//--------------------------------------------------------------------------------
void loop()
{
  int sensorData = analogRead(A0);
  myFile.println(sensorData);
  delay(100);
}
//--------------------------------------------------------------------------------
