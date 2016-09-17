#include "main/Game.h"


#if WIN32 && _DEBUG
#pragma comment( linker, "/ENTRY:\"mainCRTStartup\" ")
#endif


int main()
{
    SaGame game;

    game.Init();

    game.Run();

    game.UnInit();

    return 0;
}
