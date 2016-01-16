/**
 * Simple particle system to support other patterns
 */

#define MAX_PARTICLES   (8)

int gNumParticles = 0;

/**
 * A particles a physically aware coloured point
 */
struct Particle {
  CHSV colour;

  int offset; // Position, in 16ths of an LED
  int vel; // Velocity, in 256ths of an offset unit per tick
  int acc; // Velocity, in 256ths of a velocity unit per tick

  int min; // offset constraints
  int max;
};

Particle particles[MAX_PARTICLES];

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
  for(i=0; i<gNumParticles; i++) {
    moveParticle(&(particles[i]));
  }
}

void swapParticles(int a, int b);

/**
 * Sort particles by offset
 * Bubble sort is tolerable, given the array is only a few elements
 */
void sortParticles() {
  int i;
  bool iterateAgain = true;

  while(iterateAgain) {
    iterateAgain = false;
    for(i=0; i<gNumParticles-1; i++) {
      if(particles[i].offset > particles[i+1].offset) {
        swapParticles(i, i+1);
        iterateAgain = true;
      }
    }
  }
}

/**
 * Swap 2 particles in the global array, without swapping the colour
 */
void swapParticles(int a, int b) {
  Particle tmp;
  tmp = particles[a];
  particles[a] = particles[b];

  particles[a].colour = tmp.colour;
  tmp.colour = particles[b].colour;

  particles[b] = tmp;
}

/**
 * Particle GFX lib
 */

//void wrappedGradient(CRGB *, int, int, CHSV, CHSV, int);
void wrappedGradient(CRGB *, int, int, CRGB, CRGB, int);

/**
 * Draw blended gradients between each particle
 */
void blendBetweenParticles() {
  int i, nextI, length;
  for(i=0; i<gNumParticles; i++) {
    nextI = (i+1) % gNumParticles;

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

  for(i=0; i<gNumParticles; i++) {
    leds[particles[i].offset / 16] = particles[i].colour;
  }
}


