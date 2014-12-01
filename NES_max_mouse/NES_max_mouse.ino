/* 
   this example from the NESpad Arduino library
   displays the buttons on the joystick as bits
   on the serial port - rahji@rahji.com
   
   Version: 1.3 (11/12/2010) - got rid of shortcut constructor - seems to be broken
   
*/

#include <NESpad.h>

// put your own strobe/clock/data pin numbers here -- see the pinout in readme.txt
NESpad nintendo = NESpad(16,14,15);
const int xAxis = A0;         // joystick X axis  
const int yAxis = A1;         // joystick Y axis
// parameters for reading the joystick:
int range = 12;               // output range of X or Y movement
int responseDelay = 5;        // response delay of the mouse, in ms
int divisor = 90;
void setup() {
  Serial.begin(57600);  
  Mouse.begin();
}

void loop() {
  byte pad1;
  pad1 = nintendo.buttons();
  int xReading = readAxis(xAxis);
  int yReading = readAxis(yAxis);
  Mouse.move(map(xReading,-350,350,350,-350), yReading, 0);
    if(pad1&0x1) { Mouse.press(MOUSE_RIGHT); }
    if(pad1&0x2) { Mouse.press(MOUSE_LEFT); }
    if(pad1&0x4) { Mouse.press(MOUSE_MIDDLE); }
    if(pad1&0x8) { Mouse.press(MOUSE_MIDDLE); }
    if(!(pad1&0x1)) { Mouse.release(MOUSE_RIGHT); }
    if(!(pad1&0x2)) { Mouse.release(MOUSE_LEFT); }
    if(!(pad1&0x4)) { Mouse.release(MOUSE_MIDDLE); }
    if(!(pad1&0x8)) { Mouse.release(MOUSE_MIDDLE); }
    
    /*
        if(pad1&0x1) { Serial.println("NES A"); }
    if(pad1&0x2) { Serial.println("NES B"); }
    if(pad1&0x4) { Serial.println("NES Select"); }
    if(pad1&0x8) { Serial.println("NES Start"); }*/
    
  //delay(500);
  delay(responseDelay);
}

int readAxis(int thisAxis) { 
  // read the analog input:
  int reading = analogRead(thisAxis);

  // map the reading from the analog input range to the output range:
  reading = map(reading, 200, 900, -350, 350);

  // if the output reading is outside from the
  // rest position threshold,  use it:
  int distance = reading;

  if (abs(distance) < 50) {
    distance = 0;
  } 
if (distance >0)
{
  map(distance, 50,350,0,350);
}
else
{
  map(distance,-350,50,-350,0);
}
  // return the distance for this axis:
  return distance/divisor;
}
