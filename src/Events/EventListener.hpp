#ifndef HYPERBOREAN_EVENTS_EVENT_LISTENER_HPP_INCLUDED
#define HYPERBOREAN_EVENTS_EVENT_LISTENER_HPP_INCLUDED

#include <set>
#include <memory>

#include "Events/BaseEvent.hpp"

namespace Hyperborean {
  namespace Events {
    // Forward declarations
    class EventChannel;

    ///////////////////////////////////////////////////////////////////////////
    // Base class for all objects that wish to register themselves on event
    // channels.
    class EventListener {
    public:
      /////////////////////////////////////////////////////////////////////////
      // Unregister from all event channels
      virtual ~EventListener();

      /////////////////////////////////////////////////////////////////////////
      // Method called after the listener has been registered on the channel
      // so the listener can get a reference to the channel.
      //
      // Parameters:
      //   eventChannel - The event channel this listener is registered on.
      void AfterRegister(
        Hyperborean::Events::EventChannel* channel
      );

      /////////////////////////////////////////////////////////////////////////
      // Handles the processing of an event from an event channel.
      //
      // Parameters:
      //   event - The event received on the channel.
      virtual void OnEvent(BaseEvent* event) = 0;
    private:
      std::set<EventChannel*> eventListenerChannels_;
    };
  }
}

#endif // HYPERBOREAN_EVENTS_EVENT_LISTENER_HPP_INCLUDED
