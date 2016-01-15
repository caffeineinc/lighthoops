/**
 * Simple particle system to support other patterns
 */

#define NUM_POINTS 4

// Color 
CHSV gPointColour[NUM_POINTS];

long gPointOffset[NUM_HOOPS]; // Position, in 16ths of an LED
long gPointVel[NUM_HOOPS]; // Velocity, in 256ths of an offset unit per tick
long gPointAcc[NUM_HOOPS]; // Velocity, in 256ths of a velocity unit per tick

// Constrain to loop withn the given region
long gPointMin[NUM_HOOPS];
long gPointMax[NUM_HOOPS];

void moveParticles() {
  unsigned int i;

  // vel & pos updates aren't configurable
  for(i=0; i<NUM_POINTS; i++) {
    gPointOffset[i] += gPointVel[i]/256;
    gPointVel[i] += gPointAcc[i]/256;

    // Constrain
    while(gPointOffset[i] < gPointMin[i]) {
      gPointOffset[i] += (gPointMax[i]-gPointMin[i]);
    }
    while(gPointOffset[i] > gPointMax[i]) {
      gPointOffset[i] -= (gPointMax[i]-gPointMin[i]);
    }
    
  }

}

/**
 * Constrain a particle to loop within the given min/max LED indexes
 */
void constrainParticle(int i, long min, long max) {
  gPointMin[i] = min * 16;
  gPointMax[i] = max * 16;
}

/**
 * Particle GFX lib
 */


/**
 * Draw blended gradients between each particle
 */
void blendBetweenParticles() {
  int i, nextI, length;
  for(i=0; i<NUM_POINTS; i++) {
    nextI = (i+1) % NUM_POINTS;
    
    length = (gPointOffset[nextI ] - gPointOffset[i])/16;
    if(length < 0) length += LEDS_PER_HOOP;
    wrappedGradient(leds, gPointOffset[i]/16, length, gPointColour[i], gPointColour[nextI], LEDS_PER_HOOP);
  }
}

/**
 * Draw each particle
 */
void drawParticles() {
  int i;
  
  for(i=0; i<NUM_POINTS; i++) {
    leds[gPointOffset[i] / 16] = gPointColour[i];
  }
}
 

