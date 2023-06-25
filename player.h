#ifndef SWAGLORDSOFSPACE_PLAYER_H
#define SWAGLORDSOFSPACE_PLAYER_H
#include <SFML/Graphics.hpp>

class Player {
private:
  sf::Sprite m_sprite;
  sf::Texture *m_texture;

  void initTexture();
  void initSprite();
public:
  Player();
  virtual ~Player();

  void update();
  void render(sf::RenderTarget *target);
};


#endif //SWAGLORDSOFSPACE_PLAYER_H
