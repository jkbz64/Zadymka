#include <Graphics/Tilemap.hpp>
#include <Graphics/Sprite.hpp>
#include <Graphics/Renderer.hpp>
#include <iostream>

Tilemap::Tilemap(const Texture& texture, const glm::uvec2 &tileSize) :
    m_tileset(texture),
    m_tileSize(tileSize)
{

}

Tilemap::~Tilemap() = default;

Layer& Tilemap::prependLayer(const glm::uvec2& size)
{
    m_layers.insert(std::begin(m_layers), {
            true,
            true,
            size,
            std::vector<unsigned int>(),
            Texture()
    });
    auto& layer = m_layers.front();
    layer.m_data.assign(size.x * size.y, 0);
    return layer;
}

Layer& Tilemap::appendLayer(const glm::uvec2& size)
{
    m_layers.push_back(Layer{
            true,
            true,
            size,
            std::vector<unsigned int>(),
            Texture()
    });
    auto& layer = m_layers.back();
    layer.m_data.assign(size.x * size.y, 0);
    return layer;
}

const glm::uvec2& Tilemap::getTileSize() const
{
    return m_tileSize;
}

const glm::ivec2& Tilemap::getCoord(unsigned int id)
{
    return m_tileCoords[id];
}

Texture& Tilemap::getTileset()
{
    return m_tileset;
}

std::vector<Layer>& Tilemap::getLayers()
{
    return m_layers;
}

void Tilemap::draw(Renderer *renderer)
{
    renderer->render(*this);
}