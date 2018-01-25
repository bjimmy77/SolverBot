# SolverBot
## Overview
This is software for my home built Rubiks cube solving robot. Still under development
## Components
There are currently two planned software pieces that will run on the SolverBot
### Arduino
* This will be a C/C++ based program that will provide the main control for the whole bot. It will have the following features:
1. I2C interface to 16 Channel PWM controller
2. SPI interface to a small OLED display 
3. Color sensor interface to read the cube faces
4. Serial interface for communication with the Pi
### Raspberry Pi
* This will be done in Python and have two main functions:
1. An overall simple program for receiving cube information from the MCU and sending solution information back
2. An instatiation of the Kociemba cube solving library
