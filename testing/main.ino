#include "functions.hpp" // functions handler
#include "pins.h" // pin declarations

int keyOneCounter = 0;
int keyTwoCounter = 0;
int rDirection = -1, gDirection = 1, bDirection = -1;
int redValue = 254, greenValue = 1, blueValue = 255;
int delayTime = 500;
int fadeAmount = 1;
int brightness = 0;

// Led state
enum LedStates {
  ON, 
  OFF 
};
LedStates ledState;

// Led mode
enum SwitchStates {
  FADE,
  RAINBOW
};
SwitchStates switchState;

// Led Colors
enum Colors {
  RED,
  GREEN,
  BLUE,
  NONE 
};
Colors color;


unsigned long chrono;

void setup() {
  Serial.begin(115200);
  pinMode(analogReg, INPUT);
  pinMode(key1, INPUT);
  pinMode(key2, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  color = RED;
  ledState = ON;

}

void loop() {


  int inputVal = analogRead(analogReg);
  int mappedValue = map(inputVal, 0, 1023, 0, 100);
  int buttonOne = digitalRead(key1);
  int buttonTwo = digitalRead(key2);
  fadeAmount = mappedValue;

  /*
  if (buttonTwo == HIGH) {
    if(ledState == ON) {
      if(color == Colors::RED) {
           Serial.println("RED TO GREEN");
           color == Colors::GREEN;
      } else if (color == Colors::GREEN){
           Serial.println("GREEN TO BLUE");          
           color == Colors::BLUE;
      } else if (color == Colors::BLUE) {
           Serial.println("BLUE TO NONE");
           color == Colors::NONE;
      } else if (color == Colors::NONE){
           Serial.println("NONE TO LED OFF");
           color == Colors::NONE;
           LedStates ledState = OFF;
      }
    } else {
      LedStates ledState = ON;
      color == Colors::RED;
      Serial.println("LED ON, COLOR RED");
    }
  //toggleMachine();
    //colorMachine();
  }
  */

  // LED STATE 
   if (buttonTwo == HIGH) {
     toggleMachine();
     /*
     switch(ledState){
       case LedStates::ON:
          colorMachinima();
          break;

       case LedStates::OFF:
        ledState = LedStates::ON;
        if(color == NONE){
          color = RED;
          Serial.println("Color = none, led = off");
        }
        break;
        */
     }
     /* 
     if(ledState == LedStates::OFF && color == NONE){
      ledState = LedStates::ON;
      color = RED;
      Serial.println("LED ON, COLOR RED");
     } else if(ledState == LedStates::ON) {
      colorMachinima();
     }
      
      switch(color){
        case RED:
           Serial.println("RED TO GREEN");
           color = GREEN;
           break;
        case GREEN:
           Serial.println("GREEN TO BLUE");          
           color = BLUE;
           break;
        case BLUE:
           Serial.println("BLUE TO NONE");
           color = NONE;
           break;
        case NONE:
           Serial.println("NONE TO LED OFF");
           color = NONE;
           ledState = OFF;
           break;
      }
    } else if (ledState == OFF && color == NONE){
      Serial.println("ledState = on && color = none");

    } else {
      ledState = ON;
      color = RED;
      Serial.println("LED ON, COLOR RED");
    }
    */
    
}

void toggleMachine() {
  switch (ledState) {
    case OFF: 
      //digitalWrite(redPin, HIGH);
      colorMachinima();
      ledState = ON;
      break;
    case ON: 
      digitalWrite(redPin, LOW);
      ledState = OFF;
      break;
  }
}

void colorMachinima(){
      switch(color){
        case RED:
            if(millis() - chrono >= 2000){
              chrono = millis();
              Serial.println("RED");
              digitalWrite(redPin, 255);
              color = GREEN;
            }
           break;
        case GREEN:
           Serial.println("GREEN");          
           color = BLUE;
           break;
        case BLUE:
           Serial.println("BLUE");
           //color = NONE;
           break;
        case NONE:
           Serial.println("NONE");
           //color = RED;
           break;
    }
}