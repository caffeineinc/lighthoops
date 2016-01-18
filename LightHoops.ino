#include "FastLED.h"
FASTLED_USING_NAMESPACE

// Constants

#define DATA_PIN      3
#define NUM_HOOPS     4
#define LEDS_PER_HOOP 115
#define NUM_LEDS      (NUM_HOOPS * LEDS_PER_HOOP)
#define BRIGHTNESS          128 //48  //96

// Globals

// Elastic physics
long gOffset[NUM_HOOPS];
long gVel[NUM_HOOPS];
long gAcc[NUM_HOOPS];

// LEDs that all patterns write to
CRGB leds[NUM_LEDS];

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gNumPatterns = 1; // Total number of patterns in current set
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

// Delay between frames in ms
int gFrameDelay = 10;

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

// Libraries
#include "Button.h"
#include "PIRSensor.h"
#include "ParticleSystem.h"
#include "GfxLib.h"
#include "Elastic.h"

//Patterns
#include "BondDots.h"
#include "ColourFields.h"
#include "RapidCycle.h"
#include "Spinner.h"

void nextPattern();
void activePatterns();
void inactivePatterns();

Button nextPatternButton(8, &nextPattern);

PIRSensor activator(9, 30, &activePatterns, &inactivePatterns);

// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
typedef void (**SimplePatternListRef)();

SimplePatternListRef gPatterns;
SimplePatternListRef gPatternSetups;

SimplePatternList gActivePatterns = { colourFields, spinner, rapidCycle, bondDots };
SimplePatternList gActivePatternSetups = { colourFieldsSetup, spinnerSetup, rapidCycleSetup, bondDotsSetup };

SimplePatternList gInactivePatterns = { bondDots };
SimplePatternList gInactivePatternSetups = { bondDotsSetup };

void setup() {
  //Serial.begin(9600);
  //Serial.print("Running LightHoops.ino, compiled ");
  //Serial.println(__DATE__);

  delay(200);

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

  nextPatternButton.setup();
  activator.setup();

  gPatterns = gInactivePatterns;
  gPatternSetups = gInactivePatternSetups;
  gNumPatterns = ARRAY_SIZE(gInactivePatterns);
  gCurrentPatternNumber = 0;

  gPatternSetups[gCurrentPatternNumber]();
}

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

  nextPatternButton.loop();
  activator.loop();

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  EVERY_N_SECONDS( 200 ) { nextPattern(); } // change patterns periodically
}

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % gNumPatterns;
  gPatternSetups[gCurrentPatternNumber]();
}

void activePatterns()
{
  //Serial.println("Movement detected - activating");
  gPatterns = gActivePatterns;
  gPatternSetups = gActivePatternSetups;
  gNumPatterns = ARRAY_SIZE(gActivePatterns);
  gCurrentPatternNumber = 0;

  gPatternSetups[gCurrentPatternNumber]();
}

void inactivePatterns()
{
  //Serial.println("No movement - deactivating");
  gPatterns = gInactivePatterns;
  gPatternSetups = gInactivePatternSetups;
  gNumPatterns = ARRAY_SIZE(gInactivePatterns);
  gCurrentPatternNumber = 0;

  gPatternSetups[gCurrentPatternNumber]();
}

