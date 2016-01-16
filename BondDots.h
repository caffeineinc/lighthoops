/**
 * Animated dos vaguely reminiscent of the 007 title sequence
 */
unsigned int gDotPos = 0;
CRGB coveredDot = CRGB::Black;

void bondDotsSetup() {
   gFrameDelay = 10;
}

void bondDots() {
  // Persistent items fade, every 4th tick
  if(gDotPos % 2 == 0) {
    fadeToBlackBy( leds, NUM_LEDS, 1);
  }

  // Preseve the value of the covered dot
  leds[gDotPos] = coveredDot;
  gDotPos = (gDotPos+1) % NUM_LEDS;
  coveredDot = leds[gDotPos];

  leds[gDotPos] = CRGB::White;

  // Persist every 5th
  if(gDotPos % 5 == 0) {
    coveredDot = CRGB::White;
  }

  EVERY_N_MILLISECONDS( 500 ) {
    memmove( leds, leds+1, (NUM_LEDS-1) * sizeof( CRGB) );
  }
}
