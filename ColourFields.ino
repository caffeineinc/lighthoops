/**
 * Fields of colour that blend to white
 */

// Number of points in the particle system

void wrappedGradient(CRGB *, int, int, CHSV, CHSV, int);

void colourFieldsSetup() {
  byte i;

  gFrameDelay = 10;

  for(i=0; i<NUM_POINTS; i++) {
    gPointOffset[i] = random16(LEDS_PER_HOOP * 16);
    gPointColour[i] = CHSV(random8(), 255, 255);
    gPointAcc[i] = (random8()-127)*255;
    gPointVel[i] = 0;

    // Constrain each particle to live within the first hoop
    constrainParticle(i, 0, LEDS_PER_HOOP-1);
  }
}

void colourFields() {
  byte i, nextI;
  int length;

  fadeToBlackBy(leds, NUM_LEDS, 30);
  moveParticles();

  for(i=0; i<NUM_POINTS; i++) {

    leds[gPointOffset[i] / 16] = gPointColour[i];

    //nextI = (i+1) % NUM_POINTS;
    //length = gPointPos[nextI ] - gPointPos[i];
    //if(length < 0) length += LEDS_PER_HOOP;
    //wrappedGradient(leds, gPointOffset[i]/16, length, gPointColour[i], gPointColour[nextI], LEDS_PER_HOOP);
  }
}
