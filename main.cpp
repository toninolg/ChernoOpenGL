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
    window = glfwCreateWindow(800, 600, "Cherno OpenGL", NULL, NULL);
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
//    glEnable(GL_DEBUG_OUTPUT);
//    glDebugMessageCallback(DebugMessageCallBack, nullptr);

    // Print versions
    fprintf(stdout, "Status: Using OpenGL %s\n", glGetString(GL_VERSION)); fflush(stdout);
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION)); fflush(stdout);

    // Triangle vertex positions
    float positions [] = {
        100.0f, 100.0f, 0.0f, 0.0f, // 0
        200.0f, 100.0f, 1.0f, 0.0f, // 1
        200.0f, 200.0f, 1.0f, 1.0f, // 2
        100.0f, 200.0f, 0.0f, 1.0f  // 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))

    VertexArray va;

    VertexBuffer vb(positions, 4 * 4 * sizeof(float));

    VertexBufferLayout layout;
    layout.pushFloat(2);
    layout.pushFloat(2);
    va.addBuffer(vb, layout);

    IndexBuffer ib (indices, 6);

    glm::mat4 proj  = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    glm::mat4 view  = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0 , 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200 , 0));

    glm::mat4 mvp  = proj * view * model;

    // Create shaders
    Shader shader("../ChernoOpenGL/assets/shaders/Basic.shader");
    shader.bind();
    shader.setUniform4f("u_color", 0.8f, 0.3f, 0.8f, 1.0f);

    Texture texture("../ChernoOpenGL/assets/textures/cherno.png");
    texture.bind();
    shader.setUniform1i("u_texture", 0);
    shader.setUniformMat4f("u_MVP", mvp);

    va.unbind();
    vb.unbind();
    ib.unbind();
    shader.unbind();

    float r = 0.0f;
    float increment = 0.05f;

    Renderer renderer;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        renderer.clear();

        shader.bind();
        shader.setUniform4f("u_color", r, 0.3f, 0.8f, 1.0f);

        // Issue a draw call on the buffer that is bound
        renderer.draw(va, ib, shader);

        if (r > 1.0f){
            increment = -0.05f;
        }
        else if (r < 0.0f){
            increment = 0.05f;
        }
        r += increment;

        /* Swap front and back buffers */
        GLCall(glfwSwapBuffers(window));

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
