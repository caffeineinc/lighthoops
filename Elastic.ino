/**
 * Simple elastic physics loop used as the base of other patterns
 */

void elasticSetup() {
  unsigned int i;
  
  for(i=0; i<NUM_HOOPS; i++) {
    // Initial potential energy in the system
    gOffset[i] = 64*16;
    
    gAcc[i] = 0;
    gVel[i] = 0;
  }
}

void elastic() {
  unsigned int i;

  // vel & pos updates aren't configurable
  for(i=0; i<NUM_HOOPS; i++) {
    gOffset[i] += gVel[i]/256;
    gVel[i] += gAcc[i]/256;
  }

  // acc updates relate to the elastic connections that we have configured
  // The first hoop is elasticly bound to its own origin point, like a pull-back car
  gAcc[0] = -gOffset[0] * 64;

  // All other hoops are bound to the previous hoop in the sequence
  for(i=1; i<NUM_HOOPS; i++) {
    gAcc[i] = (gOffset[i-1] - gOffset[i]) * 16;
  }
}

