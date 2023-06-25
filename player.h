#ifndef SWAGLORDSOFSPACE_PLAYER_H
#define SWAGLORDSOFSPACE_PLAYER_H
#include <SFML/Graphics.hpp>

#include <iostream>

class Player {
private:
  sf::Sprite m_sprite;
  sf::Texture *m_texture;
  float m_moveSpeed;

  void initTexture();
  void initSprite();
public:
  Player();
  virtual ~Player();

  void update();
  void render(sf::RenderTarget *target);

  void move(const float dirX, const float dirY);
};


#endif //SWAGLORDSOFSPACE_PLAYER_H
