// #############################################################################
// #
// # Scriptname : DS1307_Monitor.pde
// # Author     : Oliver Kraus
// # Date       : 21.03.2011
// # License    : cc-by-sa-3.0
// #
// # Description:
// # Inspection and monitoring tool for the DS1307 hardware
// # 
// #############################################################################
// *********************************************
// INCLUDE
// *********************************************
#include <Wire.h>                       // For some strange reasons, Wire.h must be included here
#include <DS1307new.h>

// *********************************************
// DEFINE
// *********************************************

// *********************************************
// VARIABLES
// *********************************************

#define MON_BUF_LEN 128

char mon_buf[MON_BUF_LEN];
uint8_t mon_buf_cnt = 0;
char *mon_curr;

uint8_t mon_is_date;
uint16_t mon_year;
uint8_t mon_month;
uint8_t mon_day;

uint8_t mon_is_time;
uint8_t mon_hour;
uint8_t mon_minute;
uint8_t mon_second;

/*
  1:	missing '-' after year ("yyyy-mm-dd")
  2:	missing '-' after month ("yyyy-mm-dd")
  3:	month not within 1..12
  4:	day not within 1..31
  5:	missing ':' after hour ("hh:mm")
  6:	hour not within 0..23
  7:	minute not within 0..59
  8:	second not within 0..59
*/
uint8_t mon_error;


// *********************************************
// PARSER
// *********************************************

void mon_skip_space(void)
{
  for(;;)
  {
    if ( *mon_curr == '\0' )
      break;
    if ( *mon_curr > ' ')
      break;    
    mon_curr++;
  }
}

uint16_t mon_get_value(void)
{
  uint16_t v = 0;
  uint8_t c;
  for(;;)
  {
    if ( *mon_curr >= '0' && *mon_curr <= '9' )
    {  
      c = *mon_curr;
      c -= '0';
      v *= 10;
      v += c;
      mon_curr++;
    }
    else
      break;
  }
  mon_skip_space();
  return v;
}

uint8_t mon_check(char c)
{
  if ( *mon_curr != c ) 
    return 0;
  mon_curr++;
  mon_skip_space();
  return 1;
}

/*
  yyyy-mm-dd  
*/
uint8_t mon_get_date(void)
{
  mon_year = mon_get_value();
  if ( mon_year < 100 )
    mon_year += 2000;
  if ( mon_check('-') == 0 )
  {
    mon_error = 1;
    return 0;
  }
  mon_month = mon_get_value();
  if ( mon_month == 0 || mon_month > 12 ) 
  {
    mon_error = 3;
    return 0;
  }
  if ( mon_check('-') == 0 )
  {
    mon_error = 2;
    return 0;
  }
  mon_day = mon_get_value();
  if ( mon_day == 0 || mon_day > 31 ) 
  {
    mon_error = 4;
    return 0;
  }
  mon_is_date = 1;
  return 1;
}

/*
  hh:mm
  hh:mm:ss
*/
uint8_t mon_get_time(void)
{
  mon_second = 0;
  mon_hour = mon_get_value();
  if ( mon_hour > 23 ) 
  {
    mon_error = 6;
    return 0;
  }
  if ( mon_check(':') == 0 )
  {
    mon_error = 5;
    return 0;
  }
  mon_minute = mon_get_value();
  if ( mon_minute > 59 ) 
  {
    mon_error = 7;
    return 0;
  }
  if ( mon_check(':') == 0 ) 
  {
    mon_is_time = 1;
    return 1;
  }
  mon_second = mon_get_value();
  if ( mon_second > 59 ) 
  {
    mon_error = 8;
    return 0;
  }
  mon_is_time = 1;
  return 1;
}


/*
  yyyy-mm-dd hh:mm:ss  
*/

uint8_t mon_get_date_time(void)
{
  char *mon_ptr;
  uint16_t v;
  
  mon_is_date = 0;
  mon_year = 2000;
  mon_month = 1;
  mon_day = 1;

  mon_is_time = 0;
  mon_hour = 0;
  mon_minute = 0;
  mon_second = 0;
  
  
  for(;;)
  {
    mon_ptr = mon_curr;
    v = mon_get_value();
    if ( mon_check(':') != 0 )
    {
      mon_curr = mon_ptr;
      if ( mon_get_time() == 0 )
	return 0;
    }
    else if ( mon_check('-') != 0 )
    {
      mon_curr = mon_ptr;
      if ( mon_get_date() == 0 )
	return 0;
    }
    else
      break;
  }
  return 1;
}

void mon_help(void)
{
  Serial.println("Available commands:");
  Serial.println("i          read and display current date and time");
  Serial.println("s <d> <t>  set date <d> and/or time <t>");
  Serial.println("l          list clock NVRAM");
  Serial.println("d          print daylight saving date (Europa)");
  Serial.println("m <a> <v>  write value <v> to NVRAM location <a>");
  Serial.println("h          this help");
}

void mon_print_error(void)
{
  Serial.print("Errorcode: ");
  Serial.println(mon_error, DEC);
}

void mon_print_2d(uint8_t v)
{
  if ( v < 10 )
    Serial.print("0");
  Serial.print(v, DEC);
}

void mon_print_3d(uint8_t v)
{
  if ( v < 10 )
    Serial.print(" ");
  if ( v < 100 )
    Serial.print(" ");
  Serial.print(v, DEC);
}

void mon_print_date(uint16_t y, uint8_t m, uint8_t d)
{
    Serial.print(y, DEC);
    Serial.print("-");
    mon_print_2d(m);
    Serial.print("-");
    mon_print_2d(d);
}

void mon_print_time(uint16_t h, uint8_t m, uint8_t s)
{
    mon_print_2d(h);
    Serial.print(":");
    mon_print_2d(m);
    Serial.print(":");
    mon_print_2d(s);
}
  
void mon_info(void)
{
  char wd[7][3] = { "So", "Mo", "Tu", "We", "Th", "Fr", "Sa" };
  RTC.getTime();
  Serial.print("RTC date: ");
  mon_print_date(RTC.year, RTC.month, RTC.day);
  Serial.print(" ");
  Serial.print(wd[RTC.dow]);
  Serial.print("  time: ");
  mon_print_time(RTC.hour, RTC.minute, RTC.second);
  Serial.println(""); 
  Serial.print(RTC.cdn, DEC);
  Serial.print(" days or ");
  Serial.print(RTC.time2000, DEC);
  Serial.println(" seconds since 2000-01-01 00:00:00");
}

void mon_dst(void)
{
  long m;
  uint8_t isSummerTime;
  uint16_t i;
  
  m = millis();
  for( i = 0; i < 1000; i++ )
    isSummerTime = RTC.isMEZSummerTime();
  m = millis() - m;
  
  Serial.print("Result from isMEZSummerTime(): ");
  Serial.print(isSummerTime, DEC); 
  Serial.print(" (");
  Serial.print(m, DEC); 
  Serial.print("ns + ");

  m = millis();
  for( i = 0; i < 1000; i++ )
    RTC.fillByTime2000(RTC.time2000);			// speed measue
  m = millis() - m;
  Serial.print(m, DEC); 
  Serial.println("us)");
  
  m = millis();
  RTC.fillByYMD(RTC.year, 4, 1);		// first of April
  if ( RTC.dow == 0 )
    RTC.fillByCDN(RTC.cdn - 7);			// sunday before 
  else
    RTC.fillByCDN(RTC.cdn - RTC.dow);	// sunday before
  m = millis() - m;
  Serial.print("Summer time (turn forward the clock): ");
  mon_print_date(RTC.year, RTC.month, RTC.day);
  Serial.print(" (");
  Serial.print(RTC.cdn, DEC);
  Serial.print(" days or ");
  Serial.print(RTC.time2000, DEC);
  Serial.print(" seconds since 2000-01-01 00:00:00)");

  Serial.println(""); 
  
  RTC.fillByYMD(RTC.year, 11, 1);		// first of november
  if ( RTC.dow == 0 )
    RTC.fillByCDN(RTC.cdn - 7);			// sunday before 
  else
    RTC.fillByCDN(RTC.cdn - RTC.dow);	// sunday before 
  Serial.print("Winter time (turn back the clock): ");
  mon_print_date(RTC.year, RTC.month, RTC.day);
  Serial.print(" (");
  Serial.print(RTC.cdn, DEC);
  Serial.print(" days or ");
  Serial.print(RTC.time2000, DEC);
  Serial.print(" seconds since 2000-01-01 00:00:00)");
}



void mon_set_date_time(void)
{
  if ( mon_get_date_time() == 0 )
  {
    mon_print_error();
    return;
  }    
  RTC.getTime();
  Serial.print("Assign ");
  if ( mon_is_date != 0 )
  {
    mon_print_date(mon_year, mon_month, mon_day);
    Serial.print(" ");
    RTC.fillByYMD(mon_year, mon_month, mon_day);
  }
  if ( mon_is_time != 0 )
  {
    mon_print_time(mon_hour, mon_minute, mon_second);
    Serial.print(" ");
    RTC.fillByHMS(mon_hour, mon_minute, mon_second);
  }
  RTC.setTime();
  RTC.startClock();
  Serial.println("to RTC");
}

void mon_list(void)
{
  uint8_t i, addr;
  uint8_t ram[8];
  
  for( addr = 0; addr < 56; addr+= 8 )
  {
    RTC.getRAM(addr, ram, 8);
    mon_print_3d(addr);
    Serial.print(": ");
    for( i = 0; i < 8; i++ )
    {
      mon_print_3d(ram[i]);
      Serial.print(" ");
    }
    Serial.println("");
  }
}

void mem_memory(void)
{
    uint8_t a, m;
    a = mon_get_value();
    m = mon_get_value();
    Serial.print("Write ");
    Serial.print(m, DEC);
    Serial.print(" to memory location ");
    Serial.println(a, DEC);
    RTC.setRAM(a, &m, 1);
}


void mon_cmd(void)
{
  mon_skip_space();
  if ( *mon_curr == '\0' )
    return;
  if ( mon_check('?') )
    mon_help();
  else if ( mon_check('h') )
    mon_help();
  else if ( mon_check('s') )
    mon_set_date_time();
  else if ( mon_check('i') )
    mon_info();
  else if ( mon_check('l') )
    mon_list();
  else if ( mon_check('m') )
    mem_memory();
  else if ( mon_check('d') )
    mon_dst();
  else
    ;
    
}



// *********************************************
// SETUP
// *********************************************
void setup()
{
  delay(1000);
  pinMode(2, INPUT);                    // Test of the SQW pin, D2 = INPUT
  digitalWrite(2, HIGH);                // Test of the SQW pin, D2 = Pullup on
  Serial.begin(9600);
  Serial.println("DS1307 Monitor (enable LF/CR, type 'h' for help)");
  Serial.println();
}

// *********************************************
// EXEC
// *********************************************

void exec(void)
{
  Serial.println(mon_buf);
  mon_curr = mon_buf;
  mon_cmd();
}


// *********************************************
// LED flashing
// *********************************************
uint8_t LED_state = 0;
uint32_t LED_next_change = 0L;
uint32_t LED_on_time = 100L;
uint32_t LED_off_time = 1000L;

void LED_flashing(void)
{
  if ( LED_next_change < millis() )
  {
    if ( LED_state == 0 )
    {
      LED_next_change = millis() + LED_on_time;
      LED_state = 1;
    }
    else
    {
      LED_next_change = millis() + LED_off_time;
      LED_state = 0;
    }
    digitalWrite(13, LED_state);    
  }
}

// *********************************************
// MAIN (LOOP)
// *********************************************
void loop()
{  
  LED_flashing();
  
  if ( RTC.isPresent() == 0 )
    LED_off_time = 100L;                // fast flashing if device is not available
  
  if ( Serial.available() )
  {
    char c;
    c = Serial.read();
    if ( mon_buf_cnt >= MON_BUF_LEN-1 || c == '\n' || c == '\r'  )
    {
      exec();
      mon_buf_cnt = 0;
      mon_buf[mon_buf_cnt] = '\0';
    }
    else
    {
      mon_buf[mon_buf_cnt] = c;
      mon_buf_cnt++;
      mon_buf[mon_buf_cnt] = '\0';
    }
  }
}

