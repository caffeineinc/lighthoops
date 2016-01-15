#include "FastLED.h"
FASTLED_USING_NAMESPACE

// Constants

#define DATA_PIN      3
#define NUM_HOOPS     4
#define LEDS_PER_HOOP 115
#define NUM_LEDS      (NUM_HOOPS * LEDS_PER_HOOP)
#define BRIGHTNESS          96

// Globals

// Elastic physics
long gOffset[NUM_HOOPS];
long gVel[NUM_HOOPS];
long gAcc[NUM_HOOPS];

// LEDs that all patterns write to
CRGB leds[NUM_LEDS];

uint8_t energy[NUM_LEDS];


uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

// Delay between frames in ms
int gFrameDelay = 10;

void setup() {
  Serial.begin(9600);

  delay(200);

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

  spinnerSetup();
}

// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { spinner, rapidCycle, bondDots };
SimplePatternList gPatternSetups = { spinnerSetup, rapidCycleSetup, bondDotsSetup };

void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();
  // insert a delay to keep the framerate modest
  if(gFrameDelay) {
    FastLED.delay(gFrameDelay );
  }

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  EVERY_N_SECONDS( 30 ) { nextPattern(); } // change patterns periodically
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE(gPatterns);
  gPatternSetups[gCurrentPatternNumber]();
}

