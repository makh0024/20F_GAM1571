//#include "Framework.h"
#include "GamePCH.h"

#include "Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    fw::FWCore* pFramework = new fw::FWCore();
    Game* pGame = new Game(pFramework);

    pFramework->Init(800, 800);
    pGame->Init();

    pFramework->Run( pGame );
    pFramework->Shutdown();

    delete pGame;
    delete pFramework;

    MyMemory_ValidateAllocations(true);
}