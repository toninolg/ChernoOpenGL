#include "testclearcolor.h"

#include "renderer.h"
#include "imgui.h"

namespace test {

    TestClearColor::TestClearColor()
        : m_clearColor{ 0.2f, 0.3f, 0.8f, 1.0f }
    {

    }

    test::TestClearColor::~TestClearColor()
    {

    }

    void test::TestClearColor::onUpdate(float deltaTime)
    {

    }

    void test::TestClearColor::onRender()
    {
        GLCall(glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
    }

    void test::TestClearColor::onImGuiRender()
    {
        ImGui::ColorEdit4("Clear Color", m_clearColor);
    }

}


