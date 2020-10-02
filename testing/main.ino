#include "functions.hpp" // functions handler
#include "pins.h" // pin declarations

int keyOneCounter = 0;
int keyTwoCounter = 0;
int rDirection = -1, gDirection = 1, bDirection = -1;
int redValue = 254, greenValue = 1, blueValue = 255;
int delayTime = 500;
int fadeAmount = 1;
int brightness = 0;


enum LedStates{ON, OFF};
LedStates ledState;

enum SwitchStates {FADE, RAINBOW};

enum Colors {RED, GREEN, BLUE};
Colors Color;
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


  if (buttonTwo == HIGH) {
      if(ledState == ON){
        //LedStates ledState = ON;
        //digitalWrite(redPin, HIGH);
        //toggleMachine();
        //Color:RED;
        colorMachine();
      } else {
          LedStates ledState = ON;
          toggleMachine();
      }
 }
  
  if (keyOneCounter == 1,2,3 && keyTwoCounter != 0) keyOneCounter=0;
  if (keyTwoCounter == 1,2 && keyOneCounter != 0) keyTwoCounter=0;

}

void colorMachine(){
    if(Color == RED){
        Serial.println("hey");
    }
}


void toggleMachine() {
  switch (ledState) {
    case OFF: { 
      digitalWrite(redPin, 255);
      ledState = ON;
      break;
    }
    case ON: { 
      digitalWrite(redPin, 0);
      ledState = OFF;
      break;
    }
  }
}