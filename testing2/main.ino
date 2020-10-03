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

   if (buttonTwo == HIGH) {
     toggleMachine();
   }
    
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