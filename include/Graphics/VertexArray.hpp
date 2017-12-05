#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP
#include <Graphics/Drawable.hpp>
#include <Graphics/Vertex.hpp>
#include <vector>
#include <Graphics/Texture.hpp>
#include <Graphics/Transformable.hpp>

enum class PrimitiveType
{
    Point = 0,
    Triangle = 1,
    Quad = 2
};

class VertexArray : public Drawable, private std::vector<Vertex>, public Transformable
{
public:
    static void registerClass(sol::table);
    VertexArray(const PrimitiveType& type);
    ~VertexArray() = default;
    void resize(std::size_t);
    std::vector<Vertex>& getVertexes();
    void setTexture(const Texture&);
    const Texture& getTexture() const;
    GLuint update() const;
    const PrimitiveType& getPrimitiveType() const;
protected:
    virtual void draw(Renderer*) override;
    PrimitiveType m_primitiveType;
    mutable bool m_needUpdate;
    Texture m_texture;
};

#endif
