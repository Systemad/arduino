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

// Debouncer variables for keyOne and keyTwo
int buttonOneState;             // current reading from keyOne
int lastButtonOneState = LOW;   // previous reading input keyOne

int buttonTwoState;             // current reading from keyTwo
int lastButtonTwoState = LOW;   // previous reading from keyTwo

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

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

  // Debouncers for keyOne and keyTwo
  if (keyOne != lastButtonOneState) {
    lastDebounceTime = millis();
  }

  //debouncer(keyOne);
  
  if (keyTwo != lastButtonTwoState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (keyOne != buttonOneState) {
      buttonOneState = keyOne;
      if (buttonOneState == HIGH) {
        keyOneCounter++;
      }
    }
  }
  lastButtonOneState = keyOne;
  

  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (keyTwo != buttonTwoState) {
      buttonTwoState = keyTwo;
      if (buttonTwoState == HIGH) {
        keyTwoCounter++;
      }
    }
  }
  lastButtonTwoState = keyTwo;
  
  
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

/*
 * Handles logic for keycounters
 */
 
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
