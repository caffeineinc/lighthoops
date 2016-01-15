/**
 * Rapid cycling persistence of vision trick
 */

CRGB gCycleColours[] = {/* CRGB::White,*/ CRGB::Red, CRGB::Blue, CRGB::Green };
int gCurrentColour = 0;
int gWhitePortion = 0;

void rapidCycleSetup() {
  elasticSetup();

  gFrameDelay = 0;
}
void rapidCycle() {
  EVERY_N_MILLISECONDS(8) {
    elastic();
  }

  gCurrentColour = (gCurrentColour+1) % ARRAY_SIZE(gCycleColours);
  fill_solid(leds, NUM_LEDS, gCycleColours[gCurrentColour]);

  wrappedFill(leds, gOffset[0] / 16, 58, CRGB::Red, LEDS_PER_HOOP);
  wrappedFill(leds + LEDS_PER_HOOP, gOffset[1] / 16, 58, CRGB::Green, LEDS_PER_HOOP);

  //CRGB(100,90,120)
}

