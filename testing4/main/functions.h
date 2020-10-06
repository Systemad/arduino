#pragma once
#include "common.h"
#include <Arduino.h>

/*
 * Includes all functions
 */


void initialize(); // Initalize pins

void welcomeMessage(); // Display a welcome message and instructions

void serial_receiver(); // Receivers input from serial console, then sends it to serial_handler()

void fade(int brightness, int fadeAmount); 

void rainbow(int mappedValue);

void toggleLedColor(int keyOneCounter);

void RGB_color(int redValue, int greenValue, int blueValue); // Writes led color

void input_handler(int keyOneCounter, int keyTwoCounter); // Input handler for fade() rainbow() and toggleLedColor()

void serial_handler(int mode); // Handles input from serial_reciever()
