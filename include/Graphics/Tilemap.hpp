#ifndef TILEMAP_HPP
#define TILEMAP_HPP
#include <Graphics/Drawable.hpp>
#include <vector>
#include <glm/vec2.hpp>
#include <Graphics/Texture.hpp>
#include <Graphics/Transformable.hpp>
#include <map>

struct Layer
{
    bool m_visible;
    bool m_needUpdate;
    glm::uvec2 m_size;
    std::vector<unsigned int> m_data;
    Texture m_texture;
};

struct Tileset
{
    Tileset(const Texture& t);
    Texture m_texture;
    std::map<unsigned int, Texture> m_tiles;
    bool m_needUpdate;
};

class Tilemap : public Drawable, protected Transformable
{
public:
    Tilemap(const Texture&, const glm::uvec2&);
    ~Tilemap();
    const glm::uvec2& getTileSize() const;
    Tileset& getTileset();
    Layer& appendLayer(const glm::uvec2&);
    Layer& prependLayer(const glm::uvec2&);
    std::vector<Layer>& getLayers();
protected:
    void draw(Renderer*) override;
    Tileset m_tileset;
    glm::uvec2 m_tileSize;
    std::vector<Layer> m_layers;
};


#endif
