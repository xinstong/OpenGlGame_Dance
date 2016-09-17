//*********************************//
//File:         OpenGlViewer.h
//Auther:       xst
//History:
//  xst         2016/9/17       create
//*********************************//


#ifndef SA_VIEWER_OPENGL_VIEWER__H
#define SA_VIEWER_OPENGL_VIEWER__H

#include <iostream>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class SaOpenGlViewer
{
public:
    SaOpenGlViewer();
    ~SaOpenGlViewer();

public:
    int Init(void);

    int Run(void);

    int UnInit(void);

public:
    int setPanelSize(int iWidth, int iHeight);

private:
    GLFWwindow*         _window;

    int                 _winWidth;
    int                 _winHeight;
};

#endif //SA_VIEWER_OPENGL_VIEWER__H