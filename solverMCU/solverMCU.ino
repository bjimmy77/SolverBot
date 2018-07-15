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
#include <SPI.h> //needs SPI.h for SPI
#include "Ucglib.h"
  //I2C PWM library for Servo Controll
#include <Wire.h> //needs Wire.h for I2C
#include <Adafruit_PWMServoDriver.h>

//Call libraries
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
Ucglib_SSD1331_18x96x64_UNIVISION_HWSPI ucg(/*cd=*/ 9, /*cs=*/ 4, /*reset=*/ 8);

//Definitions
#include "defines.h"

//Variables
//Encoder
volatile int rotaryNumber = 0;              // Encoder value, print it when it changes value,
                                            // used in loop and both interrupt routines
volatile boolean halfleft = false;          // Used in both interrupt routines
volatile boolean halfright = false;         // Used in both interrupt routines

int Button = 3;            // Rotary Encoder shaft switch
int oldnumber = rotaryNumber;

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
  //Encoder
  pinMode(Button, INPUT);          // with external pull-up and cap
  attachInterrupt(CN_4, isr_A, FALLING);      // Call isr_2 when digital A0 goes LOW
  attachInterrupt(CN_6, isr_B, FALLING);      // Call isr_3 when digital A1 goes LOW

}

void loop() {
  if(rotaryNumber != oldnumber){                  // Change in value ?
    Serial.println(rotaryNumber);                 // Yes, print it (or whatever)
    oldnumber = rotaryNumber;
  }
  if(digitalRead(Button) == LOW && rotaryNumber != 0) {        // Only process 1st reset push
    rotaryNumber = 0;
    oldnumber = 0;
    Serial.println("Reset...");
  }  
}

//Encoder ISRs
void isr_A(){                                           // A went LOW
  delay(3);                                             // Debounce time
                                                        // Trade off bounce vs missed counts
  int bits = PORTB;                                     // Atomic read of encoder inputs
  int LSB = (bits >> 2) & 0x01;
  int MSB = (bits >> 4) & 0x01;
  
  if(LSB == LOW){                                 // A still LOW ?
    if(MSB == HIGH && halfright == false){        // -->
      halfright = true;                                 // One half click clockwise
    } 
    if(MSB == LOW && halfleft == true){           // <--
      halfleft = false;                                 // One whole click counter-
      rotaryNumber--;                                         // clockwise
    }
  }
}
void isr_B(){                                           // B went LOW
  delay(3);                                             // Debounce time
                                                        // Trade off bounce vs missed counts
  int bits = PORTB;                                     // Atomic read of encoder inputs
  int LSB = (bits >> 2) & 0x01;
  int MSB = (bits >> 4) & 0x01;
  
  if(MSB == LOW){                                 // A still LOW ?
    if(LSB == HIGH && halfleft == false){         // <--
      halfleft = true;                                  // One half  click counter-
    }                                                   // clockwise
    if(LSB == LOW && halfright == true){          // -->
      halfright = false;                                // One whole click clockwise
      rotaryNumber++;
    }
  }
}
