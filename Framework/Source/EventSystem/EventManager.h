#pragma once

namespace fw {
        class GameCore;
        class Event;

    class EventManager
    {

    public:
        EventManager();
        ~EventManager();

        void AddEvent(Event* pEvent);
        void DispatchAllEvents(GameCore* pGameCore);

    protected:
        //GameCore* m_pGameCore;

        //std::queue<Event*> m_Events;
        std::queue<Event*> m_EventQueue;
    };

} // namespace fw