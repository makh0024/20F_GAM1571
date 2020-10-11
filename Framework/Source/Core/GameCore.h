#pragma once

namespace fw 
{
	class Event;
	class FWCore;

	class GameCore
	{
	public:
		GameCore(FWCore* pFramework);
		virtual ~GameCore();

		virtual void OnEvent(Event* pEvent) = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Draw() = 0;

		FWCore* GetFramework();
	protected:
		FWCore* m_pFramework = nullptr;
	};
} // namespace fw
