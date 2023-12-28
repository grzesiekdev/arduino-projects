#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>

#define START_PIN 13
#define STOP_PIN 12

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup() {
  pinMode(START_PIN, INPUT_PULLUP);
  pinMode(STOP_PIN, INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Stoper!");
  lcd.setCursor(0, 1);
  lcd.print("00:00");
}

double odczyt = 0;
unsigned long startTime;
unsigned long currentTime;
unsigned long elapsedTime;
bool isStarted = 0;

void loop() {
  lcd.setCursor(0, 1);

  if (digitalRead(START_PIN) == LOW) {
    lcd.print("START");
    startTime = millis();
    isStarted = 1;
  }

  if (isStarted) {
    currentTime = millis();
    elapsedTime = currentTime - startTime;

    unsigned long seconds = (elapsedTime / 1000) % 60;
    unsigned long minutes = (elapsedTime / 60000) % 60;

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("START");

    lcd.setCursor(0, 1);
    lcd.print(String(minutes < 10 ? "0" : "") + String(minutes, DEC) + ":" +
              String(seconds < 10 ? "0" : "") + String(seconds, DEC));
    
    delay(250);

    if (digitalRead(STOP_PIN) == LOW) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("KONIEC");
      lcd.setCursor(0, 1);
      lcd.print(String(minutes < 10 ? "0" : "") + String(minutes, DEC) + ":" +
                String(seconds < 10 ? "0" : "") + String(seconds, DEC));

      isStarted = 0;
    }
  }
}
