#include "functions.h" // functions handler
#include "pins.h" // pin declarations

int keyOneCounter = 0;
int keyTwoCounter = 0;
int redValue = 254;
int greenValue = 1;
int blueValue = 255;
int mappedValue;

int rDirection = -1, gDirection = 1, bDirection = -1;
int delayTime = 500;
int fadeAmount = 1;
int brightness = 0;

char in_char;

unsigned long fadeMillis;

void setup() {
  Serial.begin(9600);
  initialize();
  Serial.println("hello");
}

void loop() {
  int inputVal = analogRead(analogReg); // Potentiometer
  mappedValue = map(inputVal, 0, 1023, 0, 100); // Map it from 0-100
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
      rainbow(); 
    }
  }
  if(keyTwoCounter == 3){
    keyTwoCounter = 0;
  }
  if (keyOneCounter == 1,2,3 && keyTwoCounter != 0) keyOneCounter=0;
  if (keyTwoCounter == 1,2 && keyOneCounter != 0) keyTwoCounter=0;

  //serialRemote(keyOneCounter, keyTwoCounter, brightness, fadeMillis, mappedValue);
  serialRemote();
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
    fadeMillis = millis() + 30;
}


void select(){

  switch (in_char)
  {
    case '1':
      Serial.println("Selected fade mode");
      //fade(mappedValue, brightness);
      keyTwoCounter = 1;
      break;
    case '2':
      Serial.println("Selected Rainbow mode");
       if (millis() > fadeMillis){
        keyTwoCounter = 2;
        //rainbow();
      }
      break;
    case '3':
      Serial.println("LED Toggle mode on, enter 3 again to change color");
        toggleLedColor(keyOneCounter);
      break;  
  case '4':
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