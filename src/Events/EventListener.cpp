#include "Events/EventListener.hpp"
#include "Events/EventChannel.hpp"

Hyperborean::Events::EventListener::~EventListener()
{
  for (auto listener : eventListenerChannels_) {
    listener->Unregister(this);
  }
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::Events::EventListener::AfterRegister(
  Hyperborean::Events::EventChannel* channel)
{
  eventListenerChannels_.insert(channel);
}
