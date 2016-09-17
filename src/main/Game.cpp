#include "Game.h"
#include <iostream>
#include "common/CommonDefine.h"
#include "viewer/OpenGlViewer.h"


SaGame::SaGame()
    : _viewer(NULL)
{

}


SaGame::~SaGame()
{

}


int SaGame::Init()
{
    int iRes = 0;

    SAFE_NEW_POINTER(_viewer, SaOpenGlViewer);
    SAFE_CALL_POINTER(_viewer, Init);

    return iRes;
}


int SaGame::Run()
{
    int iRes = 0;

    SAFE_CALL_POINTER(_viewer, Run);

    return iRes;
}


int SaGame::UnInit()
{
    int iRes = 0;

    SAFE_CALL_POINTER(_viewer, UnInit);

    return iRes;
}

