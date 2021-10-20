#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <functional>

namespace test {

    class Test
    {

    public:

        Test() {}
        virtual ~Test() {}

        virtual void onUpdate(float deltaTime = 0.0f) {}
        virtual void onRender() {}
        virtual void onImGuiRender() {}

    };


    class TestMenu : public Test
    {

    public:

        TestMenu(Test*& currentTestPointer);

        void onImGuiRender() override;

        template<typename T>
        void registerTest(const std::string& name)
        {
            m_tests.push_back(std::make_pair(name, []() {return new T(); }));

            std::cout << "Registering test " << name << " total tests = " << m_tests.size() << std::endl;
        }

    private:

        Test*& m_currentTest;
        std::vector<std::pair<std::string, std::function<Test*()>>> m_tests;

    };
}



#endif // TEST_H
