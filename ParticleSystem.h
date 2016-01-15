/**
 * Simple particle system to support other patterns
 */

#define NUM_POINTS 4

/**
 * A particles a physically aware coloured point
 */
struct Particle {
  CHSV colour;
  long offset; // Position, in 16ths of an LED
  long vel; // Velocity, in 256ths of an offset unit per tick
  long acc; // Velocity, in 256ths of a velocity unit per tick

  long min; // offset constraints
  long max;
};

Particle particles[NUM_POINTS];

/**
 * Initialise a stationary particle
 */
void initParticle(int i, long offset, CHSV colour) {
  particles[i] = {colour, offset, 0, 0, 0, NUM_LEDS * 16 };
}

/**
 * Set the velocity & acceleration of a particle
 */
void setParticleMovement(int i, long vel, long acc) {
  particles[i].vel = vel;
  particles[i].acc = acc;
}

/**
 * Constrain a particle to loop within the given min/max LED indexes
 */
void setParticleConstraints(int i, long min, long max) {
  particles[i].min = min * 16;
  particles[i].max = max * 16;
}

void moveParticle(Particle *p) {
    p->offset += p->vel/256;
    p->vel += p->acc/256;

    // Constrain
    while(p->offset < p->min) {
      p->offset += (p->max - p->min);
    }
    while(p->offset > p->max) {
      p->offset -= (p->max - p->min);
    }
}

void moveParticles() {
  unsigned int i;

  // vel & pos updates aren't configurable
  for(i=0; i<NUM_POINTS; i++) {
    moveParticle(&(particles[i]));
  }
}

/**
 * Particle GFX lib
 */

void wrappedGradient(CRGB *, int, int, CHSV, CHSV, int);

/**
 * Draw blended gradients between each particle
 */
void blendBetweenParticles() {
  int i, nextI, length;
  for(i=0; i<NUM_POINTS; i++) {
    nextI = (i+1) % NUM_POINTS;

    length = (particles[nextI].offset - particles[i].offset)/16;
    if(length < 0) length += LEDS_PER_HOOP;
    wrappedGradient(leds, particles[i].offset/16, length, particles[i].colour, particles[nextI].colour, LEDS_PER_HOOP);
  }
}

/**
 * Draw each particle
 */
void drawParticles() {
  int i;

  for(i=0; i<NUM_POINTS; i++) {
    leds[particles[i].offset / 16] = particles[i].colour;
  }
}


