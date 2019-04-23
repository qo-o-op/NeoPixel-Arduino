#include <Adafruit_NeoPixel.h>

#define PIN 6
#define LEDS 28
Adafruit_NeoPixel leds(LEDS, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
	// put your setup code here, to run once:
	leds.begin();
	Serial.begin(9600);
}

void loop() {
	static unsigned long getTick = 0;
	static unsigned long timeOut = 0;
	static uint8_t
		red = 0,
		green = 0,
		blue = 0;

	if (millis() - getTick > 100) {

		while (Serial.available())//Clear avilable data
			Serial.read();

		Serial.write('G');//Send request data to PC
		getTick = millis();//Reset task tick
	}
	else if (Serial.available() >= 3) {
		red = Serial.read();
		green = Serial.read();
		blue = Serial.read();
		timeOut = millis();
	}
	else if (millis() - timeOut > 1000) {
		red = green = blue = 0;
	}

	for (int i = 0; i < 16; i++)
		leds.setPixelColor(i, leds.Color(green, red, blue));
	for (int i = 16; i < 28; i++)
		leds.setPixelColor(i, leds.Color(red, green, blue));
	leds.show();
}