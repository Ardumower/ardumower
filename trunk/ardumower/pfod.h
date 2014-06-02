// Arduino robot mower
// Copyright (c) 2013 by Alexander Grau
//
// Android remote control (pfod App)

#ifndef PFOD_H
#define PFOD_H

#include <Arduino.h>

// pfodApp state
enum { PFOD_OFF, PFOD_MENU, PFOD_MONITOR, PFOD_ARDU_MAG,
       PFOD_PLOT_BAT, PFOD_PLOT_ODO, PFOD_PLOT_IMU, PFOD_PLOT_SENSOR_COUNTERS, PFOD_PLOT_SENSORS, PFOD_PLOT_PERIMETER, PFOD_PLOT_GPS };


void initSerialPfod(int baudrate);
void readSerialPfod();
void pfodLoop();


#endif

