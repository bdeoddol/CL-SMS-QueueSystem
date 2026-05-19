#include <Arduino.h>
const int buttonPin1 = 2;
const int buttonPin2 = 3;
const int buttonPin3 = 4;

const int ledPin1 = 11;
const int ledPin2 = 6;
const int ledPin3 = 7;

// debounce settings
const unsigned long debounceDelay = 50;

// tracking arrays
int buttonPins[] = {2, 3, 4};
int ledPins[] = {11, 6, 7};

int lastStableState[3];
int lastReading[3];
unsigned long lastDebounceTime[3];

int lastLedState[3];

String ProjName[3] = {"86!", "Frisson", "Desk Drawer"};

void setup() {
  Serial.begin(9600);


  // set LED pins
  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  // set button pins (NO pull-up)
  for (int i = 0; i < 3; i++) {
    pinMode(buttonPins[i], INPUT);

    int reading = digitalRead(buttonPins[i]);
    lastStableState[i] = reading;
    lastReading[i] = reading;
    lastDebounceTime[i] = 0;

    lastLedState[i] = LOW;
  }
}

void loop() {
  for (int i = 0; i < 3; i++) {

    int reading = digitalRead(buttonPins[i]);

    // detect noise change
    if (reading != lastReading[i]) {
      lastDebounceTime[i] = millis();
      lastReading[i] = reading;
    }

    // if stable long enough → accept change
    if ((millis() - lastDebounceTime[i]) > debounceDelay) {

      if (lastStableState[i] != reading) {
        lastStableState[i] = reading;

        // update LED (pressed = HIGH)
        int currentLedState = (reading == HIGH) ? HIGH : LOW;
        digitalWrite(ledPins[i], currentLedState);

        // detect OFF → ON transition
        if (currentLedState == HIGH && lastLedState[i] == LOW) {
          Serial.println(ProjName[i]);
          // Serial.print(ProjName[i] + "(");
          // Serial.print("LED ");
          // Serial.print((i + 1));
          // Serial.print(")");
          // Serial.println(" requests new group");
        }

        lastLedState[i] = currentLedState;
      }
    }
  }
}