#pragma once
#include "GameItems/Bomb.h"

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

class BombExplosionEvent : public fw::Event
{
public:
    BombExplosionEvent(fw::GameObject* bombplacedby)
    {
        m_EventType = "BombExplosionEvent";
        m_pObject = bombplacedby;
    }
    ~BombExplosionEvent() {}

    static const char* GetStaticEventType() { return "BombExplosionEvent"; }
    virtual const char* GetType() override { return GetStaticEventType(); }

    fw::GameObject* GetGameObject() { return m_pObject; }

protected:
    fw::GameObject* m_pObject;
};

class RemoveBombFromGameEvent : public fw::Event
{
public:
    RemoveBombFromGameEvent(Bomb* pObject)
    {
        m_EventType = "RemoveBombFromGameEvent";
        m_pObject = pObject;
    }
    ~RemoveBombFromGameEvent() {}

    static const char* GetStaticEventType() { return "RemoveBombFromGameEvent"; }
    virtual const char* GetType() override { return GetStaticEventType(); }

    Bomb* GetBomb() { return m_pObject; }

protected:
    Bomb* m_pObject;
};