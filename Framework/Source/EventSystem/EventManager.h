#pragma once

namespace fw {
        class GameCore;
        class Event;

    class EventManager
    {

    public:
        EventManager();
        ~EventManager();

        void AddEvent(Event* pEvent, float delayBeforeSending);
        void DispatchAllEvents(float deltaTime, GameCore* pGameCore);

    protected:

        std::queue<Event*> m_EventQueue;
    };

} // namespace fw