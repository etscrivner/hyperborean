#ifndef HYPERBOREAN_EVENTS_CHANNEL_HPP_INCLUDED
#define HYPERBOREAN_EVENTS_CHANNEL_HPP_INCLUDED

#include <set>
#include <memory>

#include "Events/BaseEvent.hpp"

namespace Hyperborean {
  namespace Events {
    // Forward definitions (this classes are circularly linked)
    class EventListener;

    ///////////////////////////////////////////////////////////////////////////
    // Responsible for broadcasting messages to a series of objects. Multiple
    // event channels can be created and allowed to receive or not receive
    // events in order to simulate menus and other overriding event handlers.
    //
    // Events are not necessarily dispatched to registered listeners by their
    // registration order, so any ordering requirements on events should be
    // handled at a higher level or ignored at a lower level.
    //
    // The lifecycle of event listeners registered to this class is unowned
    // by the event channel.
    class EventChannel {
    public:
      /////////////////////////////////////////////////////////////////////////
      // Registers a new event listener on this event channel. Once registered,
      // all new events will be broadcast to the listener.
      //
      // Parameters:
      //   listener - The event listener to be registered.
      void Register(EventListener* listener);

      /////////////////////////////////////////////////////////////////////////
      // Unregisters an event listener from this channel. If a matching event
      // listener could not be found then an error is logged and nothing is
      // done.
      //
      // Parameters:
      //   listener - The event listener to be unregistered.
      void Unregister(EventListener* listener);

      /////////////////////////////////////////////////////////////////////////
      // Broadcast the given event to all registered event listeners.
      //
      // Parameters:
      //   event - The event to broadcast to all listeners.
      virtual void SendEvent(BaseEvent* event);
    private:
      // Unowned pointers to all the registered event listeners.
      std::set<EventListener*> listeners_;
    };
  }
}

#endif // HYPERBOREAN_EVENTS_CHANNEL_HPP_INCLUDED
