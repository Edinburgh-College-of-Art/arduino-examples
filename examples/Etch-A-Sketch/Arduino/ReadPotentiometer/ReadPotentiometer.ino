//==============================================================================
// Read a pot and spit the numbers back out over Serial
//==============================================================================
// Forward Declerations
void writeRawSerial(uint16_t value);
//==============================================================================
void setup()
{
  Serial.begin(19200);
}
//==============================================================================
void loop()
{
  //----------------------------------------------------------------------------
  // read and average data from sensor
  const uint16_t average = 20;
  uint16_t sensorValue[2] = {0};
  for(uint16_t i = 0; i < average; ++i)
  {
    sensorValue[0] += analogRead(A0);
    sensorValue[1] += analogRead(A1);
  }
  sensorValue[0] /= average;
  sensorValue[1] /= average;
  //----------------------------------------------------------------------------
  writeRawSerial(sensorValue[0]); // write first byte
  writeRawSerial(sensorValue[1]); // write second byte
  //----------------------------------------------------------------------------
  delay(50);
}
//==============================================================================
/** writes 2 bytes of data over Serial as 2 individual 8-bit numbers*/
void writeRawSerial(uint16_t value)
{
  uint8_t byteOut[2];
  byteOut[0] = (value & 0xff);
  byteOut[1] = (value >> 8);
  Serial.write(byteOut[0]);
  Serial.write(byteOut[1]);
}
