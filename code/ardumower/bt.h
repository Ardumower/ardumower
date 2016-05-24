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

#ifndef BT_H
#define BT_H

#include <Arduino.h>


/*
  BT automatic programmer
   *linvor
   *HC03/04/05/06
   *ModiaTek FBT06/MBTV4 

 NOTE for HC05:           Connect KEY pin to 3.3V!
 NOTE for HC06/linvor:    Do NOT pair/connect (LED must be blinking)
 NOTE for FBT06/MBTV4:    First you have to solder the PIO11 pin to VCC (PIN 12) which is 3.3 Volts using a thin wire.
*/

class BluetoothConfig
{
  public:
    BluetoothConfig();
    void setParams(String name, int pin, long baudrate, boolean quickBaudScan);
  private:
    void setConfigs(byte *config);
    void writeBT(String s);
    void readBT();
    void writeReadBT(String s);
    void setName(String name);    
    void setPin(int pin);
    void setBaudrate(long rate);
    boolean detectBaudrate(boolean quickBaudScan);
    void detectModuleType();
    byte btTestConfig[24];
    byte btConfig;
    char btType;
    char btData;
    String btResult;
    long btRate;  
};




#endif

