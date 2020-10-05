#include "common.h"
#include "functions.h"
#include "pins.h"

//char in_char; // Serial mode

/*
int redValue = 254;
int greenValue = 1;
int blueValue = 255;

int rDirection = -1;
int gDirection = 1;
int bDirection = -1;
*/

unsigned long fadeMillis;
int fadeAmount = 1;
int brightness = 0;

int inputVal;
int mappedValue;


void fade(int brightness, int fadeAmount){
    analogWrite(redPin, brightness);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
    brightness += fadeAmount;

    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = fadeAmount;
    }
}

void rainbow(int mappedValue){
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

void toggleLedColor(int keyOneCounter){    
  if (keyOneCounter == 1){
    //Serial.println("Red.");
    RGB_color(255, 0, 0);
  } else if (keyOneCounter == 2){
    //Serial.println("Green.");
    RGB_color(0, 255, 0);
  } else if (keyOneCounter == 3){
    //Serial.println("Blue.");
    RGB_color(0, 0, 255);
  } else if (keyOneCounter == 4){
    //Serial.println("Counter reset");
    keyOneCounter = 0;
  }
}


void initialize(){
  pinMode(analogReg, INPUT);
  pinMode(key1, INPUT);
  pinMode(key2, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}


void RGB_color(int redValue, int greenValue, int blueValue)
{
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

/**
void serialRemote(int keyOneCounter, int keyTwoCounter, int mappedValue) {
  while (Serial.available()){
    in_char = Serial.read();
    //Serial.println(in_char);
    select(keyOneCounter, keyTwoCounter, mappedValue);
  }
}
*/

void select(int serialMode, int keyOneCounter, int keyTwoCounter){

  switch (serialMode)
  {
    case '1':
      Serial.println("Selected fade mode");
      fade(mappedValue, brightness);
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

void input_handler(int keyOneCounter, int keyTwoCounter){


  inputVal = analogRead(analogReg); // Potentiometer
  mappedValue = map(inputVal, 0, 1023, 0, 100); // Map it from 0-100
  
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
    if (millis() > fadeMillis){
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
