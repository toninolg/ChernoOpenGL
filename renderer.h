#ifndef RENDERER_H
#define RENDERER_H

#include <signal.h>
#include <GL/glew.h>

#define ASSERT(x) if (!(x)) raise(SIGTRAP);
 #define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))


void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

#endif // RENDERER_H
