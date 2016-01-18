/*
 * Copyright (c) 2010 by Blake Foster <blfoster@vassar.edu>
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#include "ICMPPing.h"
#include <util.h>

inline uint16_t _makeUint16(const uint8_t& highOrder, const uint8_t& lowOrder)
{
    // make a 16-bit unsigned integer given the low order and high order bytes.
    // lowOrder first because the Arduino is little endian.
    uint8_t value [] = {lowOrder, highOrder};
    return *(uint16_t *)&value;
}

uint16_t _checksum(const ICMPEcho& echo)
{
    // calculate the checksum of an ICMPEcho with all fields but icmpHeader.checksum populated
    unsigned long sum = 0;

    // add the header, bytes reversed since we're using little-endian arithmetic.
    sum += _makeUint16(echo.icmpHeader.type, echo.icmpHeader.code);

    // add id and sequence
    sum += echo.id + echo.seq;

    // add time, one half at a time.
    uint16_t const * time = (uint16_t const *)&echo.time;
    sum += *time + *(time + 1);
    
    // add the payload
    for (uint8_t const * b = echo.payload; b < echo.payload + sizeof(echo.payload); b+=2)
    {
        sum += _makeUint16(*b, *(b + 1));
    }

    // ones complement of ones complement sum
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    return ~sum;
}

ICMPEcho::ICMPEcho(uint8_t type, uint16_t _id, uint16_t _seq, uint8_t * _payload)
: seq(_seq), id(_id), time(millis())
{
    memcpy(payload, _payload, REQ_DATASIZE);
    icmpHeader.type = type;
    icmpHeader.code = 0;
    icmpHeader.checksum = _checksum(*this);
}

ICMPEcho::ICMPEcho()
: seq(0), id(0), time(0)
{
    memset(payload, 0, sizeof(payload));
    icmpHeader.code = 0;
    icmpHeader.type = 0;
    icmpHeader.checksum = 0;
}

void ICMPEcho::serialize(uint8_t * binData) const
{
    *(binData++) = icmpHeader.type;
    *(binData++) = icmpHeader.code;

    *(uint16_t *)binData = htons(icmpHeader.checksum); binData += 2;
    *(uint16_t *)binData = htons(id);                  binData += 2;
    *(uint16_t *)binData = htons(seq);                 binData += 2;
    *(time_t *)  binData = htonl(time);                binData += 4;

    memcpy(binData, payload, sizeof(payload));
}

void ICMPEcho::deserialize(uint8_t const * binData)
{
    icmpHeader.type = *(binData++);
    icmpHeader.code = *(binData++);

    icmpHeader.checksum = ntohs(*(uint16_t *)binData); binData += 2;
    id                  = ntohs(*(uint16_t *)binData); binData += 2;
    seq                 = ntohs(*(uint16_t *)binData); binData += 2;

    if (icmpHeader.type != TIME_EXCEEDED)
    {
        time = ntohl(*(time_t *)binData);   binData += 4;
    }

    memcpy(payload, binData, sizeof(payload));
}

ICMPPing::ICMPPing(SOCKET socket, uint8_t id)
: _socket(socket), _id(id)
{}

void ICMPPing::operator()(const IPAddress& addr, int nRetries, ICMPEchoReply& result)
{
    W5100.execCmdSn(_socket, Sock_CLOSE);
    W5100.writeSnIR(_socket, 0xFF);
    W5100.writeSnMR(_socket, SnMR::IPRAW);
    W5100.writeSnPROTO(_socket, IPPROTO::ICMP);
    W5100.writeSnPORT(_socket, 0);
    W5100.execCmdSn(_socket, Sock_OPEN);

    static uint8_t payload [REQ_DATASIZE];
    memset(payload, 0x1A, REQ_DATASIZE);

    ICMPEcho echoReq(ICMP_ECHOREQ, _id, _nextSeq++, payload);

    for (int i=0; i<nRetries; ++i)
    {
        result.status = sendEchoRequest(addr, echoReq);
        if (result.status == SUCCESS)
        {
            byte replyAddr [4];
            receiveEchoReply(echoReq, addr, result);
        }
        if (result.status == SUCCESS)
        {
            break;
        }
    }
   
    W5100.execCmdSn(_socket, Sock_CLOSE);
    W5100.writeSnIR(_socket, 0xFF);
}

ICMPEchoReply ICMPPing::operator()(const IPAddress& addr, int nRetries)
{
    ICMPEchoReply reply;
    operator()(addr, nRetries, reply);
    return reply;
}

Status ICMPPing::sendEchoRequest(const IPAddress& addr, const ICMPEcho& echoReq)
{
    // I wish there were a better way of doing this, but if we use the uint32_t
    // cast operator, we're forced to (1) cast away the constness, and (2) deal
    // with an endianness nightmare.
    uint8_t addri [] = {addr[0], addr[1], addr[2], addr[3]};
    W5100.writeSnDIPR(_socket, addri);
    W5100.writeSnTTL(_socket, 128);
    // The port isn't used, becuause ICMP is a network-layer protocol. So we
    // write zero. This probably isn't actually necessary.
    W5100.writeSnDPORT(_socket, 0);

    uint8_t serialized [sizeof(ICMPEcho)];
    echoReq.serialize(serialized);

    W5100.send_data_processing(_socket, serialized, sizeof(ICMPEcho));
    W5100.execCmdSn(_socket, Sock_SEND);
    while ((W5100.readSnIR(_socket) & SnIR::SEND_OK) != SnIR::SEND_OK) 
    {
        if (W5100.readSnIR(_socket) & SnIR::TIMEOUT)
        {
            W5100.writeSnIR(_socket, (SnIR::SEND_OK | SnIR::TIMEOUT));
            return SEND_TIMEOUT;
        }
    }
    W5100.writeSnIR(_socket, SnIR::SEND_OK);
    return SUCCESS;
}

void ICMPPing::receiveEchoReply(const ICMPEcho& echoReq, const IPAddress& addr, ICMPEchoReply& echoReply)
{
    time_t start = millis();
    while (millis() - start < PING_TIMEOUT)
    {
        if (W5100.getRXReceivedSize(_socket))
        {
            uint8_t ipHeader [6];
            uint8_t buffer = W5100.readSnRX_RD(_socket);
            W5100.read_data(_socket, (uint8_t *)buffer, ipHeader, sizeof(ipHeader));
            buffer += sizeof(ipHeader);
            for (int i=0; i<4; ++i) echoReply.addr[i] = ipHeader[i];
            uint8_t dataLen = ipHeader[4];
            dataLen = (dataLen << 8) + ipHeader[5];

            uint8_t serialized [sizeof(ICMPEcho)];
            if (dataLen > sizeof(ICMPEcho)) dataLen = sizeof(ICMPEcho);
            W5100.read_data(_socket, (uint8_t *)buffer, serialized, dataLen);
            echoReply.data.deserialize(serialized);

            buffer += dataLen;
            W5100.writeSnRX_RD(_socket, buffer);
            W5100.execCmdSn(_socket, Sock_RECV);

            echoReply.ttl = W5100.readSnTTL(_socket);

            // Since there aren't any ports in ICMP, we need to manually inspect the response
            // to see if it originated from the request we sent out.
            switch (echoReply.data.icmpHeader.type)
            {
                case ICMP_ECHOREP:
                {
                    if(echoReply.data.id == echoReq.id &&
                       echoReply.data.seq == echoReq.seq)
                    {
                        echoReply.status = SUCCESS;
                        return;
                    }
                    break;
                }
                case TIME_EXCEEDED:
                {
                    uint8_t * sourceIpHeader = echoReply.data.payload;
                    unsigned int ipHeaderSize = (sourceIpHeader[0] & 0x0F)*4u;
                    uint8_t * sourceIcmpHeader = echoReply.data.payload + ipHeaderSize;

                    // The destination ip address in the originating packet's IP header.
                    IPAddress sourceDestAddress(sourceIpHeader + ipHeaderSize - 4);

                    if (!(sourceDestAddress == addr)) continue;

                    uint16_t sourceId  = ntohs(*(uint16_t *)(sourceIcmpHeader + 4));
                    uint16_t sourceSeq = ntohs(*(uint16_t *)(sourceIcmpHeader + 6));

                    if (sourceId == echoReq.id && sourceSeq == echoReq.seq)
                    {
                        echoReply.status = BAD_RESPONSE;
                        return;
                    }
                    break;
                }
            }
        }
    }
    echoReply.status = NO_RESPONSE;
}
