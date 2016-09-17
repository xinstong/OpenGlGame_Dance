//*********************************//
//File:         Game.h
//Auther:       xst
//History:
//  xst         2016/9/17       create
//*********************************//


#ifndef SA_MAIN_GAME__H
#define SA_MAIN_GAME__H

class SaOpenGlViewer;

class SaGame
{
public:
    SaGame();
    ~SaGame();

public:
    int Init(void);

    int Run(void);

    int UnInit(void);

private:
    SaOpenGlViewer*             _viewer;
};

#endif //SA_MAIN_GAME__H