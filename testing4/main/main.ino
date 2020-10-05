#include "functions.h" // functions handler
#include "pins.h" // pin declarations
#include "common.h"

int keyOneCounter = 0;
int keyTwoCounter = 0;
//char in_char;
int serialMode;

int redValue = 254;
int greenValue = 1;
int blueValue = 255;

int rDirection = -1;
int gDirection = 1;
int bDirection = -1;

//char in_char;

void setup() {
  Serial.begin(9600);
  initialize();
  Serial.println("hello");
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
  
  //serialRemote(keyOneCounter, keyTwoCounter, brightness, fadeMillis, mappedValue);
  input_handler(keyOneCounter, keyTwoCounter);
  //serialRemote(keyOneCounter, keyTwoCounter, mappedValue);
  serialRemote();
  //logicCheck();
}

void serialRemote() {
  while (Serial.available()){
    serialMode = Serial.read();
    //Serial.println(in_char);
    select(serialMode, keyOneCounter, keyTwoCounter);
  }
}

/*
void input_handler(){
  if (keyOneCounter == 0 && keyTwoCounter == 0){ 
      RGB_color(0, 0, 0); 
    } else {
      toggleLedColor(keyOneCounter);
    }

  if (keyTwoCounter == 0){
      RGB_color(0, 0, 0);
  } else if (keyTwoCounter == 1){
    fade(mappedValue, brightness);
  } else if (keyTwoCounter == 2){
    if (millis() > 50){
      //rainbow(); 
      rainbow(mappedValue);
    }
  }
  if(keyTwoCounter == 3){
    keyTwoCounter = 0;
  }
  if (keyOneCounter == 1,2,3 && keyTwoCounter != 0) keyOneCounter=0;
  if (keyTwoCounter == 1,2 && keyOneCounter != 0) keyTwoCounter=0;
  
}

//void rainbow(int rDirection, int gDirection, int bDirection, int redValue, int greenValue, int blueValue){

void rainbow(){
    analogWrite(redPin, redValue);
    analogWrite(greenPin, greenValue);
    analogWrite(bluePin, blueValue);
    
    redValue = redValue + rDirection;  
    greenValue = greenValue + gDirection;
    blueValue = blueValue + bDirection;
    
    if (redValue >= 255 || redValue <= 0){
        rDirection = rDirection * -1;
      }
    if (greenValue >= 255 || greenValue <= 0){
          gDirection = gDirection * -1;
    }
    if (blueValue >= 255 || blueValue <= 0){
        bDirection = bDirection * -1;
    }
    fadeMillis = millis() + mappedValue;
}
*/

/*
void select(){

  switch (in_char)
  {
    case '1':
      Serial.println("Selected fade mode");
      keyTwoCounter = 1;
      break;
    case '2':
      Serial.println("Selected Rainbow mode");
       if (millis() > fadeMillis){
        keyTwoCounter = 2;
      }
      break;
    case '3':
      Serial.println("Turned off modes");
      keyTwoCounter = 0;
      keyOneCounter = 0;
      break;  
  }
}

void serialRemote() {
  while (Serial.available()){
    in_char = Serial.read();
    //Serial.println(in_char);
    select();
  }
}
*/
