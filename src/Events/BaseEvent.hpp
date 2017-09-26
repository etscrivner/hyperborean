#ifndef HYPERBOREAN_EVENTS_BASE_EVENT_HPP_INCLUDED
#define HYPERBOREAN_EVENTS_BASE_EVENT_HPP_INCLUDED

namespace Hyperborean {
  namespace Events {
    ///////////////////////////////////////////////////////////////////////////
    // Base class for all in game events.
    struct BaseEvent {
      // Event type, these should be game-specific and generation can be
      // platform-specific.
      int type;
    };
  }
}

#endif // HYPERBOREAN_EVENTS_BASE_EVENT_HPP_INCLUDED
