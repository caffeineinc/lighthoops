/**
 * Fields of colour that blend to white
 */

// Number of points in the particle system

void colourFieldsSetup() {
  byte i;

  gFrameDelay = 10;
  gNumParticles = 8;

  byte hues[8] = {0, 96, 160, 224, 64, 192, 32, 128 };

  for(i=0; i<gNumParticles; i++) {
    // Position and colour randomly
    initParticle(i, random16(LEDS_PER_HOOP * 16), CHSV(hues[i], 255, 255));

    // Set some initial movement/force
    //setParticleMovement(i, (random8()-127)*4, (random8()-127)*16);
    setParticleMovement(i, (512*random8(2)-255)*8, 0);

    // Constrain each particle to live within the first hoop
    setParticleConstraints(i, 0, LEDS_PER_HOOP-1);
  }
}

int gFTB = 0;
int gDeltaFTB = 1;

void colourFields() {
  moveParticles();

  gFTB += gDeltaFTB;
  if(gFTB > 50) gDeltaFTB = -1;
  else if(gFTB < 1) gDeltaFTB = 1;

  fadeToBlackBy(leds, NUM_LEDS, gFTB );
  sortParticles();
  drawParticles();

  //blendBetweenParticles();
}
