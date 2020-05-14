/*
  Ardumower (www.ardumower.de)
  Copyright (c) 2013-2014 by Alexander Grau
  Copyright (c) 2013-2014 by Sven Gennat

  Private-use only! (you need to ask for a commercial-use)

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  Private-use only! (you need to ask for a commercial-use)

*/

//  GPS neo6m  (NMEA-0183 protocol)


#ifndef GPS_H
#define GPS_H

#include "Arduino.h"

#define MPH_PER_KNOT 1.15077945
#define MPS_PER_KNOT 0.51444444
#define KMH_PER_KNOT 1.852
#define MILES_PER_METER 0.00062137112
#define KM_PER_METER 0.001
// #define _GPS_NO_STATS

enum {
    GPS_INVALID_AGE = 0xFFFFFFFF,
    GPS_INVALID_ANGLE = 999999999,
    GPS_INVALID_ALTITUDE = 999999999,
    GPS_INVALID_DATE = 0,
    GPS_INVALID_TIME = 0xFFFFFFFF,
    GPS_INVALID_SPEED = 999999999,
    GPS_INVALID_FIX_TIME = 0xFFFFFFFF,
    GPS_INVALID_SATELLITES = 0xFF,
    GPS_INVALID_HDOP = 0xFFFFFFFF
};

static const float GPS_INVALID_F_ANGLE = 1000.0;
static const float GPS_INVALID_F_ALTITUDE = 1000000.0;
static const float GPS_INVALID_F_SPEED = -1.0;

class GPS
{
public:
    GPS();
    bool encode(char c); // process one character received from GPS
    void init();
    boolean feed();
    GPS & operator << (char c) {
        encode(c);
        return *this;
    }

    /** lat/long in hundred thousandths of a degree and age of fix in milliseconds */
    void get_position(long * latitude, long * longitude, unsigned long * fix_age = 0) const;

    /** date as ddmmyy, time as hhmmsscc, and age in milliseconds */
    void get_datetime(unsigned long * date, unsigned long * time, unsigned long * age = 0) const;

    /** signed altitude in centimeters (from GPGGA sentence) */
    inline long altitude() const {
        return _altitude;
    }

    /** course in last full GPRMC sentence in 100th of a degree */
    inline unsigned long course() const {
        return _course;
    }

    /** speed in last full GPRMC sentence in 100ths of a knot */
    inline unsigned long speed() const {
        return _speed;
    }

    /** satellites used in last full GPGGA sentence */
    inline unsigned short satellites() const {
        return _numsats;
    }

    /** horizontal dilution of precision in 100ths */
    inline unsigned long hdop() const {
        return _hdop;
    }

    void f_get_position(float * latitude, float * longitude, unsigned long * fix_age = 0) const;
    void crack_datetime(int * year, byte * month, byte * day,
                        byte * hour, byte * minute, byte * second, byte * hundredths = 0, unsigned long * fix_age = 0) const;
    float f_altitude() const;
    float f_course() const;
    float f_speed_knots() const;
    float f_speed_mph() const;
    float f_speed_mps() const;
    float f_speed_kmph() const;

    //static int library_version() { return _GPS_VERSION; }

    static float distance_between (float lat1, float long1, float lat2, float long2);
    static float course_to (float lat1, float long1, float lat2, float long2);
    static const char * cardinal(float course);

#ifndef _GPS_NO_STATS
    void stats(unsigned long * chars, unsigned short * good_sentences, unsigned short * failed_cs);
#endif

private:
    enum {_GPS_SENTENCE_GPGGA, _GPS_SENTENCE_GPRMC, _GPS_SENTENCE_OTHER};

    // properties
    unsigned long _time{GPS_INVALID_TIME}, _new_time;
    unsigned long _date{GPS_INVALID_DATE}, _new_date;
    long _latitude{GPS_INVALID_ANGLE}, _new_latitude;
    long _longitude{GPS_INVALID_ANGLE}, _new_longitude;
    long _altitude{GPS_INVALID_ALTITUDE}, _new_altitude;
    unsigned long _speed{GPS_INVALID_SPEED}, _new_speed;
    unsigned long _course{GPS_INVALID_ANGLE}, _new_course;
    unsigned long _hdop{GPS_INVALID_HDOP}, _new_hdop;
    unsigned short _numsats{GPS_INVALID_SATELLITES}, _new_numsats;

    unsigned long _last_time_fix{GPS_INVALID_FIX_TIME}, _new_time_fix;
    unsigned long _last_position_fix{GPS_INVALID_FIX_TIME}, _new_position_fix;

    // parsing state variables
    byte _parity{0};
    bool _is_checksum_term{false};
    char _term[15];
    byte _sentence_type{_GPS_SENTENCE_OTHER};
    byte _term_number{0};
    byte _term_offset{0};
    bool _gps_data_good{false};

#ifndef _GPS_NO_STATS
    // statistics
    unsigned long _encoded_characters{0};
    unsigned short _good_sentences{0};
    unsigned short _failed_checksum{0};
    unsigned short _passed_checksum;
#endif

    // internal utilities
    int from_hex(char a);
    unsigned long parse_decimal();
    unsigned long parse_degrees();
    bool term_complete();
    bool gpsisdigit(char c) {
        return c >= '0' && c <= '9';
    }
    long gpsatol(const char * str);
    int gpsstrcmp(const char * str1, const char * str2);
};


#endif
