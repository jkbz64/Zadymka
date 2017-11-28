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

class VertexArray : public Drawable, private std::vector<Vertex>, public Transformable
{
public:
    static void registerClass();
    VertexArray(const PrimitiveType& type);
    virtual ~VertexArray() = default;
    void resize(std::size_t);
    std::vector<Vertex>& getVertexes();
    void setTexture(const Texture&);
protected:
    virtual void draw(const Shader&) override;
    PrimitiveType m_primitiveType;
    bool m_needUpdate;
    Texture m_texture;
    virtual GLuint update();
};

#endif
