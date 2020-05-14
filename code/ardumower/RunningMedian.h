//
//    FILE: RunningMedian.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
// PURPOSE: RunningMedian library for Arduino
// VERSION: 0.1.13
//     URL: http://arduino.cc/playground/Main/RunningMedian
// HISTORY: See RunningMedian.cpp
//
// Released to the public domain
//

#ifndef RunningMedian_h
#define RunningMedian_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <inttypes.h>

#define RUNNING_MEDIAN_VERSION "0.1.13"

// prepare for dynamic version
// not tested use at own risk :)
// #define RUNNING_MEDIAN_USE_MALLOC

// conditional compile to minimize lib
// by removeing a lot of functions.
#define RUNNING_MEDIAN_ALL


// should at least be 5 to be practical
// odd size results in a 'real' middle element.
// even size takes the lower of the two middle elements
#define MEDIAN_MIN_SIZE     1
#define MEDIAN_MAX_SIZE     19          // adjust if needed


class RunningMedian
{
public:
    explicit RunningMedian(const uint8_t size); // # elements in the internal buffer
    ~RunningMedian();

    /** resets internal buffer and var */
    void clear();

    /** adds a new value to internal buffer, optionally replacing the oldest element. */
    void add(const double value);

    /** returns the median == middle element */
    double getMedian();

#ifdef RUNNING_MEDIAN_ALL
    /** returns average of the values in the internal buffer */
    double getAverage() const;

    /** returns average of the middle nMedian values, removes noise from outliers */
    double getAverage(uint8_t nMedian);

    /** returns highest element */
    double getHighest();

    /** return lowest element */
    double getLowest();

    /** get n'th element from the values in time order */
    double getElement(const uint8_t n) const;

    /** get n'th element from the values in size order */
    double getSortedElement(const uint8_t n);

    /** predict the max change of median after n additions */
    double predict(const uint8_t n);

    /** returns size of internal buffer */
    uint8_t getSize() const;

    /** returns current used elements, getCount() <= getSize() */
    uint8_t getCount() const;
#endif

protected:
    boolean _sorted;
    uint8_t _size;
    uint8_t _cnt;
    uint8_t _idx;

#ifdef RUNNING_MEDIAN_USE_MALLOC
    double * _ar;
    uint8_t * _p;
#else
    double _ar[MEDIAN_MAX_SIZE];
    uint8_t _p[MEDIAN_MAX_SIZE];
#endif
    void sort();
};

#endif
