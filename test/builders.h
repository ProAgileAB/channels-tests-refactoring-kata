#pragma once

#include "channel.h"

// IPAddress
typedef struct {
    char bytes[4];
} IPAddressBuilderStruct;

IPAddressBuilderStruct anIPAddress();

IPAddress buildIPAddress(IPAddressBuilderStruct abs);

IPAddressBuilderStruct withIP(char a, char b, char c, char d, IPAddressBuilderStruct builder);

// Channel
typedef struct {
    int port;
    IPAddress address;
    Protocol protocol;
} ChannelBuilderStruct;

ChannelBuilderStruct aChannel();

Channel buildChannel(ChannelBuilderStruct builder);

ChannelBuilderStruct withPort(int port, ChannelBuilderStruct builder);

ChannelBuilderStruct withProtocol(Protocol protocol, ChannelBuilderStruct builder);

ChannelBuilderStruct withChannelAddress(IPAddress address, ChannelBuilderStruct builder);
