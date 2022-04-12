#include "channel.h"

enum PacketAction should_send_packet(Channel ch) {
    switch(ch.protocol) {
        case LEGACY_UDP:
            return Send;
        case LEGACY_TCP:
            if(ch.connected)
                return Send;
            if(ch.bufferFull)
                return Drop;
            return Buffer;
    }
}

void initChannel(Channel* channel) {
    IPAddress address = {.bytes = {127, 0, 0, 1}};
    channel->address = address;
    channel->port = 1;
    channel->protocol = LEGACY_UDP;
}
