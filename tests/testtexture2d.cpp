#include "testtexture2d.h"

#include "renderer.h"
#include "imgui.h"
#include "glm/gtc/matrix_transform.hpp"

namespace test {

    TestTexture2D::TestTexture2D() :
        m_translationA(200.0f, 200.0f , 0.0f), m_translationB(400.0f, 200.0f , 0.0f),
        m_proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
        m_view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0 , 0)))
    {
        // Triangle vertex positions
           float positions [] = {
               -50.0f, -50.0f, 0.0f, 0.0f, // 0
                50.0f, -50.0f, 1.0f, 0.0f, // 1
                50.0f,  50.0f, 1.0f, 1.0f, // 2
               -50.0f,  50.0f, 0.0f, 1.0f  // 3
           };

           unsigned int indices[] = {
               0, 1, 2,
               2, 3, 0
           };

           GLCall(glEnable(GL_BLEND));
           GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

           m_VAO = std::make_unique<VertexArray>();

           m_vertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
           VertexBufferLayout layout;
           layout.pushFloat(2);
           layout.pushFloat(2);

           m_VAO->addBuffer(*m_vertexBuffer, layout);

           m_indexBuffer = std::make_unique<IndexBuffer>(indices, 6);

           m_shader = std::make_unique<Shader>("../ChernoOpenGL/assets/shaders/Basic.shader");
           m_shader->bind();

           m_texture = std::make_unique<Texture>("../ChernoOpenGL/assets/textures/cherno.png");
           m_shader->setUniform1i("u_texture", 0);
    }

    test::TestTexture2D::~TestTexture2D()
    {

    }

    void test::TestTexture2D::onUpdate(float deltaTime)
    {

    }

    void test::TestTexture2D::onRender()
    {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;

        m_texture->bind();

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationA);
            glm::mat4 mvp  = m_proj * m_view * model;
            m_shader->bind();
            m_shader->setUniformMat4f("u_MVP", mvp);
            renderer.draw(*m_VAO, *m_indexBuffer, *m_shader);
        }

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationB);
            glm::mat4 mvp  = m_proj * m_view * model;
            m_shader->setUniformMat4f("u_MVP", mvp);
            renderer.draw(*m_VAO, *m_indexBuffer, *m_shader);
        }
    }

    void test::TestTexture2D::onImGuiRender()
    {
        ImGui::SliderFloat3("Translation A", &m_translationA.x, 0.0f, 960.0f);
        ImGui::SliderFloat3("Translation B", &m_translationB.x, 0.0f, 960.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }

}

