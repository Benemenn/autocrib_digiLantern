/*
Code adapted, example from Tim (https://github.com/timpear/NeoCandle)
Credits go to him.
*/


#include <Adafruit_NeoPixel.h>
#define NUM_STRIPS 8  // Number of strips connected (Pins 2 to 9)
#define NUMPIXELS 10  // Number of LEDs in each strip

Adafruit_NeoPixel strips[NUM_STRIPS] = {
  Adafruit_NeoPixel(NUMPIXELS, 2, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, 3, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, 4, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, 5, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, 6, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, 7, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, 8, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, 9, NEO_GRB + NEO_KHZ800)
};

// Color variables: mix RGB (0-255) for desired yellow
int redPx = 240;
int grnHigh = 80;
int bluePx = 5;

// Animation time variables, with recommendations
int burnDepth = 6; // How much green dips below grnHigh for normal burn
int flutterDepth = 20; // Maximum dip for flutter
int cycleTime = 200; // Duration of one dip in milliseconds

// Variables for controlling animation dynamics
int fDelay;
int fRep;
int flickerDepth;
int burnDelay;
int burnLow;
int flickDelay;
int flickLow;
int flutDelay;
int flutLow;

// Basic fire function - not called in main loop
void fire(int grnLow) {
  for (int grnPx = grnHigh; grnPx > grnLow; grnPx--) {
    int halfGrn = grnHigh - ((grnHigh - grnPx) / 2);
    int darkGrn = grnPx - 70;
    darkGrn = constrain(darkGrn, 5, 255);
    for (int s = 0; s < NUM_STRIPS; s++) {
      for (int p = 0; p < NUMPIXELS; p++) {
        if (p == 8 || p == 9) { // Shift flickering effect to the opposite end
          strips[s].setPixelColor(p, redPx - 180, darkGrn, 0);
        } else if (p == 7) {
          strips[s].setPixelColor(p, redPx - 120, grnPx - 50, bluePx - 5);
        } else if (p == 6) {
          strips[s].setPixelColor(p, redPx - 60, grnPx - 35, bluePx - 2);
        } else if (p == 4 || p == 5) {
          strips[s].setPixelColor(p, redPx, grnPx, bluePx);
        } else if (p == 3) {
          strips[s].setPixelColor(p, redPx, halfGrn, bluePx);
        } else if (p == 0 || p == 1 || p == 2) {
          strips[s].setPixelColor(p, redPx, grnHigh, bluePx);
        }
      }
      strips[s].show();
    }
    delay(fDelay);
  }
  for (int grnPx = grnLow; grnPx < grnHigh; grnPx++) {
    int halfGrn = grnHigh - ((grnHigh - grnPx) / 2);
    int darkGrn = grnPx - 70;
    darkGrn = constrain(darkGrn, 5, 255);
    for (int s = 0; s < NUM_STRIPS; s++) {
      for (int p = 0; p < NUMPIXELS; p++) {
        if (p == 8 || p == 9) { // Shift flickering effect to the opposite end
          strips[s].setPixelColor(p, redPx - 180, darkGrn, 0);
        } else if (p == 7) {
          strips[s].setPixelColor(p, redPx - 120, grnPx - 50, bluePx - 5);
        } else if (p == 6) {
          strips[s].setPixelColor(p, redPx - 60, grnPx - 35, bluePx - 2);
        } else if (p == 4 || p == 5) {
          strips[s].setPixelColor(p, redPx, grnPx, bluePx);
        } else if (p == 3) {
          strips[s].setPixelColor(p, redPx, halfGrn, bluePx);
        } else if (p == 0 || p == 1 || p == 2) {
          strips[s].setPixelColor(p, redPx, grnHigh, bluePx);
        }
      }
      strips[s].show();
    }
    delay(fDelay);
  }
}

// Fire animation
void on(int f) {
  fRep = f * 1000;
  int grnPx = grnHigh - 6;
  for (int s = 0; s < NUM_STRIPS; s++) {
    for (int p = 0; p < NUMPIXELS; p++) {
      if (p == 8 || p == 9) { // Shift flickering effect to the opposite end
        strips[s].setPixelColor(p, redPx - 180, grnPx - 70, 0);
      } else if (p == 7) {
        strips[s].setPixelColor(p, redPx - 120, grnPx - 50, bluePx - 5);
      } else if (p == 6) {
        strips[s].setPixelColor(p, redPx - 60, grnPx - 35, bluePx - 2);
      } else if (p == 4 || p == 5) {
        strips[s].setPixelColor(p, redPx, grnPx, bluePx);
      } else if (p == 3) {
        strips[s].setPixelColor(p, redPx, grnPx, bluePx);
      } else if (p == 0 || p == 1 || p == 2) {
        strips[s].setPixelColor(p, redPx, grnHigh, bluePx);
      }
    }
    strips[s].show();
  }
  delay(fRep);
}

void burn(int f) {
  fRep = f * 8;
  fDelay = burnDelay;
  for (int var = 0; var < fRep; var++) {
    fire(burnLow);
  }
}

void flicker(int f) {
  fRep = f * 8;
  fDelay = burnDelay;
  fire(burnLow);
  fDelay = flickDelay;
  for (int var = 0; var < fRep; var++) {
    fire(flickLow);
  }
  fDelay = burnDelay;
  fire(burnLow);
  fire(burnLow);
  fire(burnLow);
}

void flutter(int f) {
  fRep = f * 8;
  fDelay = burnDelay;
  fire(burnLow);
  fDelay = flickDelay;
  fire(flickLow);
  fDelay = flutDelay;
  for (int var = 0; var < fRep; var++) {
    fire(flutLow);
  }
  fDelay = flickDelay;
  fire(flickLow);
  fire(flickLow);
  fDelay = burnDelay;
  fire(burnLow);
  fire(burnLow);
}

void setup() {
  flickerDepth = (burnDepth + flutterDepth) / 2.4;
  burnLow = grnHigh - burnDepth;
  burnDelay = (cycleTime / 2) / burnDepth;
  flickLow = grnHigh - flickerDepth;
  flickDelay = (cycleTime / 2) / flickerDepth;
  flutLow = grnHigh - flutterDepth;
  flutDelay = ((cycleTime / 2) / flutterDepth);

  for (int s = 0; s < NUM_STRIPS; s++) {
    strips[s].begin();
    strips[s].show();
  }
}

// In loop, call CANDLE STATES, with duration in seconds
// 1. on() = solid yellow
// 2. burn() = candle is burning normally, flickering slightly
// 3. flicker() = candle flickers noticeably
// 4. flutter() = the candle needs air!

void loop() {
  burn(10);
  flicker(5);
  burn(8);
  flutter(6);
  burn(3);
  on(10);
  burn(10);
  flicker(10);
}
