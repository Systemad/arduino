#include "functions.h" // Includes all functions
#include "pins.h" // Pin Declarations
#include "common.h"

int keyOneCounter = 0;
int keyTwoCounter = 0;
int redValue = 254;
int greenValue = 1;
int blueValue = 255;

int rDirection = -1;
int gDirection = 1;
int bDirection = -1;

unsigned long fadeMillis;

void setup() {
  Serial.begin(9600);
  initialize();
  delay(300);
  welcomeMessage();
}

void loop() {
  
  // Buttons Key1 and Key2
  int keyOne = digitalRead(key1);
  int keyTwo = digitalRead(key2);
 

  if (keyOne == HIGH){
    keyOneCounter++;
    delay(300);
  }
  if (keyTwo == HIGH){
    keyTwoCounter++;
    delay(300);
  }

  logic();
  input_handler(keyOneCounter, keyTwoCounter);
  serial_receiver();
  
}


void serial_receiver() {
  while (Serial.available()){
    int serialMode = Serial.read();
    serial_handler(serialMode);
  }
}


void logic(){

  if(keyOneCounter == 4){
    keyOneCounter = 0;
  }

  if(keyTwoCounter == 3){
    keyTwoCounter = 0;
  }
  
  if (keyOneCounter == 1,2,3 && keyTwoCounter != 0) keyOneCounter=0;

  
  if (keyTwoCounter == 1,2 && keyOneCounter != 0) keyTwoCounter=0;
}
