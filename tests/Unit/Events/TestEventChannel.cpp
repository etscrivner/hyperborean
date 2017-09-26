#include "Events/BaseEvent.hpp"
#include "Events/EventChannel.hpp"
#include "Events/EventListener.hpp"
#include "Log.hpp"

#include "catch.hpp"

///////////////////////////////////////////////////////////////////////////////
// Mock event listener used for testing
class MockEventListener : public Hyperborean::Events::EventListener {
public:
  // The last event received by this event listener
  Hyperborean::Events::BaseEvent* lastEvent_;

  void OnEvent(Hyperborean::Events::BaseEvent* event) {
    lastEvent_ = event;
  }
};

///////////////////////////////////////////////////////////////////////////////

TEST_CASE("EventChannel::Register", "[events]")
{
  Hyperborean::Events::EventChannel channel;

  SECTION("successfully registers listener")
  {
    std::array<MockEventListener, 2> listeners;
    REQUIRE_NOTHROW(channel.Register(&listeners[0]));
    REQUIRE_NOTHROW(channel.Register(&listeners[1]));
  }
}

///////////////////////////////////////////////////////////////////////////////

TEST_CASE("EventChannel::SendEvent", "[events]")
{
  Hyperborean::Events::EventChannel channel;

  std::array<MockEventListener, 2> listeners;
  REQUIRE_NOTHROW(channel.Register(&listeners[0]));
  REQUIRE_NOTHROW(channel.Register(&listeners[1]));

  SECTION("successfully dispatches event to all listeners")
  {
    Hyperborean::Events::BaseEvent event = { 12 };
    channel.SendEvent(&event);

    REQUIRE(listeners[0].lastEvent_ == &event);
    REQUIRE(listeners[1].lastEvent_ == &event);
  }
}
