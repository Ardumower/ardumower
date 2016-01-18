/*
  Ping Example
 
 This example sends an ICMP pings every 500 milliseconds, sends the human-readable
 result over the serial port. 

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 
 created 30 Sep 2010
 by Blake Foster
 
 */

#include <SPI.h>         
#include <Ethernet.h>
#include <ICMPPing.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; // max address for ethernet shield
byte ip[] = {192,168,2,177}; // ip address for ethernet shield
IPAddress pingAddr(74,125,26,147); // ip address to ping

SOCKET pingSocket = 0;

char buffer [256];
ICMPPing ping(pingSocket, (uint16_t)random(0, 255));

void setup() 
{
  // start Ethernet
  Ethernet.begin(mac, ip);
  Serial.begin(9600);
}

void loop()
{
  ICMPEchoReply echoReply = ping(pingAddr, 4);
  if (echoReply.status == SUCCESS)
  {
    sprintf(buffer,
            "Reply[%d] from: %d.%d.%d.%d: bytes=%d time=%ldms TTL=%d",
            echoReply.data.seq,
            echoReply.addr[0],
            echoReply.addr[1],
            echoReply.addr[2],
            echoReply.addr[3],
            REQ_DATASIZE,
            millis() - echoReply.data.time,
            echoReply.ttl);
  }
  else
  {
    sprintf(buffer, "Echo request failed; %d", echoReply.status);
  }
  Serial.println(buffer);
  delay(500);
}










