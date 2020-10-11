#include "pins.h"

class Led {
    private:
    byte pin;

    public:
    Led(byte pin){
        this->pin = pin;
        init();
    }

    void init(){
        pinMode(pin, OUTPUT);
        off();
    }

    void off(){
        digitalWrite(pin, LOW);
    }
    void on(){
        digitalWrite(pin, HIGH);
    }
};

class Button{
    private:
    byte pin;
    byte state;
    byte lastReading;

    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 50;

    public:
    Button(byte pin){
        this->pin = pin;
        lastReading = LOW;
        init();
    }

    void init(){
        pinMode(pin, INPUT);
        update();
    }

    void update(){
        byte newReading = digitalRead(pin);

        if(newReading != lastReading){
            lastDebounceTime = millis();
        }

        if(millis() - lastDebounceTime > debounceDelay){
            state = newReading;
        }
        lastReading = newReading;
    }

    byte getState(){
        update();
        return state;
    }

    void isPressed(){
        return (getState() == HIGH);
    }


};

Led led1(redPin);

void setup(){
    Serial.begin(9600);
}

void loop(){
    led1.on();
    delay(500);
    led1.off();
    delay(500);
}