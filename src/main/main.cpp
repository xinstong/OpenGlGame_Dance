#include "main/Game.h"


#if WIN32 && _DEBUG
#pragma comment( linker, "/subsystem:\"console\" /ENTRY:\"mainCRTStartup\" ")
#endif


int main()
{
    SaGame game;

    game.Init();

    game.Run();

    game.UnInit();

    return 0;
}
