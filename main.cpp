#include <GL/glew.h> // Before including GLFW
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "renderer.h"
#include "vertexbufferlayout.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "shader.h"
#include "texture.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "testclearcolor.h"
#include "testtexture2d.h"


static void DebugMessageCallBack(GLenum source, GLenum type, GLenum id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
    fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
               ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
                type, severity, message );
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 720, "Cherno OpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* After creating a valid OpenGL rendering context and call glewInit() to initialize the extension entry points */
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Uncomment to output errors
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(DebugMessageCallBack, nullptr);

    // Print versions
    fprintf(stdout, "Status: Using OpenGL %s\n", glGetString(GL_VERSION)); fflush(stdout);
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION)); fflush(stdout);

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))

    Renderer renderer;

    // *******************************************
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    ImGui::StyleColorsDark();
    // *******************************************

    test::Test* currentTest = nullptr;
    test::TestMenu* testMenu = new test::TestMenu(currentTest);
    currentTest = testMenu;

    testMenu->registerTest<test::TestClearColor>("Clear Color");
    testMenu->registerTest<test::TestTexture2D>("2D Texture");

    while (!glfwWindowShouldClose(window))
    {
        renderer.clear();

        // *****************************
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (currentTest)
        {
            currentTest->onUpdate(0.0f);
            currentTest->onRender();
            ImGui::Begin("Test");
            if (currentTest != testMenu && ImGui::Button("<-"))
            {
                delete currentTest;
                currentTest = testMenu;
            }
            currentTest->onImGuiRender();
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // *******************************************************

        GLCall(glfwSwapBuffers(window));
        glfwPollEvents();
    }

    delete currentTest;
    if (currentTest != testMenu){
        delete testMenu;
    }

    // ********************************
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    // ********************************

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
