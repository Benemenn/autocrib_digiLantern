#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#define NUM_STRIPS     5  // Number of strips connected (Pins 2 to 6)
#define NUMPIXELS      10 // Number of LEDs in each strip

Adafruit_NeoPixel strips[NUM_STRIPS] = {
  Adafruit_NeoPixel(NUMPIXELS, 2, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, 3, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, 4, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, 5, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, 6, NEO_GRB + NEO_KHZ800)
};

void simulateCandleFire();

void setup() {
  for (int i = 0; i < NUM_STRIPS; i++) {
    strips[i].begin();
    strips[i].setBrightness(200);
    strips[i].show(); // Initialize all pixels to 'off'
  }
}

void loop() {
  simulateCandleFire();
}

void simulateCandleFire() {
  static int flickerStart = 0;
  static int flickerEnd = 3;  // Number of LEDs to extinguish simultaneously
  static bool rising = true;
  static unsigned long previousMillis = 0;
  static unsigned long flickerInterval = random(20, 120); // Random initial delay interval

  unsigned long currentMillis = millis();

  // Check if it's time to update the LEDs
  if (currentMillis - previousMillis >= flickerInterval) {
    previousMillis = currentMillis;
    flickerInterval = random(20, 120); // Update interval with a new random value

    for (int s = 0; s < NUM_STRIPS; s++) {
      for (int i = 0; i < NUMPIXELS; i++) {
        // Create a random flicker effect with warm colors similar to candlelight
        bool isOff = false;
        if (i >= flickerStart && i < flickerEnd) {
          isOff = random(0, 100) < 70; // Higher chance for these LEDs to go off simultaneously
        } else if (i < NUMPIXELS / 3) {
          isOff = random(0, 100) < 20; // Lower chance for lower LEDs to flicker off
        } else {
          isOff = random(0, 100) < 40; // Moderate chance for middle LEDs to flicker off
        }

        if (isOff) {
          strips[s].setPixelColor(i, strips[s].Color(0, 0, 0)); // Turn off the LED
        } else {
          int flicker = random(180, 255); // Random brightness to simulate flickering, more emphasis on brighter orange tones
          int red = flicker;
          int green = random(80, 130); // Adjusted green value to create a more orange tone
          int blue = random(0, 20); // Reduced blue range to maintain a warm, orange tone

          strips[s].setPixelColor(i, strips[s].Color(red, green, blue));
        }
      }
      strips[s].show();
    }

    // Update flicker range to create a rising and falling effect
    if (rising) {
      flickerStart++;
      flickerEnd++;
      if (flickerEnd >= NUMPIXELS) {
        rising = false;
      }
    } else {
      flickerStart--;
      flickerEnd--;
      if (flickerStart <= 0) {
        rising = true;
      }
    }
  }
}
