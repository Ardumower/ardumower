/*
  Ardumower (www.ardumower.de)
  Copyright (c) 2013-2014 by Alexander Grau
  Copyright (c) 2013-2014 by Sven Gennat
 
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

*/

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

