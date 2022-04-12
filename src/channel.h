#pragma once

typedef struct {
    char bytes[4];
} IPAddress;

typedef enum {
    LEGACY_TCP,
    LEGACY_UDP,
} Protocol;

typedef struct {
    int port;
    IPAddress address;
    Protocol protocol;
    int connected;
    int bufferFull;
} Channel;

enum PacketAction {
    Send,
    Buffer,
    Drop
};

enum PacketAction should_send_packet(Channel ch);

void initChannel(Channel* channel);
