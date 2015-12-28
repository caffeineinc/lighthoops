
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
  fourColourWheel(leds + 115, gOffset[1] / 16);
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

/**
 * Fill a region from start-length with colour, but wrap the fill within wrapSize
 * Calls 2 fill commands when needed by the underlying code.
 * 
 * Breaks if length > wrapSize; don't do that.
 */
void wrappedFill(CRGB *leds, int start, int length, CRGB color, int wrapSize) {
  int segmentStart, segmentLength;
  segmentStart = start % wrapSize;
  if(segmentStart < 0) segmentStart += wrapSize;

  // 1 segment
  if(segmentStart + length < wrapSize) {
    fill_solid(leds+segmentStart, length, color); 

  // 2 segments
  } else {
    segmentLength = wrapSize - segmentStart - 1;
    fill_solid(leds + segmentStart, segmentLength, color);
    fill_solid(leds, length - segmentLength, color); 
  }
}
