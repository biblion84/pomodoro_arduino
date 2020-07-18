# pomodoro_arduino
A pomodoro timer with an Arduino and some segment display

# What it is

It's a pomodoro timer with basic functionnalities : 
  * It counts down from 25 minutes and switch to a 5 minutes pause
  * It has a button that can pause current timer or skip session, to go into pause or work mode quickly
  * You'll know when to stop working its led indicates it

# Components

  * Arduino UNO
  * Four digit 7 segment display 3461AS
  * A button
  * 7 47 Ohms resistors
   * Some jumper cables

# Instructions

1. Connect the arduino UNO pins 1 to 12 to the 3461AS pins 1 to 12
2. Skip pin 3 and connect the button to pin 3, connect the other button leg to ground
3. Connect a led to pin 13 and ground
4. Build and load the given .ino file
5. That's all folks !


![The pomodoro timer](/img/device.jpg)

