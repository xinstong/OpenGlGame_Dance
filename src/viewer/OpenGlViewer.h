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
    // sub env
    int InitEnv(void);

    int UnInitEnv(void);

    // show
    int Show(void);

    // sub shader function
    int InitShader(void);

    int UnInitShader(void);

    // test the status
    int fetchShaderStatus(GLuint glShader, GLenum stage);

    int fetchProgramStatus(GLuint glProg, GLenum stage);

    // sub input data function
    int InputData(void);

    int ClearData(void);

private:
    GLFWwindow*         _window;
    GLuint              _vertexShader;
    GLuint              _fragmentShader;
    GLuint              _shaderProgram;
    GLuint              _VBO;
    GLuint              _VAO;
    GLuint              _EBO;

    int                 _winWidth;
    int                 _winHeight;
};

#endif //SA_VIEWER_OPENGL_VIEWER__H