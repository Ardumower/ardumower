/*
 * Copyright (c) 2010 by Blake Foster <blfoster@vassar.edu>
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#include <SPI.h>
#include <Ethernet.h>
#include <utility/w5100.h>

#define REQ_DATASIZE 64
#define ICMP_ECHOREPLY 0
#define ICMP_ECHOREQ 8
#define ICMP_ECHOREP 0
#define TIME_EXCEEDED 11
#define PING_TIMEOUT 1000

typedef unsigned long time_t;

class ICMPHeader;
class ICMPPing;

typedef enum Status
{
    /*
    Indicates whether a ping succeeded or failed due to one of various error
    conditions. These correspond to error conditions that occur in this
    library, not anything defined in the ICMP protocol.
    */
    SUCCESS = 0,
    SEND_TIMEOUT = 1, // Timed out sending the request
    NO_RESPONSE = 2, // Died waiting for a response
    BAD_RESPONSE = 3 // we got back the wrong type
};


struct ICMPHeader
{
    /*
    Header for an ICMP packet. Does not include the IP header.
    */
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
};


struct ICMPEcho
{
    /*
    Contents of an ICMP echo packet, including the ICMP header. Does not
    include the IP header.
    */

    /*
    This constructor sets all fields and calculates the checksum. It is used
    to create ICMP packet data when we send a request.
    @param type: ICMP_ECHOREQ or ICMP_ECHOREP.
    @param _id: Some arbitrary id. Usually set once per process.
    @param _seq: The sequence number. Usually started at zero and incremented
    once per request.
    @param payload: An arbitrary chunk of data that we expect to get back in
    the response.
    */
    ICMPEcho(uint8_t type, uint16_t _id, uint16_t _seq, uint8_t * _payload);

    /*
    This constructor leaves everything zero. This is used when we receive a
    response, since we nuke whatever is here already when we copy the packet
    data out of the W5100.
    */
    ICMPEcho();

    ICMPHeader icmpHeader;
    uint16_t id;
    uint16_t seq;
    time_t time;
    uint8_t payload [REQ_DATASIZE];

    /*
    Serialize the header as a byte array, in big endian format.
    */
    void serialize(byte * binData) const;
    /*
    Serialize the header as a byte array, in big endian format.
    */
    void deserialize(byte const * binData);
};


struct ICMPEchoReply
{
    /*
    Struct returned by ICMPPing().
    @param data: The packet data, including the ICMP header.
    @param ttl: Time to live
    @param status: SUCCESS if the ping succeeded. One of various error codes
    if it failed.
    @param addr: The ip address that we received the response from. Something
    is borked if this doesn't match the IP address we pinged.
    */
    ICMPEcho data;
    uint8_t ttl;
    Status status;
    IPAddress addr;
};


class ICMPPing
{
    /*
    Function-object for sending ICMP ping requests.
    */

public:
    /*
    Construct an ICMP ping object.
    @param socket: The socket number in the W5100.
    @param id: The id to put in the ping packets. Can be pretty much any
    arbitrary number.
    */
    ICMPPing(SOCKET s, uint8_t id);

    /*
    Pings the given IP address.
    @param addr: IP address to ping, as an array of four octets.
    @param nRetries: Number of times to rety before giving up.
    @return: An ICMPEchoReply containing the response. The status field in
    the return value indicates whether the echo request succeeded or
    failed. If the request failed, the status indicates the reason for
    failure on the last retry.
    */
    ICMPEchoReply operator()(const IPAddress&, int nRetries);

    /*
    This overloaded version of the () operator takes a (hopefully blank)
    ICMPEchoReply as parameter instead of constructing one internally and
    then copying it on return. This creates a very small improvement in
    efficiency at the cost of making your code uglier.
    @param addr: IP address to ping, as an array of four octets.
    @param nRetries: Number of times to rety before giving up.
    @param result: ICMPEchoReply that will hold the result.
    */
    void operator()(const IPAddress& addr, int nRetries, ICMPEchoReply& result);

private:

    Status sendEchoRequest(const IPAddress& addr, const ICMPEcho& echoReq);
    void receiveEchoReply(const ICMPEcho& echoReq, const IPAddress& addr, ICMPEchoReply& echoReply);

    uint8_t _id;
    uint8_t _nextSeq;
    SOCKET _socket;
};

#pragma pack(1)
