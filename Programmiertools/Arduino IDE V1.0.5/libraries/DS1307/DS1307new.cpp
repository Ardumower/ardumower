// ###########.read##################################################################
// #
// # Scriptname : DS1307new.cpp
// # Author     : Peter Schmelzer
// # Contributor: Oliver Kraus
// # contact    : info@schmelle2.de
// # Date       : 2010-11-01
// # Version    : 1.00
// # License    : cc-by-sa-3.0
// #
// # Description:
// # The DS1307new Library
// #
// # Naming Convention:
// #	get...	Get information from the DS1307 hardware
// #	set...	Write information to the DS1307 hardware
// #	fill...		Put some information onto the object, but do not access DS1307 hardware
// #
// # Notes on the date calculation procedures
// #  Written 1996/97 by Oliver Kraus
// #  Published by Heinz Heise Verlag 1997 (c't 15/97)
// #  Completly rewritten and put under GPL 2011 by Oliver Kraus
// #
// #############################################################################
// *********************************************
// INCLUDE
// *********************************************
#include "Wire.h"
#include "DS1307new.h"

// *********************************************
// DEFINE
// *********************************************
#define DS1307_ID 0x68

// *********************************************
// Public functions
// *********************************************
DS1307new::DS1307new()
{
  Wire.begin();
}

uint8_t DS1307new::isPresent(void)         // check if the device is present
{
  Wire.beginTransmission(DS1307_ID);
  Wire.write((uint8_t)0x00);
  if (Wire.endTransmission() == 0) return 1;
  return 0;
}

void DS1307new::stopClock(void)         // set the ClockHalt bit high to stop the rtc
{
  Wire.beginTransmission(DS1307_ID);
  Wire.write((uint8_t)0x00);                      // Register 0x00 holds the oscillator start/stop bit
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ID, 1);
  second = Wire.read() | 0x80;       // save actual seconds and OR sec with bit 7 (sart/stop bit) = clock stopped
  Wire.beginTransmission(DS1307_ID);
  Wire.write((uint8_t)0x00);
  Wire.write((uint8_t)second);                    // write seconds back and stop the clock
  Wire.endTransmission();
}

void DS1307new::startClock(void)        // set the ClockHalt bit low to start the rtc
{
  Wire.beginTransmission(DS1307_ID);
  Wire.write((uint8_t)0x00);                      // Register 0x00 holds the oscillator start/stop bit
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ID, 1);
  second = Wire.read() & 0x7f;       // save actual seconds and AND sec with bit 7 (sart/stop bit) = clock started
  Wire.beginTransmission(DS1307_ID);
  Wire.write((uint8_t)0x00);
  Wire.write((uint8_t)second);                    // write seconds back and start the clock
  Wire.endTransmission();
}

// Aquire time from the RTC chip in BCD format and convert it to DEC
void DS1307new::getTime(void)
{
  Wire.beginTransmission(DS1307_ID);
  Wire.write((uint8_t)0x00);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ID, 7);       // request secs, min, hour, dow, day, month, year
  second = bcd2dec(Wire.read() & 0x7f);// aquire seconds...
  minute = bcd2dec(Wire.read());     // aquire minutes
  hour = bcd2dec(Wire.read());       // aquire hours
  dow = bcd2dec(Wire.read());        // aquire dow (Day Of Week)
  dow--;							//  correction from RTC format (1..7) to lib format (0..6). Useless, because it will be overwritten
  day = bcd2dec(Wire.read());       // aquire day
  month = bcd2dec(Wire.read());      // aquire month
  year = bcd2dec(Wire.read());       // aquire year...
  year = year + 2000;                   // ...and assume that we are in 21st century!
  
  // recalculate all other values
  calculate_ydn();
  calculate_cdn();
  calculate_dow();
  calculate_time2000();
}

// Set time to the RTC chip in BCD format
void DS1307new::setTime(void)
{
  Wire.beginTransmission(DS1307_ID);
  Wire.write((uint8_t)0x00);
  Wire.write(dec2bcd(second) | 0x80);   // set seconds (clock is stopped!)
  Wire.write(dec2bcd(minute));           // set minutes
  Wire.write(dec2bcd(hour) & 0x3f);      // set hours (24h clock!)
  Wire.write(dec2bcd(dow+1));              // set dow (Day Of Week), do conversion from internal to RTC format
  Wire.write(dec2bcd(day));             // set day
  Wire.write(dec2bcd(month));            // set month
  Wire.write(dec2bcd(year-2000));             // set year
  Wire.endTransmission();
}

// Aquire data from the CTRL Register of the DS1307 (0x07)
void DS1307new::getCTRL(void)
{
  Wire.beginTransmission(DS1307_ID);
  Wire.write((uint8_t)0x07);                      // set CTRL Register Address
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ID, 1);       // read only CTRL Register
  while(!Wire.available())
  {
    // waiting
  }
  ctrl = Wire.read();                // ... and store it in ctrl
}

// Set data to CTRL Register of the DS1307 (0x07)
void DS1307new::setCTRL(void)
{
  Wire.beginTransmission(DS1307_ID);
  Wire.write((uint8_t)0x07);                      // set CTRL Register Address
  Wire.write((uint8_t)ctrl);                      // set CTRL Register
  Wire.endTransmission();
}

// Aquire data from RAM of the RTC Chip (max 56 Byte)
void DS1307new::getRAM(uint8_t rtc_addr, uint8_t * rtc_ram, uint8_t rtc_quantity)
{
  Wire.beginTransmission(DS1307_ID);
  rtc_addr &= 63;                       // avoid wrong adressing. Adress 0x08 is now address 0x00...
  rtc_addr += 8;                        // ... and address 0x3f is now 0x38
  Wire.write(rtc_addr);                  // set CTRL Register Address
  if ( Wire.endTransmission() != 0 )
    return;
  Wire.requestFrom(DS1307_ID, (int)rtc_quantity);
  while(!Wire.available())
  {
    // waiting
  }
  for(int i=0; i<rtc_quantity; i++)     // Read x data from given address upwards...
  {
    rtc_ram[i] = Wire.read();        // ... and store it in rtc_ram
  }
}

// Write data into RAM of the RTC Chip
void DS1307new::setRAM(uint8_t rtc_addr, uint8_t * rtc_ram, uint8_t rtc_quantity)
{
  Wire.beginTransmission(DS1307_ID);
  rtc_addr &= 63;                       // avoid wrong adressing. Adress 0x08 is now address 0x00...
  rtc_addr += 8;                        // ... and address 0x3f is now 0x38
  Wire.write(rtc_addr);                  // set RAM start Address 
  for(int i=0; i<rtc_quantity; i++)     // Send x data from given address upwards...
  {
    Wire.write(rtc_ram[i]);              // ... and send it from rtc_ram to the RTC Chip
  }
  Wire.endTransmission();
}

/*
  Variable updates:
    cdn, ydn, year, month, day
*/
void DS1307new::fillByCDN(uint16_t _cdn)
{
  uint16_t y, days_per_year;
  cdn = _cdn;
  y = 2000;
  for(;;)
  {
    days_per_year = 365;
    days_per_year += is_leap_year(y);
    if ( _cdn >= days_per_year )
    {
      _cdn -= days_per_year;
      y++;
    }
    else
      break;
  }
  _cdn++;
  year = y;
  ydn = _cdn;
  calculate_dow();
  calculate_month_by_year_and_ydn();
  calculate_day_by_month_year_and_ydn();
  calculate_time2000();
}

/*
  Variable updates:
    time2000, cdn, ydn, year, month, day, hour, minute, second
*/
void DS1307new::fillByTime2000(uint32_t _time2000)
{
  time2000 = _time2000;
  second = _time2000 % 60;
  _time2000 /= 60;
  minute = _time2000 % 60;
  _time2000 /= 60;
  hour = _time2000 % 24;
  _time2000 /= 24;
  fillByCDN(_time2000);
}

void DS1307new::fillByHMS(uint8_t h, uint8_t m, uint8_t s)
{
  // assign variables
  hour = h;
  minute = m;
  second = s;
  // recalculate seconds since 2000-01-01
  calculate_time2000();
}

void DS1307new::fillByYMD(uint16_t y, uint8_t m, uint8_t d)
{
  // assign variables
  year = y;
  month = m;
  day = d;
  // recalculate depending values
  calculate_ydn();
  calculate_cdn();
  calculate_dow();
  calculate_time2000();
}

// check if current time is european summer time
uint8_t DS1307new::isMEZSummerTime(void)
{
  uint32_t current_time, summer_start, winter_start;
  current_time = time2000;
  
  // calculate start of summer time
  fillByYMD(year, 3, 30);
  fillByHMS(2,0,0);
  fillByCDN(RTC.cdn - RTC.dow);	// sunday before
  summer_start = time2000;
  
  // calculate start of winter
  fillByYMD(year, 10, 31);
  fillByHMS(3,0,0);
  fillByCDN(RTC.cdn - RTC.dow);	// sunday before
  winter_start = time2000;
  
  // restore time
  fillByTime2000(current_time);
  
  // return result
  if ( summer_start <= current_time && current_time < winter_start )
    return 1;
  return 0;  
}


// *********************************************
// Private functions
// *********************************************
// Convert Decimal to Binary Coded Decimal (BCD)
uint8_t DS1307new::dec2bcd(uint8_t num)
{
  return ((num/10 * 16) + (num % 10));
}

// Convert Binary Coded Decimal (BCD) to Decimal
uint8_t DS1307new::bcd2dec(uint8_t num)
{
  return ((num/16 * 10) + (num % 16));
}

/*
  Prototype:
    uint8_t DS1307new::is_leap_year(uint16_t y)
  Description:
    Calculate leap year
  Arguments:
    y   		year, e.g. 2011 for year 2011
  Result:
    0           not a leap year
    1           leap year
*/
uint8_t DS1307new::is_leap_year(uint16_t y)
{
  //uint16_t y = year;
   if ( 
          ((y % 4 == 0) && (y % 100 != 0)) || 
          (y % 400 == 0) 
      )
      return 1;
   return 0;
}

/*
  Prototype:
    void calculate_ydn(void)
  Description:
    Calculate the day number within a year. 1st of Jan has the number 1.
    "Robertson" Algorithm
  Arguments:
    this->year           	year, e.g. 2011 for year 2011
    this->month         	month with 1 = january to 12 = december
    this->day          	day starting with 1
  Result:
    this->ydn		The "day number" within the year: 1 for the 1st of Jan.

*/
void DS1307new::calculate_ydn(void)
{
  uint8_t tmp1; 
  uint16_t tmp2;
  tmp1 = 0;
  if ( month >= 3 )
    tmp1++;
  tmp2 = month;
  tmp2 +=2;
  tmp2 *=611;
  tmp2 /= 20;
  tmp2 += day;
  tmp2 -= 91;
  tmp1 <<=1;
  tmp2 -= tmp1;
  if ( tmp1 != 0 )
    tmp2 += is_leap_year(year);
  ydn = tmp2;
}

/*
  Prototype:
    uint16_t to_century_day_number(uint16_t y, uint16_t ydn)
  Description:
    Calculate days since January, 1st, 2000
  Arguments:
    this->y           year, e.g. 2011 for year 2011
    this->ydn	year day number (1st of Jan has the number 1)
  Result
    this->cdn	days since 2000-01-01 (2000-01-01 has the cdn 0)
*/
void DS1307new::calculate_cdn(void)
{
  uint16_t y = year;
  cdn = ydn;
  cdn--;
  while( y > 2000 )
  {
    y--;
    cdn += 365;
    cdn += is_leap_year(y);
  }
}

/*
  calculate day of week (dow)
  0 = sunday .. 6 = saturday
  Arguments:
    this->cdn	days since 2000-01-01 (2000-01-01 has the cdn 0 and is a saturday)
*/
void DS1307new::calculate_dow(void)
{
  uint16_t tmp;
  tmp = cdn;
  tmp += 6;
  tmp %= 7;
  dow = tmp;
}

/*
  Calculate the seconds after 2000-01-01 00:00. The largest possible
  time is 2136-02-07 06:28:15
  Arguments:
    this->h         hour
    this->m	minutes
    this->s		seconds
    this->cdn	days since 2000-01-01 (2000-01-01 has the cdn 0)
*/
void DS1307new::calculate_time2000(void)
{
  uint32_t t;
  t = cdn;
  t *= 24;
  t += hour;
  t *= 60;
  t += minute;
  t *= 60;
  t += second;
  time2000 = t;
}


uint16_t DS1307new::_corrected_year_day_number(void)
{
   uint8_t a;
   uint16_t corrected_ydn = ydn;
   a = is_leap_year(year);
   if ( corrected_ydn > (uint8_t)(((uint8_t)59)+a) )
   {
      corrected_ydn += 2;
      corrected_ydn -= a;
   }
   corrected_ydn += 91;
   return corrected_ydn;
}

/*
  Variables reads:
    ydn, year 
  Variable updates:
    month
*/
void DS1307new::calculate_month_by_year_and_ydn(void)
{
  uint8_t a;
  uint16_t c_ydn;
  c_ydn = _corrected_year_day_number();
  c_ydn *= 20;
  c_ydn /= 611;
  a = c_ydn;
  a -= 2;
  month = a;  
}

/*
  Variables reads:
    ydn, year, month
  Variable updates:
    day
*/
void DS1307new::calculate_day_by_month_year_and_ydn(void)
{
  uint8_t m;
  uint16_t tmp, c_ydn;
  m = month;
  m += 2;
  c_ydn = _corrected_year_day_number();
  tmp = 611;
  tmp *= m;
  tmp /= 20;
  c_ydn -= tmp;
  day = c_ydn;
}




// *********************************************
// Define user object
// *********************************************
class DS1307new RTC;
