//============================================================
// Etch-a-Sketch with Arduino
//============================================================
// Libraries
//============================================================
import processing.serial.*;
//============================================================
int lastValueX, lastValueY;
Serial serialDevice;
int serialValueX = width;
int serialValueY = height;
//============================================================
void setup() 
{
  //----------------------------------------------------------
  //size(640, 480);
  fullScreen();
  //----------------------------------------------------------
  serialDevice = new Serial(this, Serial.list()[1], 19200);
  //----------------------------------------------------------
  lastValueY = lastValueX = height/2; // set starting point
  //----------------------------------------------------------
  stroke(255, 0, 0);
  strokeWeight(2);
  background(50);
}
//============================================================
void draw() 
{
  //----------------------------------------------------------
  // Get the whole screen except for the leftmost pixel
  int currentX = int(map(serialValueX,0,1023,0,width));
  int currentY = int(map(serialValueY,0,1023,0,height));
  PImage img = get(0, 0, width, height);
  background(50);
  image(img, 0, 0); 
  line(lastValueX, lastValueY, currentX, currentY);
  //----------------------------------------------------------
  lastValueX = currentX;
  lastValueY = currentY;
  setXYValues();
  //----------------------------------------------------------
}
//============================================================
// returns value from incoming serial bytes or -1 if not available
int readSerialBytes(int numberOfBytes)
{
  int valueFromBytes = -1;
  if (serialDevice.available() != 0) 
  {   
    valueFromBytes = 0;
    for (int i = 0; i < numberOfBytes; ++i)
    {      
      int inByte = (serialDevice.read() & 0xff); // masking with 0xff should limit incoming values to range 0 - 255
      valueFromBytes |= (inByte << (i*8));
    } 
  }
  return valueFromBytes;
}
//============================================================
// attempt to get a new value for a given coordinate from seriual input
// give the maximum value for the required dimension to scale the value
int setNewCoordValue(int currentCoordValue)
{
  int serialValue = readSerialBytes(2);
  if (serialValue == -1 || serialValue > 1024 || (abs(serialValue - currentCoordValue) > 150)) // filter values
  {   
    return currentCoordValue;
  }
  else
  { 
    return serialValue;
  }
}

//============================================================
// Set the X and Y value from incoming serial data
void setXYValues()
{
  serialValueX = setNewCoordValue(serialValueX);
  serialValueY = setNewCoordValue(serialValueY);
}

void mouseClicked() 
{
  background(50);
}
