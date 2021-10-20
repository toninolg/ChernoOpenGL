#ifndef TESTCLEARCOLOR_H
#define TESTCLEARCOLOR_H

#include "test.h"

namespace test {

    class TestClearColor : public Test
    {

    public:

        TestClearColor();
        ~TestClearColor();

        void onUpdate(float deltaTime = 0.0f) override;
        void onRender() override;
        void onImGuiRender() override;

    private:

        float m_clearColor[4];

    };

}


#endif // TESTCLEARCOLOR_H
