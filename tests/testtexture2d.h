#ifndef TESTTEXTURE2D_H
#define TESTTEXTURE2D_H

#include "test.h"
#include "glm/glm.hpp"
#include "vertexbuffer.h"
#include "vertexbufferlayout.h"
#include "texture.h"
#include "memory"

namespace test {

    class TestTexture2D : public Test
    {

    public:

        TestTexture2D();
        ~TestTexture2D();

        void onUpdate(float deltaTime = 0.0f) override;
        void onRender() override;
        void onImGuiRender() override;


    private:

        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_vertexBuffer;
        std::unique_ptr<IndexBuffer> m_indexBuffer;
        std::unique_ptr<Shader> m_shader;
        std::unique_ptr<Texture> m_texture;

        glm::mat4 m_proj, m_view;
        glm::vec3 m_translationA, m_translationB;

    };
}

#endif // TESTTEXTURE2D_H
