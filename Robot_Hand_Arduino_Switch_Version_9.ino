// Robot Hand Arduino Switch Version 9
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2,3);
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define MIN_PULSE_WIDTH       650
#define MAX_PULSE_WIDTH       2350
#define DEFAULT_PULSE_WIDTH   1500
#define FREQUENCY             50
uint8_t servonum = 0;
void setup() {
  Serial.begin(9600);
  Serial.println("pick a lowercase letter or a number 0 to 9");
  
  BTSerial.begin(38400);

  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);  // Analog servos run at ~60 Hz updates
}
 
void loop()  {           
if(BTSerial.available() >= 0){
 String inByte = BTSerial.readString();
 Serial.println(inByte);
for(int i=0;i<inByte.length();i++){
 

switch (inByte[i]) {
    
  case '-': //neutral hand position
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    break;

// Letters

  case 'a' : //c
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(180));
    pwm.setPWM(2, 0, pulseWidth(180));
    pwm.setPWM(3, 0, pulseWidth(180));
    pwm.setPWM(4, 0, pulseWidth(180));
      delay(1000);
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));  
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    break;

  case 'b' : //c
    pwm.setPWM(0, 0, pulseWidth(180));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
      delay(1000);
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));  
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    break;

  case 'c' : //c // looks weird
    pwm.setPWM(0, 0, pulseWidth(120));
    pwm.setPWM(1, 0, pulseWidth(140));
    pwm.setPWM(2, 0, pulseWidth(130));
    pwm.setPWM(3, 0, pulseWidth(95));
    pwm.setPWM(4, 0, pulseWidth(165));
      delay(1000);
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));  
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    break;

  case 'd' : //c
    pwm.setPWM(0, 0, pulseWidth(145));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(145));
    pwm.setPWM(3, 0, pulseWidth(145));
    pwm.setPWM(4, 0, pulseWidth(165));
      delay(1000);
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));  
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    break;

  case 'e' : //c
    pwm.setPWM(0, 0, pulseWidth(180));
    pwm.setPWM(1, 0, pulseWidth(180));
    pwm.setPWM(2, 0, pulseWidth(180));
    pwm.setPWM(3, 0, pulseWidth(180));
    pwm.setPWM(4, 0, pulseWidth(180));
      delay(1000);
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));  
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    break;

  case 'f' : //c
    pwm.setPWM(0, 0, pulseWidth(180));
    pwm.setPWM(1, 0, pulseWidth(180));
    pwm.setPWM(2, 0, pulseWidth(0));
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
      delay(1000);
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));  
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    break;
    
//  case 'g' : // wrist motion
//    pwm.setPWM(0, 0, pulseWidth(90));
//    pwm.setPWM(1, 0, pulseWidth(90));
//    pwm.setPWM(2, 0, pulseWidth(180));
//    pwm.setPWM(3, 0, pulseWidth(180));
//    pwm.setPWM(4, 0, pulseWidth(180));
//    break;
 
//  case 'h' : //wrist motion and fingers crossed
//    pwm.setPWM(0, 0, 1056);
//    pwm.setPWM(1, 0, 1000);
//    pwm.setPWM(2, 0, 2000);
//    pwm.setPWM(3, 0, 2000);
//    pwm.setPWM(4, 0, 2000);
//    break;

  case 'i' : //c
    pwm.setPWM(0, 0, pulseWidth(180));
    pwm.setPWM(1, 0, pulseWidth(180));
    pwm.setPWM(2, 0, pulseWidth(180));
    pwm.setPWM(3, 0, pulseWidth(180));
    pwm.setPWM(4, 0, pulseWidth(0));
      delay(1000);
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));  
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    break;

//  case 'j' : // Wrist motion
//    servoth.write();
//    servoin.write();
//    servomid.write();
//    servoring.write();
//    servopinky.write();
//    break;

  case 'k' : //c
    pwm.setPWM(0, 0, pulseWidth(90));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));
    pwm.setPWM(3, 0, pulseWidth(180));
    pwm.setPWM(4, 0, pulseWidth(180));
      delay(1000);
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));  
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    break;

  case 'l' : //c      
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(180));
    pwm.setPWM(3, 0, pulseWidth(180));
    pwm.setPWM(4, 0, pulseWidth(180));
      delay(1000);
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));  
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    break;

  case 'm' : //c
    pwm.setPWM(0, 0, pulseWidth(180));
       delay(500);
    pwm.setPWM(1, 0, pulseWidth(160));
    pwm.setPWM(2, 0, pulseWidth(160));
    pwm.setPWM(3, 0, pulseWidth(160));
    pwm.setPWM(4, 0, pulseWidth(180));
      delay(1000);
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));  
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    break;

  case 'n' : //c
    pwm.setPWM(0, 0, pulseWidth(180));
      delay(500);
    pwm.setPWM(1, 0, pulseWidth(160));
    pwm.setPWM(2, 0, pulseWidth(160));
    pwm.setPWM(3, 0, pulseWidth(160));
    pwm.setPWM(4, 0, pulseWidth(160));
      delay(1000);
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));  
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    break;

  case 'o' : //c
    pwm.setPWM(0, 0, pulseWidth(180));
    pwm.setPWM(1, 0, pulseWidth(180));
    pwm.setPWM(2, 0, pulseWidth(180));
    pwm.setPWM(3, 0, pulseWidth(180));
    pwm.setPWM(4, 0, pulseWidth(180));
      delay(1000);
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));  
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    break;

//  case 'p' :
//    pwm.setPWM(0, 0, pulseWidth(75));
//    pwm.setPWM(1, 0, pulseWidth(75));
//    pwm.setPWM(2, 0, pulseWidth(90));
//    pwm.setPWM(3, 0, pulseWidth(180));
//    pwm.setPWM(4, 0, pulseWidth(180));
//    break;

//  case 'q' : //Wrist Motion
//    pwm.setPWM(0, 0, 1083);
//    pwm.setPWM(1, 0, 1528);
//    pwm.setPWM(2, 0, 2167);
//    pwm.setPWM(3, 0, 2167);
//    pwm.setPWM(4, 0, 2167);
//    break;

//  case 'r' : // Fingers Crossed
//    servoth.write();
//    servoin.write();
//    servomid.write();
//    servoring.write();
//    servopinky.write();
//    break;

  case 's' : //c
    pwm.setPWM(1, 0, pulseWidth(180));
    pwm.setPWM(2, 0, pulseWidth(180));
    pwm.setPWM(3, 0, pulseWidth(180));
    pwm.setPWM(4, 0, pulseWidth(180));
      delay(500);
    pwm.setPWM(0, 0, pulseWidth(180));
      delay(1000);
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));  
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    break;

  case 't' : //c
    pwm.setPWM(0, 0, pulseWidth(140));
      delay(500);
    pwm.setPWM(1, 0, pulseWidth(160));
    pwm.setPWM(2, 0, pulseWidth(180));
    pwm.setPWM(3, 0, pulseWidth(180));
    pwm.setPWM(4, 0, pulseWidth(180));
      delay(1000);
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));  
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    break;

 case 'u' :                  
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));
    pwm.setPWM(3, 0, pulseWidth(180));
    pwm.setPWM(4, 0, pulseWidth(180));
      delay(500);
    pwm.setPWM(0, 0, pulseWidth(120));
      delay(1000);
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));  
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    break;

  case 'v' : //c
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));
    pwm.setPWM(3, 0, pulseWidth(180));
    pwm.setPWM(4, 0, pulseWidth(180));
      delay(500);
    pwm.setPWM(0, 0, pulseWidth(120));
      delay(1000);
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));  
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    break;

  case 'w' : //c
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(180));
      delay(500);
    pwm.setPWM(0, 0, pulseWidth(120));
      delay(1000);
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));  
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    break;

  case 'x' : //c
    pwm.setPWM(0, 0, pulseWidth(180));
    pwm.setPWM(1, 0, pulseWidth(90));
      delay(500);
    pwm.setPWM(2, 0, pulseWidth(160));
    pwm.setPWM(3, 0, pulseWidth(160));
    pwm.setPWM(4, 0, pulseWidth(160));
      delay(1000);
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));  
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    break;

  case 'y' : //c
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(180));
    pwm.setPWM(2, 0, pulseWidth(180));
    pwm.setPWM(3, 0, pulseWidth(180));
    pwm.setPWM(4, 0, pulseWidth(0));
      delay(1000);
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));  
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    break;

//  case 'z' // Wrist Motion
//    servoth.write();
//    servoin.write();
//    servomid.write();
//    servoring.write();
//    servopinky.write();
//    break;

// Numbers
  
  case '0' : //c
    pwm.setPWM(0, 0, pulseWidth(180));
    pwm.setPWM(1, 0, pulseWidth(180));
    pwm.setPWM(2, 0, pulseWidth(180));
    pwm.setPWM(3, 0, pulseWidth(180));
    pwm.setPWM(4, 0, pulseWidth(180));
      delay(1000);
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));  
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    break;

  case '1' : //c
    pwm.setPWM(0, 0, pulseWidth(180));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(180));
    pwm.setPWM(3, 0, pulseWidth(180));
    pwm.setPWM(4, 0, pulseWidth(180));
      delay(1000);
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));  
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    break;

  case '2' : //c
    pwm.setPWM(0, 0, pulseWidth(180));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));
    pwm.setPWM(3, 0, pulseWidth(180));
    pwm.setPWM(4, 0, pulseWidth(180));
      delay(1000);
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));  
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    break;

  case '3' : //c
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));
    pwm.setPWM(3, 0, pulseWidth(180));
    pwm.setPWM(4, 0, pulseWidth(180));
      delay(1000);
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));  
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    break;

  case '4' : //c
    pwm.setPWM(0, 0, pulseWidth(180));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
      delay(1000);
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));  
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    break;

  case '5' : //c
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
      delay(1000);
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));  
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    break;

  case '6' : //c
    pwm.setPWM(0, 0, pulseWidth(180));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));
    pwm.setPWM(3, 0, pulseWidth(60));
    pwm.setPWM(4, 0, pulseWidth(180));
      delay(1000);
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));  
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));;
    break;
   
  case '7' : //c
    pwm.setPWM(0, 0, pulseWidth(180));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));
    pwm.setPWM(3, 0, pulseWidth(180));
    pwm.setPWM(4, 0, pulseWidth(0));
      delay(1000);
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));  
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    break;

  case '8' : //c
    pwm.setPWM(0, 0, pulseWidth(180));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(180));
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
      delay(1000);
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));  
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    break;
    

  case '9' : //c
    pwm.setPWM(0, 0, pulseWidth(180));
    pwm.setPWM(1, 0, pulseWidth(180));
    pwm.setPWM(2, 0, pulseWidth(0));
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
      delay(1000);
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));  
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    break;
    }
}
}}

int pulseWidth(int angle)
{
  int pulse_wide, analog_value;
  pulse_wide   = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  Serial.println(analog_value);
  return analog_value;
}
