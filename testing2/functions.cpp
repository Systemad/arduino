#include "functions.hpp"
#include "pins.h"

void fade(int brightness, int fadeAmount){
    Serial.println("Fade.");
    analogWrite(redPin, brightness);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
    brightness += fadeAmount;

    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = fadeAmount;
    }
}

void keyOnePress(int keyOneCounter){    
  if (keyOneCounter == 1){
    Serial.println("Red.");
    RGB_color(255, 0, 0);
  } else if (keyOneCounter == 2){
    Serial.println("Green.");
    RGB_color(0, 255, 0);
  } else if (keyOneCounter == 3){
    Serial.println("Blue.");
    RGB_color(0, 0, 255);
  } else if (keyOneCounter == 4){
    Serial.println("Counter reset");
    keyOneCounter = 0;
  }
}

void keyOnePressState(bool keyOneState){    
  if (keyOneState == true){
    Serial.println("Red.");
    RGB_color(255, 0, 0);
  }
  
  /*
  } else if (keyOneCounter == 2){
    Serial.println("Green.");
    RGB_color(0, 255, 0);
  } else if (keyOneCounter == 3){
    Serial.println("Blue.");
    RGB_color(0, 0, 255);
  } else if (keyOneCounter == 4){
    Serial.println("Counter reset");
    keyOneCounter = 0;
  }
  */
}


void RGB_color(int redValue, int greenValue, int blueValue)
{
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}