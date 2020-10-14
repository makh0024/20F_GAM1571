#pragma once

namespace fw {

    class Event
    {
    public:
        Event();
        virtual ~Event();

        virtual const char* GetType() = 0; //{ return m_EventType; }

    protected:
        std::string m_EventType = "BaseEvent";
    };

} // namespace fw