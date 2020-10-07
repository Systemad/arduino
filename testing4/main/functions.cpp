#include "common.h"
#include "functions.h"
#include "pins.h"

int fadeAmount = 1;
int brightness = 0;

int inputVal;
int mappedValue;

//int buttonOneState;             // current reading from keyOne
//int lastButtonOneState = LOW;   // previous reading input keyOne

//unsigned long lastDebounceTime = 0;
//unsigned long debounceDelay = 50;

//int keyOneCounter = 0;
//int keyTwoCounter = 0;

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
      fade(mappedValue, brightness);
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
      Serial.println("Selected fade mode.");
      keyTwoCounter = 1;
      break;
    case '2':
      Serial.println("Selected Rainbow mode");
       keyTwoCounter = 2;
      break;
    case '3':
      Serial.println("Selected Toggle color mode. Use 3 again to change color");
      keyTwoCounter = 0;
      keyOneCounter++;
      break;

    case '4':
      Serial.println("Selected Turned off modes");
      keyTwoCounter = 0; // Resets both counters and modes
      keyOneCounter = 0;
      break;  
  }
}

/*
void debouncer(int key){
  if (key != lastButtonOneState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (key != buttonOneState) {
      buttonOneState = key;
      if (buttonOneState == HIGH) {
        keyOneCounter++;
      }
    }
  }
  lastButtonOneState = key; 
}
*/
void welcomeMessage(){
  Serial.println("Click button 1 to toggle LED colors. Click button 2 to toggle between fade mode and rainbow mode.");  
  Serial.println("You can also serial console to trigger functions.");
  Serial.println("Enter 1 for fade, 2 for rainbow, 3 for toggle color mode and 4 to turn off all.");
}
