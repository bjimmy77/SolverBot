/*************************************************** 
  This is the Arduino/ChipKit code that is used to do
  the state machine and motor control for my home built
  Rubik's Cube Solver

  Credits:
  Rotary Encoder code:
  https://github.com/jmlynesjr/chipKIt-Arduino-Examples/blob/master/RotaryEncoderISR4.pde
  
 ****************************************************/

//Libraries
  //Rotary Encoder
  //https://github.com/MajenkoLibraries/ChangeNotification
#include <ChangeNotification.h> 
  //Graphics Library for small .96" OLED
#include <SPI.h>
#include "Ucglib.h"
  //I2C PWM library for Servo Controll
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


//Call libraries
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
Ucglib_SSD1331_18x96x64_UNIVISION_HWSPI ucg(/*cd=*/ 9, /*cs=*/ 4, /*reset=*/ 8);

//Definitions
#include defines.h


void setup(void) {
  delay(300);
  //Serial
  Serial.begin(9600);
  //Graphics
  ucg.begin(UCG_FONT_MODE_TRANSPARENT);
  ucg.clearScreen();
  ucg.setFont(ucg_font_ncenR10_tr);
  ucg.setPrintPos(0,25);
  ucg.setColor(255, 255, 255);
  //Servo  
  pwm.begin();
  pwm.setPWMFreq(60);
  //Set all Servos to a safe value
  pwm.setPWM(NORTHGRIP, 0, 250);
  pwm.setPWM(NORTHEXT, 0, 250);
  pwm.setPWM(SOUTHGRIP, 0, 250);
  pwm.setPWM(SOUTHEXT, 0, 250);
  pwm.setPWM(EASTGRIP, 0, 250);
  pwm.setPWM(EASTEXT, 0, 250);
  pwm.setPWM(WESTGRIP, 0, 250);
  pwm.setPWM(WESTEXT, 0, 250);
  pwm.setPWM(SCANEXT, 0, 250);
  pwm.setPWM(SCANLEFT, 0, 250);
  pwm.setPWM(SCANRIGHT, 0, 250);
}

void loop() {
  
}

