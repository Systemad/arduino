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



enum LedStates{ ON, OFF };
LedStates ledState;

void setup() {
  Serial.begin(115200);
  digitalWrite(redPin, 0);
  init();
}

void loop() {


  long time_now = millis();
  int inputVal = analogRead(analogReg); // Potentiometer
  int mappedValue = map(inputVal, 0, 1023, 0, 100); // Map it from 0-100
  // Buttons Key1 and Key2
  int keyOne = digitalRead(key1);
  int keyTwo = digitalRead(key2);
  
  
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
