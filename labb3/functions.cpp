#include "functions.h"
#include "pins.h"

void fade(int brightness, int fadeAmount){
    Serial.println("Fade.");
    analogWrite(redPin, brightness);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
    brightness += fadeAmount;

    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = 100; //-fadeAmount * 50;
    }
  delay(30);
}
/*
void rainbow(int redValue, int greenValue, int blueValue, int rDirection, int gDirection, int bDirection){
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
    delay(100); 
}
*/
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


void RGB_color(int redValue, int greenValue, int blueValue)
 {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}