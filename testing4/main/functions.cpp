#include "common.h"
#include "functions.h"
#include "pins.h"

int fadeAmount = 1;
int brightness = 0;

int inputVal;
int mappedValue;

void fade(int brightness){
    analogWrite(redPin, brightness);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
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

    switch(keyOneCounter){
      case 1:
        RGB_color(255, 0, 0);
        break;
      case 2:
        RGB_color(0, 255, 0);
        break;
      case 3:
        RGB_color(0, 0, 255);
        break;
      case 4:
        RGB_color(0, 0, 0);
        keyOneCounter = 0;
        break;
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

void input_handler(int keyOneCounter, int keyTwoCounter){
  inputVal = analogRead(analogReg); // Potentiometer
  mappedValue = map(inputVal, 0, 1023, 0, 100); // Map it from 0-100

  if (keyOneCounter == 0 && keyTwoCounter == 0){ 
      RGB_color(0, 0, 0); 
    } else {
      toggleLedColor(keyOneCounter);
    }

  switch(keyTwoCounter){
    case 0:
      RGB_color(0, 0, 0);
      break;
      
    case 1:
      fade(mappedValue);
      break;
      
    case 2:
      if (millis() > fadeMillis){
        rainbow(mappedValue);
       }
       break;
   
    case 3:
      RGB_color(0, 0, 0);
      keyTwoCounter = 0;
      break;
  }
}

void serial_handler(int mode){

  switch (mode)
  {
    case '1':
      Serial.println("Selected Toggle color mode. Enter 1 again to change color\n");
      keyTwoCounter = 0;
      keyOneCounter++;
      break;
    case '2':
      Serial.println("Selected fade mode. Enter 3 for rainbow mode\n");
      keyTwoCounter = 1;
      break;
    case '3':
      Serial.println("Selected Rainbow mode, Enter 4 to turn off\n");
       keyTwoCounter = 2;
      break;
    case '4':
      Serial.println("All modes has been turned off\n");
      keyTwoCounter = 0;
      keyOneCounter = 0;
      break;  
  }
}

void welcomeMessage(){
  Serial.println("Buttons:");
  Serial.println("Button 1: Toggle LED colors \nButton 2: Toggle between fade and rainbow mode\n");
  Serial.println("Serial console:\nEnter 1 to Toggle LED Colors\nEnter 2 Toggle between rainbow and fade\n");
}
