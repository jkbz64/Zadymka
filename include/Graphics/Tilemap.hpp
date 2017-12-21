#ifndef TILEMAP_HPP
#define TILEMAP_HPP
#include <Graphics/Drawable.hpp>
#include <vector>
#include <glm/vec2.hpp>
#include <Graphics/Texture.hpp>
#include <Graphics/Transformable.hpp>

struct Layer
{
    bool m_visible;
    bool m_needUpdate;
    glm::uvec2 m_size;
    std::vector<unsigned int> m_data;
    Texture m_texture;
};

using TileCoord = glm::ivec2;

class Tilemap : public Drawable, protected Transformable
{
public:
    Tilemap(const Texture&, const glm::uvec2&);
    ~Tilemap();
    const glm::uvec2& getTileSize() const;
    Texture& getTileset();
    Layer& appendLayer(const glm::uvec2&);
    Layer& prependLayer(const glm::uvec2&);
    std::vector<Layer>& getLayers();
    const glm::ivec2& getCoord(unsigned int);
protected:
    void draw(Renderer*) override;
    Texture m_tileset;
    glm::uvec2 m_tileSize;
    std::vector<TileCoord> m_tileCoords;
    std::vector<Layer> m_layers;
};


#endif
