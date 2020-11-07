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

class GameOverEvent : public fw::Event
{
public:
    GameOverEvent()
    {
        m_EventType = "GameOverEvent";
    }
    ~GameOverEvent() {}

    static const char* GetStaticEventType() { return "GameOverEvent"; }
    virtual const char* GetType() override { return GetStaticEventType(); }

protected:

};

class RestartEvent : public fw::Event
{
public:
    RestartEvent()
    {
        m_EventType = "RestartEvent";
    }
    ~RestartEvent() {}

    static const char* GetStaticEventType() { return "RestartEvent"; }
    virtual const char* GetType() override { return GetStaticEventType(); }

protected:

};

class EnemyCollisionEvent : public fw::Event
{
public:
    EnemyCollisionEvent(fw::GameObject* pObject)
    {
        m_EventType = "EnemyCollisionEvent";
    }
    ~EnemyCollisionEvent() {}

    static const char* GetStaticEventType() { return "EnemyCollisionEvent"; }
    virtual const char* GetType() override { return GetStaticEventType(); }

    /*fw::GameObject* GetGameObject() { return m_pObject; }

protected:
    fw::GameObject* m_pObject;*/

};