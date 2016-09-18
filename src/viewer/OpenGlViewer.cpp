#include "OpenGlViewer.h"
#include "common/CommonDefine.h"

namespace
{
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
    {
        // 当用户按下ESC键,我们设置window窗口的WindowShouldClose属性为true
        // 关闭应用程序
        if (GLFW_PRESS == action)
        {
            switch (key)
            {
            case GLFW_KEY_ESCAPE:
            {
                // quit
                glfwSetWindowShouldClose(window, GL_TRUE);
                break;
            }
            case GLFW_KEY_F1:
            {
                // line mode
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                break;
            }
            case GLFW_KEY_F2:
            {
                // fill mode
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                break;            
            }
            default:
                break;
            }
        }
    }

    // Shaders
    const GLchar* kStrVertexShaderSource = 
        "#version 330 core\n"
        "layout (location = 0) in vec3 position;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
        "}";

    const GLchar* kStrFragmentShaderSource =
        "#version 330 core\n"
        "out vec4 color;\n"
        "void main()\n"
        "{\n"
        "   color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}";
}


SaOpenGlViewer::SaOpenGlViewer()
    : _window(NULL)
    , _vertexShader(0)
    , _fragmentShader(0)
    , _shaderProgram(0)
    , _VBO(0)
    , _VAO(0)
    , _EBO(0)
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

    InitEnv();

    InitShader();

    InputData();

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

        // show
        Show();

        // Swap the screen buffers
        glfwSwapBuffers(_window);
    }

    return iRes;
}


int SaOpenGlViewer::UnInit()
{
    int iRes = 0;

    ClearData();

    UnInitShader();

    UnInitEnv();

    return iRes;
}


int SaOpenGlViewer::setPanelSize(int iWidth, int iHeight)
{
    int iRes = 0;

    _winWidth = iWidth;

    _winHeight = iHeight;

    return iRes;
}


int SaOpenGlViewer::InitEnv()
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


int SaOpenGlViewer::UnInitEnv()
{
    int iRes = 0;

    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();

    return iRes;
}


int SaOpenGlViewer::Show()
{
    int iRes = 0;

    glUseProgram(_shaderProgram);
    glBindVertexArray(_VAO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    return iRes;
}

int SaOpenGlViewer::InitShader()
{
    int iRes = 0;

    do
    {
        // init vertex shader
        _vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(_vertexShader, 1, &kStrVertexShaderSource, NULL);
        glCompileShader(_vertexShader);
        fetchShaderStatus(_vertexShader, GL_COMPILE_STATUS);

        // init fragment shader
        _fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(_fragmentShader, 1, &kStrFragmentShaderSource, NULL);
        glCompileShader(_fragmentShader);
        fetchShaderStatus(_fragmentShader, GL_COMPILE_STATUS);

        // link shader into program
        _shaderProgram = glCreateProgram();
        if (!_shaderProgram)
        {
            iRes = -1;
            SaLog(ERROR, "create program shader failed.");
            break;
        }
        glAttachShader(_shaderProgram, _vertexShader);
        glAttachShader(_shaderProgram, _fragmentShader);
        glLinkProgram(_shaderProgram);
        fetchProgramStatus(_shaderProgram, GL_LINK_STATUS);
    } while (0);

    glDeleteShader(_vertexShader);
    glDeleteShader(_fragmentShader);

    return iRes;
}


int SaOpenGlViewer::UnInitShader()
{
    int iRes = 0;

    return iRes;
}


int SaOpenGlViewer::fetchShaderStatus(GLuint glShader, GLenum stage)
{
    int iRes = 0;

    GLint curRes = 0;
    GLchar infoLog[512];

    glGetShaderiv(glShader, stage, &curRes);
    if (!curRes)
    {
        iRes = -1;
        glGetShaderInfoLog(glShader, sizeof(infoLog), NULL, infoLog);
        SaLog(ERROR, "when stage is [" << stage << "], error infor:" << infoLog);
    }

    return iRes;
}


int SaOpenGlViewer::fetchProgramStatus(GLuint glProg, GLenum stage)
{
    int iRes = 0;

    GLint curRes = 0;
    GLchar infoLog[512];

    glGetProgramiv(glProg, stage, &curRes);
    if (!curRes)
    {
        iRes = -1;
        glGetShaderInfoLog(glProg, sizeof(infoLog), NULL, infoLog);
        SaLog(ERROR, "when stage is [" << stage << "], error infor:" << infoLog);
    }

    return iRes;
}


int SaOpenGlViewer::InputData()
{
    int iRes = 0;

    // temp define
    GLfloat vertices[] = {
        0.5f, 0.5f, 0.0f,  // Top Right
        0.5f, -0.5f, 0.0f,  // Bottom Right
        -0.5f, -0.5f, 0.0f,  // Bottom Left
        -0.5f, 0.5f, 0.0f   // Top Left 
    };
    GLuint indices[] = {  // Note that we start from 0!
        0, 1, 3,  // First Triangle
        1, 2, 3   // Second Triangle
    };

    // gen buffer
    glGenVertexArrays(1, &_VBO);
    glGenBuffers(1, &_VAO);
    glGenBuffers(1, &_EBO);

    // bind vbo
    glBindVertexArray(_VBO);
    
    // bind vao
    glBindBuffer(GL_ARRAY_BUFFER, _VAO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // bind ebo
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // config vertex attr
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return iRes;
}


int SaOpenGlViewer::ClearData()
{
    int iRes = 0;

    glDeleteVertexArrays(1, &_VAO);
    glDeleteBuffers(1, &_VBO);
    glDeleteBuffers(1, &_EBO);

    return iRes;
}