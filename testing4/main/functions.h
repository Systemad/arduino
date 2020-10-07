#pragma once
#include "common.h"
#include <Arduino.h>

/*
 * Includes all functions
 */

void initialize(); // Initalize pins

void welcomeMessage(); // Display a welcome message and instructions

void serial_receiver(); // Receiver input from serial console, then sends it to serial_handler()

void fade(int brightness, int fadeAmount); // Fade function

void rainbow(int mappedValue); // Rainbow function

void toggleLedColor(int keyOneCounter); // Toggle LED function

void RGB_color(int redValue, int greenValue, int blueValue); // Writes LED color

void input_handler(int keyOneCounter, int keyTwoCounter); // Input handler for fade(), rainbow() and toggleLedColor()

void serial_handler(int mode); // Handles input from serial_reciever()
