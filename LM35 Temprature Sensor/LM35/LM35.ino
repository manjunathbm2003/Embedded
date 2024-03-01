#include <Arduino.h>
#include <elapsedMillis.h>  // Include the library for tracking elapsed time
// Include the library to communicate with the LM35 sensor
#include <LM35.h>



const int sensorPin = A0;  // LM35 temperature sensor connected to analog pin A0
LM35 lm35(sensorPin); // Create an instance of the LM35 class

const int ledPin = 13;     // Onboard LED connected to digital pin 13

elapsedMillis elapsedTime;  // Object to track elapsed time
int interval = 250;         // Initial blink interval for temperature below 30°C
boolean ledState = LOW;     // Initial state of LED is off

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int temperatureC = readTemperature();

  // Check if temperature is below 30°C
  if (temperatureC < 30) {
    interval = 250; // Change blink interval to 250ms
  }
  // Check if temperature is above or equal to 30°C
  else {
    interval = 500; // Change blink interval to 500ms
  }

  // Check if it's time to toggle the LED based on elapsed time
  if (elapsedTime >= interval) {
    // Toggle LED state
    ledState = !ledState;

    // Update LED state
    digitalWrite(ledPin, ledState);

    // Reset elapsed time
    elapsedTime = 0;
  }
}

int readTemperature() {
  // Read the analog value from LM35 sensor
   float temperatureC = lm35.cel();
    
    // Print temperature to serial monitor
    Serial.print("Temperature: ");
    Serial.print(temperatureC);
}
