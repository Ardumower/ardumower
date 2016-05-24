#include "common.h"
#include <math.h>
#include <cstdlib>


float distance(float x1, float y1, float x2, float y2){
  return sqrtf( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );
}

float random(){
  return (float)rand()/(float)(RAND_MAX);
}

/*
 * Returns random number in normal distribution centering on 0.
 * ~95% of numbers returned should fall between -2 and 2
 */
float gaussRandom() {
    //printf("random=%3.3f\n", random());
    float u = 2*random()-1;
    float v = 2*random()-1;
    float r = u*u + v*v;
    /*if outside interval [0,1] start over*/
    if ((r == 0) || (r > 1)) return gaussRandom();

    float c = sqrt(-2*log(r)/r);
    return u*c;

    /* todo: optimize this algorithm by caching (v*c)
     * and returning next time gaussRandom() is called.
     * left out for simplicity */
}

/*
 * Returns member of set with a given mean and standard deviation
 * mean: mean
 * standard deviation: std_dev
 */
float gauss(float mean, float std_dev){
    return mean + (gaussRandom()*std_dev);
}

// calculates the probability of x for 1-dim Gaussian with mean mu and var. sigma
float gaussian(float mu, float sigma, float x)
{
  return exp(-   pow(mu - x, 2) / pow(sigma,  2) / 2.0     )
              / sqrt(2.0 * M_PI * pow(sigma, 2));
}


// rescale to -PI..+PI
float scalePI(float v)
{
  double d = v;
  while (d < 0) d+=2*M_PI;
  while (d >= 2*M_PI) d-=2*M_PI;
  if (d >= M_PI) return (-2*M_PI+d);
  else if (d < -M_PI) return (2*M_PI+d);
  else return d;
}

// computes minimum distance between x radiant (current-value) and w radiant (set-value)
float distancePI(float x, float w)
{
  // cases:
  // w=330 degree, x=350 degree => -20 degree
  // w=350 degree, x=10  degree => -20 degree
  // w=10  degree, x=350 degree =>  20 degree
  // w=0   degree, x=190 degree => 170 degree
  // w=190 degree, x=0   degree => -170 degree
  float d = scalePI(w - x);
  if (d < -M_PI) d = d + 2*M_PI;
  else if (d > M_PI) d = d - 2*M_PI;
  return d;
}


