#include "functions.h" // functions handler
#include "pins.h" // pin declarations

int keyOneCounter = 0;
int keyTwoCounter = 0;
int rDirection = -1, gDirection = 1, bDirection = -1;
int redValue = 254, greenValue = 1, blueValue = 255;
int delayTime = 500;
int fadeAmount = 1;
int brightness = 0;

bool buttonOneState;

unsigned long fadeTime;

void setup() {
  Serial.begin(115200);
  pinMode(analogReg, INPUT);
  pinMode(key1, INPUT);
  pinMode(key2, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  
  int inputVal = analogRead(analogReg);
  int mappedValue = map(inputVal, 0, 1023, 0, 100);
  int buttonOne = digitalRead(key1);
  int buttonTwo = digitalRead(key2);
  fadeAmount = mappedValue;


  if (buttonOne == HIGH){
    //keyOneCounter++;
    buttonOneState = true;
    Serial.println("key 1 pressed");
    delay(300);
  }

  if (buttonTwo == HIGH){
    keyTwoCounter++;
    Serial.println("key 2 pressed");
    delay(300);
  }
  
  if (buttonOneState == false){ 
      Serial.println("buttonOneState = false");
      RGB_color(0, 0, 0); 
    } else {
      //keyOnePress(keyOneCounter);
      buttonOneState = true;
      keyOnePressState(buttonOneState);
    }

/*
  if (buttonOneState == false && keyTwoCounter == 0){ 
      Serial.println("buttonOneState = false");
      RGB_color(0, 0, 0); 
    } else {
      //keyOnePress(keyOneCounter);
      keyOnePressState(buttonOneState);
      buttonOneState = true;

    }
*/
  
  if (keyTwoCounter == 0){
      Serial.println("Key2Count = 0");
      RGB_color(0, 0, 0);
  } else if (keyTwoCounter == 1){
    fade(fadeAmount, brightness);
  } else if (keyTwoCounter == 2){
    //rainbow(rDirection, gDirection, bDirection, redValue, greenValue, blueValue);
    if (millis() > fadeTime){
      //rainbow(); 
      setColor(redValue, greenValue, blueValue);
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
    fadeTime = millis() + 50;
}


void setColor(int red, int green, int blue) {

    analogWrite(redPin, redValue);
    analogWrite(greenPin, greenValue);
    analogWrite(bluePin, blueValue); 

    if ( redValue < red ) redValue += 1;
    if ( redValue > red ) redValue -= 1;

    if ( greenValue < green ) greenValue += 1;
    if ( greenValue > green ) greenValue -= 1;

    if ( greenValue < blue ) greenValue += 1;
    if ( greenValue > blue ) greenValue -= 1;

    //_setColor();
    fadeTime = millis() + 50;
}

void _setColor() {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue); 
}