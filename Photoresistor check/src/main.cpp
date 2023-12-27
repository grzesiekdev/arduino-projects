#include <Arduino.h>

#define greenLed 10
#define yellowLed 9
#define redLed 8


int resistor1value = 0;
int resistor2value = 0;
int threshold = 50;


void setup() {
	Serial.begin(9600);

	pinMode(greenLed, OUTPUT);
	pinMode(yellowLed, OUTPUT);
	pinMode(redLed, OUTPUT);

	digitalWrite(greenLed, LOW);
	digitalWrite(yellowLed, LOW);
	digitalWrite(redLed, LOW);
}

void loop() {
	resistor1value = analogRead(A5);
	resistor2value = analogRead(A4);

	Serial.println("Resistor 1: " + String(resistor1value));
	Serial.println("Resistor 2: " + String(resistor2value));

	if((resistor1value + threshold) < resistor2value) {
		digitalWrite(greenLed, HIGH);
		digitalWrite(yellowLed, LOW);
		digitalWrite(redLed, LOW);
	} else if((resistor2value + threshold) < resistor1value) {
		digitalWrite(greenLed, LOW);
		digitalWrite(yellowLed, LOW);
		digitalWrite(redLed, HIGH);
	} else {
		digitalWrite(greenLed, LOW);
		digitalWrite(yellowLed, HIGH);
		digitalWrite(redLed, LOW);
	}
	delay(500);
}
