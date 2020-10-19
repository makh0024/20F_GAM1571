#pragma once

class RemoveFromGameEvent : public fw::Event
{
public:
    RemoveFromGameEvent(fw::GameObject* pObject)
    {
        m_EventType = "RemoveFromGameEvent";
        m_pObject = pObject;
    }
    ~RemoveFromGameEvent() {}

    static const char* GetStaticEventType() { return "RemoveFromGameEvent"; }
    virtual const char* GetType() override { return GetStaticEventType(); }
    
    fw::GameObject* GetGameObject() { return m_pObject; }

protected:
    fw::GameObject* m_pObject;
};

class SpawnNewEnemyEvent : public fw::Event
{
public:
    SpawnNewEnemyEvent()
    {
        m_EventType = "SpawnNewEnemyEvent";
    }
    ~SpawnNewEnemyEvent() {}

    static const char* GetStaticEventType() { return "SpawnNewEnemyEvent"; }
    virtual const char* GetType() override { return GetStaticEventType(); }

protected:

};