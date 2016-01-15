
/**
 * 4 colour spinner
 */
void spinnerSetup() {
  gFrameDelay = 8;
  elasticSetup();
}

void spinner() {
  elastic();

  // 4 colour spinner
  fourColourWheel(leds, gOffset[0] / 16);
  fourColourWheel(leds + LEDS_PER_HOOP, gOffset[1] / 16);
  fourColourWheel(leds + LEDS_PER_HOOP*2, gOffset[2] / 16);
  fourColourWheel(leds + LEDS_PER_HOOP*3, gOffset[3] / 16);
}


/*
 * Draw a 4 colour wheel of 115 LEDs with the given rotational offet
 */
void fourColourWheel(CRGB *leds, int offset) {
  wrappedFill(leds, offset, 29, CRGB::Red, LEDS_PER_HOOP);
  wrappedFill(leds, offset+29, 29, CRGB::Green, LEDS_PER_HOOP);
  wrappedFill(leds, offset+58, 29, CRGB::Blue, LEDS_PER_HOOP);
  wrappedFill(leds, offset+87, 28, CRGB::Yellow, LEDS_PER_HOOP);
}
