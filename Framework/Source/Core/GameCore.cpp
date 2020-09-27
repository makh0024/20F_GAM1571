#include "GameCore.h"
using namespace fw;

fw::GameCore::GameCore(FWCore* pFramework)
{
	m_pFramework = pFramework;
}

GameCore::~GameCore()
{

}

FWCore* fw::GameCore::GetFramework()
{
	return m_pFramework;
}

