#include "Arduino.h"

#define RED_LED_PIN 2
#define GREEN_LED_PIN 0
#define YELLOW_LED_PIN 1
#define BUTTON_PIN 13
#define POTENTIOMETER_PIN A5

int initialPotentiometerValue = 0;
int potentiameterValue = 0;
int enteredNumber = 0;
int chances = 3;
bool gameStarted = false;

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  Serial.begin(9600);

  initialPotentiometerValue = analogRead(POTENTIOMETER_PIN);
}

void loop() {
  static bool buttonPressed = false;

  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, LOW);

  if (digitalRead(BUTTON_PIN) == LOW && !buttonPressed) {
    buttonPressed = true;
    potentiameterValue = analogRead(POTENTIOMETER_PIN);

    if ((potentiameterValue > initialPotentiometerValue - 5) && (potentiameterValue < initialPotentiometerValue + 5)) {
      Serial.println("You have to set the potentiometer to some random position first!");
      delay(1000);
    } else {
      gameStarted = true;
      Serial.println("Enter number:");
    }
  }

  if (gameStarted) {
    if (Serial.available() > 0) {
      enteredNumber = Serial.readStringUntil('\n').toInt();

      if ((enteredNumber > potentiameterValue - 50) && (enteredNumber < potentiameterValue + 50)) {
        digitalWrite(GREEN_LED_PIN, HIGH);
        Serial.println("Correct! Searched value was " + String(potentiameterValue) + ", and your guess was " + String(enteredNumber));
        gameStarted = false;
        Serial.println("Press button to play again!");
      } else {
        if (chances > 0) {
          Serial.println("Incorrect! You have " + String(chances) + " more chances");
          chances--;
          digitalWrite(YELLOW_LED_PIN, HIGH);
          Serial.println("Enter number:");
        } else {
          Serial.println("You've lost! Correct answer was " + String(potentiameterValue));
          digitalWrite(RED_LED_PIN, HIGH);
          gameStarted = false;
          chances = 3;
          Serial.println("Press button to play again!");
        }
      }
    }
  }

  delay(50);

  if (digitalRead(BUTTON_PIN) == HIGH) {
    buttonPressed = false;
  }
}
