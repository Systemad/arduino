#pragma once

#include "common.h"
#include <Arduino.h>


void fade(int brightness, int fadeAmount);
void rainbow(int mappedValue);
void toggleLedColor(int keyOneCounter);
void RGB_color(int redValue, int greenValue, int blueValue);
void initialize();
void resetCounter(int key);
void logicCheck();

void input_handler(int keyOneCounter, int keyTwoCounter);
void select(int serialMode, int keyOneCounter, int keyTwoCounter);
//void serialRemote(int keyOneCounter, int keyTwoCounter, int mappedValue);
