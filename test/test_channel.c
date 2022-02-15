#include <cgreen/cgreen.h>
#include "channel.h"
#include "builders.h"

Describe(ChannelFixture);

Channel testChannel;

BeforeEach(ChannelFixture) {
    testChannel.address = buildIPAddress(anIPAddress());
    testChannel.protocol = LEGACY_UDP;
    testChannel.port = 1;
}

AfterEach(ChannelFixture) {
}

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

Ensure(ChannelFixture, setting_protocol_to_legacy_udp) {
    Channel channel = buildChannel(
        withProtocol(LEGACY_UDP,
        aChannel())
    );
    assert_that(channel.protocol, is_equal_to(LEGACY_UDP));
}

Ensure(ChannelFixture, setting_2_channel_parameters) {
    Channel channel = buildChannel(
        withPort(2,
        withProtocol(LEGACY_UDP,
        aChannel()))
    );
    assert_that(channel.port, is_equal_to(2));
    assert_that(channel.protocol, is_equal_to(LEGACY_UDP));
}
larif
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
        withProtocol(LEGACY_UDP,
        withChannelAddress(
            buildIPAddress(
                withIP(1, 1, 1, 1,
                anIPAddress())
            ),
        aChannel()))
    ));
    assert_that(channel.port, is_equal_to(2));
    assert_that(channel.protocol, is_equal_to(LEGACY_UDP));
    assert_that(channel.address.bytes[0], is_equal_to(1));
    assert_that(channel.address.bytes[1], is_equal_to(1));
    assert_that(channel.address.bytes[2], is_equal_to(1));
    assert_that(channel.address.bytes[3], is_equal_to(1));
}

/* GOALS Tuesday
 * skriva om fixturer till test data builder pattern
 * "realistiskt liten funktion(er)" som använder strukturerna
 * tester som testar funktionerna
 * learning hour goal: skriv om från tester+fixtur till TestDataBuilder mönster
 */

// fixture tests below

Ensure(ChannelFixture, udp_protocol_always_sends) {
    assert_that(should_send_packet(testChannel), is_equal_to(Send));
}

Ensure(ChannelFixture, tcp_protocol_drops_if_buffer_is_full) {
    testChannel.protocol = LEGACY_TCP;
    testChannel.connected = 0;
    testChannel.bufferFull = 1;
    assert_that(should_send_packet(testChannel), is_equal_to(Drop));
}

Ensure(ChannelFixture, tcp_protocol_buffers_if_not_connected_and_buffer_is_not_full) {
    testChannel.protocol = LEGACY_TCP;
    testChannel.connected = 0;
    testChannel.bufferFull = 0;
    assert_that(should_send_packet(testChannel), is_equal_to(Buffer));
}

Ensure(ChannelFixture, tcp_protocol_sends_if_connected) {
    testChannel.protocol = LEGACY_TCP;
    testChannel.connected = 1;
    assert_that(should_send_packet(testChannel), is_equal_to(Send));
}
