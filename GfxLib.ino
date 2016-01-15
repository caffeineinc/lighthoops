/**
 * More drawing tools for FastLED.
 */

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

/**
 * Fill a region from start-length with colour, but wrap the fill within wrapSize
 * Calls 2 fill commands when needed by the underlying code.
 * 
 * Breaks if length > wrapSize; don't do that.
 */
void wrappedGradient(CRGB *leds, int start, int length, CHSV color1, CHSV color2, int wrapSize) {
  int segmentStart, segmentLength;
  CHSV midColor1, midColor2;
  
  segmentStart = start % wrapSize;
  if(segmentStart < 0) segmentStart += wrapSize;

  // 1 segment
  if(segmentStart + length < wrapSize) {
    fill_gradient(leds, segmentStart, color1, segmentStart+length, color2); 

  // 2 segments
  } else {
    segmentLength = wrapSize - segmentStart - 1;
  
    midColor1 = blend( color1, color2, segmentLength * 256 / length);
    midColor2 = blend( color1, color2, (segmentLength+1) * 256 / length);
    
    // To do: find mid-point colour
    fill_gradient(leds, segmentStart, color1, wrapSize-1, midColor1);
    fill_gradient(leds, 0, midColor2, length - segmentLength, color2); 
  }
}
