#include <cgreen/cgreen.h>
#include "channel.h"
#include "builders.h"

Describe(ChannelFixture);

// TODO/HARD: remove this global variable
Channel testChannel;

BeforeEach(ChannelFixture) {
    // TODO/HARD: rewrite this setup to use Test Data Builder pattern, instead
    // of calling initChannel function.
    // Note: you will have to add a withProtocol builder for the Channel struct
    // Without looking at initChannel source code - what does initChannel do?
    initChannel(&testChannel);

    // TODO/HARD: Move the setup code into each individual test, simplifying the tests as you go!
}

void setFullTCPChannel(Channel* testChannel) {
    testChannel->bufferFull = 1;
    testChannel->protocol = LEGACY_TCP;
}

void connectIt(Channel* channel) {
    channel->connected = 1;
}

AfterEach(ChannelFixture) {
}

/*
 * Tests for should_send_packet
 */

Ensure(ChannelFixture, udp_protocol_always_sends) {
    assert_that(should_send_packet(testChannel), is_equal_to(Send));
}

Ensure(ChannelFixture, tcp_protocol_drops_if_buffer_is_full) {
    // TODO/EASY: Add builder function for protocol
    // TODO: Add builder functions for connected, call them withConnection and notConnected or similar
    // TODO: Add builder functions for bufferFull, call them something readable
    // TODO: Rewrite the arrange part of test with your TestDataBuilder functions
    setFullTCPChannel(&testChannel);
    assert_that(should_send_packet(testChannel), is_equal_to(Drop));
}

// TODO: rewrite test using TestDataBuilder pattern
Ensure(ChannelFixture, tcp_protocol_buffers_if_not_connected_and_buffer_is_not_full) {
    setFullTCPChannel(&testChannel);
    testChannel.bufferFull = 0;
    assert_that(should_send_packet(testChannel), is_equal_to(Buffer));
}

// TODO: rewrite test using TestDataBuilder pattern
Ensure(ChannelFixture, tcp_protocol_sends_if_connected) {
    setFullTCPChannel(&testChannel);
    connectIt(&testChannel);
    assert_that(should_send_packet(testChannel), is_equal_to(Send));
}


/*
 * Tests for builders - no TODOs below!
 * Use these as a reference on how to create new builders and
 * as documentation for how to use existing builders.
 */

Ensure(ChannelFixture, the_default_address) {
    IPAddress address = buildIPAddress(anIPAddress());
    assert_that(address.bytes[0], is_equal_to(127));
    assert_that(address.bytes[1], is_equal_to(0));
    assert_that(address.bytes[2], is_equal_to(0));
    assert_that(address.bytes[3], is_equal_to(1));
}

Ensure(ChannelFixture, switching_to_a_famous_ip_address) {
    IPAddress address = buildIPAddress(withIP(1, 1, 1, 1, anIPAddress()));
    assert_that(address.bytes[0], is_equal_to(1));
    assert_that(address.bytes[1], is_equal_to(1));
    assert_that(address.bytes[2], is_equal_to(1));
    assert_that(address.bytes[3], is_equal_to(1));
}

Ensure(ChannelFixture, the_default_channel) {
    Channel channel = buildChannel(aChannel());
    assert_that(channel.port, is_equal_to(1));
    assert_that(channel.address.bytes[0], is_equal_to(127));
    assert_that(channel.address.bytes[1], is_equal_to(0));
    assert_that(channel.address.bytes[2], is_equal_to(0));
    assert_that(channel.address.bytes[3], is_equal_to(1));
    assert_that(channel.protocol, is_equal_to(LEGACY_TCP));
}

Ensure(ChannelFixture, setting_port_to_2) {
    Channel channel = buildChannel(
        withPort(2,
        aChannel())
    );
    assert_that(channel.port, is_equal_to(2));
}

Ensure(ChannelFixture, setting_2_channel_parameters) {
    Channel channel = buildChannel(
        withChannelAddress(buildIPAddress(anIPAddress()),
        withPort(2,
        aChannel()))
    );
    assert_that(channel.port, is_equal_to(2));
    assert_that(channel.address.bytes[0], is_equal_to(127));
    assert_that(channel.address.bytes[1], is_equal_to(0));
    assert_that(channel.address.bytes[2], is_equal_to(0));
    assert_that(channel.address.bytes[3], is_equal_to(1));
}

Ensure(ChannelFixture, setting_address_of_channel) {
    Channel channel = buildChannel(
        withChannelAddress(buildIPAddress(withIP(1, 1, 1, 1, anIPAddress())),
        aChannel())
    );
    assert_that(channel.address.bytes[0], is_equal_to(1));
    assert_that(channel.address.bytes[1], is_equal_to(1));
    assert_that(channel.address.bytes[2], is_equal_to(1));
    assert_that(channel.address.bytes[3], is_equal_to(1));
}

Ensure(ChannelFixture, setting_simple_and_nested_fields) {
    Channel channel = buildChannel(
        withPort(2,
        withChannelAddress(
            buildIPAddress(
                withIP(1, 1, 1, 1,
                anIPAddress())
            ),
        aChannel()))
    );
    assert_that(channel.port, is_equal_to(2));
    assert_that(channel.address.bytes[0], is_equal_to(1));
    assert_that(channel.address.bytes[1], is_equal_to(1));
    assert_that(channel.address.bytes[2], is_equal_to(1));
    assert_that(channel.address.bytes[3], is_equal_to(1));
}
