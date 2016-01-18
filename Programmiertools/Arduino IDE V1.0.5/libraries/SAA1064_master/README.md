cool-SAA1064-lib
================

The 'Cool SAA1064 lib' driving the NXP SAA1064 IC
as an arduino library in a comfortable way ...

Example code:

SAA1064 saa1064; // generate an object
saa1064.scollCooLSAA1064( ); // shows functionality

Features are:

- select IC's internal test mode switching on all segments
- select mode for two or four digits
- select the intensity of the segments by dark, normal, bright
- select the intensity of the segments by an integer 1 .. 7 
- display a number by 0 to 9999 as integer; blank not used
- display a number by 0000 to 9999 as integer; not blanking
- display hex values 0000 to FFFF as integer 0 .. 15
- display letters by an interal code 16 .. following
- display a digit as integer on a selected segment as update
- display a digit as byte on a selected segment as update
- display a digit on a selected segment as register update
- display four digits seperately as integer or blank by -1
- display four digits seperately as bytes
- display one of a predefined word; CooL, Foo, bAr, ...
- display a predefined smiley; 8-]
- display the time directly
- display the date and the date in US and year
- scroll any integer or internal codes by milliseconds per step
- scroll time by 'hour-minute-second' from right to left
- scroll date by 'day-month-year' from right to left
- display an amplitude from right to left by an integer of 0 .. 7
- display all possible letters that are stored internal
- display all byte coding over all segments; takes time!

All necessary I2C communications are realized by only three methods:
- _set( .. ); // once
- _say( .. ); // two times
