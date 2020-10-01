#include "functions.h"
#include "pins.h"


int keyOneCounter = 0;
int keyTwoCounter = 0;
int rDirection = -1, gDirection = 1, bDirection = -1;
int redValue = 254, greenValue = 1, blueValue = 255;
int delayTime = 500;
int fadeAmount = 1;
int brightness = 0;

unsigned long currentTime;
unsigned long loopTime;


void setup() {
  Serial.begin(115200);
  Serial.println("Started...");
  pinMode(analogReg, INPUT);
  pinMode(key1, INPUT);
  pinMode(key2, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  currentTime = millis();
  loopTime = currentTime;
}

void loop() {
  
  int inputVal = analogRead(analogReg);
  int mappedValue = map(inputVal, 0, 1023, 0, 100);
  int buttonState = digitalRead(key1);
  int buttonTwoState = digitalRead(key2);
  currentTime = millis();
  fadeAmount = mappedValue;
  
  if (buttonState == HIGH){
    keyOneCounter++;
    Serial.println("key 1 pressed");
    delay(300);
  }

  if (buttonTwoState == HIGH){
    keyTwoCounter++;
    Serial.println("key 2 pressed");
    delay(300);
  }
  
  if (keyOneCounter == 0 && keyTwoCounter == 0){ 
      Serial.println("Key1Count + Key2Count = 0");
      RGB_color(0, 0, 0); 
    } else {
      keyOnePress(keyOneCounter);
    }

  
  if (keyTwoCounter == 0){
      Serial.println("Key2Count = 0");
      RGB_color(0, 0, 0);
  } else if (keyTwoCounter == 1){
    fade(fadeAmount, brightness);
  } else if (keyTwoCounter == 2){
    //rainbow(rDirection, gDirection, bDirection, redValue, greenValue, blueValue);
    rainbow(); 
    //if(currentTime >=(loopTime + 30)){
    //  rainbow(); 
    //  loopTime = currentTime;
    //}
  }
  if(keyTwoCounter == 3){
    keyTwoCounter = 0;
  }
  if (keyOneCounter == 1,2,3 && keyTwoCounter != 0) keyOneCounter=0;
  if (keyTwoCounter == 1,2 && keyOneCounter != 0) keyTwoCounter=0;

}

//void rainbow(int rDirection, int gDirection, int bDirection, int redValue, int greenValue, int blueValue){
void rainbow(){
    Serial.println("Rainbow mode ON.");
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
}
