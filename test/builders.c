#include "builders.h"
#include "channel.h"

IPAddressBuilderStruct anIPAddress() {
    IPAddressBuilderStruct builder = {.bytes = {127, 0, 0, 1}};
    return builder;
}

IPAddressBuilderStruct withIP(char a, char b, char c, char d, IPAddressBuilderStruct builder) {
    builder.bytes[0] = a;
    builder.bytes[1] = b;
    builder.bytes[2] = c;
    builder.bytes[3] = d;
    return builder;
}

IPAddress buildIPAddress(IPAddressBuilderStruct builder) {
    IPAddress ipaddress = {.bytes = {builder.bytes[0], builder.bytes[1], builder.bytes[2], builder.bytes[3]}};
    return ipaddress;
}

ChannelBuilderStruct aChannel() {
    ChannelBuilderStruct builder = {
            .port = 1,
            .address = buildIPAddress(anIPAddress()),
    };
    return builder;
}

Channel buildChannel(ChannelBuilderStruct builder) {
    Channel channel = {
            .port = builder.port,
            .address = builder.address,
            .protocol = builder.protocol,
    };
    return channel;
}

ChannelBuilderStruct withPort(int port, ChannelBuilderStruct builder) {
    builder.port = port;
    return builder;
}

ChannelBuilderStruct withProtocol(Protocol protocol, ChannelBuilderStruct builder) {
    builder.protocol = protocol;
    return builder;
}

ChannelBuilderStruct withChannelAddress(IPAddress address, ChannelBuilderStruct builder) {
    builder.address = address;
    return builder;
}
