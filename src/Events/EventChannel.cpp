#include "Events/EventChannel.hpp"
#include "Events/EventListener.hpp"
#include "Log.hpp"

void Hyperborean::Events::EventChannel::Register(
  Hyperborean::Events::EventListener* listener)
{
  listeners_.insert(listener);
  listener->AfterRegister(this);
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::Events::EventChannel::Unregister(
  Hyperborean::Events::EventListener* listener)
{
  listeners_.erase(listener);
}

///////////////////////////////////////////////////////////////////////////////

void Hyperborean::Events::EventChannel::SendEvent(
  Hyperborean::Events::BaseEvent* event)
{
  for(auto listener : listeners_) {
    listener->OnEvent(event);
  }
}
