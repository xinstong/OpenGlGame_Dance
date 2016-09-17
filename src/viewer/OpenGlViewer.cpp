#include "OpenGlViewer.h"
#include "common/CommonDefine.h"

namespace
{
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
    {
        // 当用户按下ESC键,我们设置window窗口的WindowShouldClose属性为true
        // 关闭应用程序
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);
    }
}


SaOpenGlViewer::SaOpenGlViewer()
    : _window(NULL)
    , _winWidth(800)
    , _winHeight(600)
{

}


SaOpenGlViewer::~SaOpenGlViewer()
{

}


int SaOpenGlViewer::Init()
{
    int iRes = 0;

    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    _window = glfwCreateWindow(_winWidth, _winHeight, "LearnOpenGL", nullptr, nullptr);
    if (_window == nullptr)
    {
        SaLog(ERROR, "Failed to create GLFW window");
        glfwTerminate();
        iRes = -1;
        return iRes;
    }
    glfwMakeContextCurrent(_window);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (glewInit() != GLEW_OK)
    {
        SaLog(ERROR, "Failed to initialize GLEW");
        iRes = -1;
        return iRes;
    }

    glfwGetFramebufferSize(_window, &_winWidth, &_winHeight);
    glViewport(0, 0, _winWidth, _winHeight);

    // set callback
    glfwSetKeyCallback(_window, key_callback);

    return iRes;
}


int SaOpenGlViewer::Run()
{
    int iRes = 0;

    assert(_window);

    // Game loop
    while (!glfwWindowShouldClose(_window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap the screen buffers
        glfwSwapBuffers(_window);
    }

    return iRes;
}


int SaOpenGlViewer::UnInit()
{
    int iRes = 0;

    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;

    return iRes;
}


int SaOpenGlViewer::setPanelSize(int iWidth, int iHeight)
{
    int iRes = 0;

    _winWidth = iWidth;

    _winHeight = iHeight;

    return iRes;
}