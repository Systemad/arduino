#include "functions.h" // functions handler
#include "pins.h" // pin declarations

int keyOneCounter = 0;
int keyTwoCounter = 0;
int redValue = 254;
int greenValue = 1;
int blueValue = 255;

int rDirection = -1, gDirection = 1, bDirection = -1;
int delayTime = 500;
int fadeAmount = 1;
int brightness = 0;

unsigned long fadeMillis;


int ledState = HIGH;         // current state of LED
int buttonState;             // current state of button
int lastButtonState = LOW;   // previous state of button

unsigned long lastDebounceTime = 0; // last toggle
unsigned long debounceDelay = 50;   // debounce time

void setup() {
  Serial.begin(115200);
  init();
}

void loop() {
  int inputVal = analogRead(analogReg); // Potentiometer
  int mappedValue = map(inputVal, 0, 1023, 0, 100); // Map it from 0-100
  // Buttons Key1 and Key2
  int keyOne = digitalRead(key1);
  int keyTwo = digitalRead(key2);
 
  if (keyTwo != lastButtonState) // If the switch changed
  {
    lastDebounceTime = millis();  // reset the debouncing
  }
  //check if debounce time > 50ms
  if ((millis() - lastDebounceTime) > debounceDelay)
  { if (keyTwo != buttonState)
    { buttonState = keyTwo;
      if (buttonState == HIGH)
      {
        //ledState = !ledState;
        keyTwoCounter++;
        Serial.println("Key two pressed");
      }
    }
  }

  if (buttonState == HIGH){
    keyOneCounter++;
    Serial.println("key 1 pressed");
    delay(300);
  }

  //if (keyTwo == HIGH){
  //  keyTwoCounter++;
  //  Serial.println("key 2 pressed");
  //  delay(300);
  //}
  
  if (keyOneCounter == 0 && keyTwoCounter == 0){ 
      Serial.println("Key1Count Key2Count = 0");
      RGB_color(0, 0, 0); 
    } else {
      keyOnePress(keyOneCounter);
    }

  
  if (keyTwoCounter == 0){
      Serial.println("Key2Count = 0");
      RGB_color(0, 0, 0);
  } else if (keyTwoCounter == 1){
    fade(mappedValue, brightness);
  } else if (keyTwoCounter == 2){
    if (millis() > fadeMillis){
      rainbow(); 
      Serial.println("Raunbiw");
    }
  }
  if(keyTwoCounter == 3){
    keyTwoCounter = 0;
  }
  if (keyOneCounter == 1,2,3 && keyTwoCounter != 0) keyOneCounter=0;
  if (keyTwoCounter == 1,2 && keyOneCounter != 0) keyTwoCounter=0;

  lastButtonState = keyTwo; 

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
    fadeMillis = millis() + 30;
}
