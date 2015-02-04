#include "common.h"


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


