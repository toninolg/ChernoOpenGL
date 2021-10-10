#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "vertexbuffer.h"
#include "vertexbufferlayout.h"

class VertexArray
{

private:

    unsigned int m_rendererID;

public:

    VertexArray();
    ~VertexArray();

    void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

    void bind() const;
    void unbind() const;
};

#endif // VERTEXARRAY_H
