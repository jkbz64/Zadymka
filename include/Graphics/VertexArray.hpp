#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP
#include <Graphics/Drawable.hpp>
#include <Graphics/Vertex.hpp>
#include <vector>
#include <Graphics/Texture.hpp>

enum class PrimitiveType
{
    Point = 0,
    Triangle = 1,
    Quad = 2
};

class VertexArray : public Drawable<VertexArray>, private std::vector<Vertex>
{
public:
    static void registerClass();
    VertexArray(const PrimitiveType& type);
    virtual ~VertexArray() = default;
    void resize(std::size_t);
    std::vector<Vertex>& getVertexes();
    void setTexture(const Texture&);
protected:
    virtual void draw() override;
    PrimitiveType m_primitiveType;
    bool m_needUpdate;

    Texture m_texture;
    GLuint m_vao;
    GLuint m_vVBO;
    GLuint m_txVBO;
    GLuint m_cVBO;
    void update();
};

#endif
