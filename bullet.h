//
// Created by Vincent Allen on 6/25/23.
//

#ifndef SWAGLORDSOFSPACE_BULLET_H
#define SWAGLORDSOFSPACE_BULLET_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Bullet {
private:
  inline static int m_refCount;

  sf::Sprite m_sprite;
  inline static sf::Texture *m_texture{nullptr};

  sf::Vector2f m_direction;
  float m_moveSpeed{};

public:
  Bullet() = default;
  Bullet(float dirX, float dirY, float x, float y, float moveSpeed);
  Bullet(const Bullet &bullet);
  Bullet &operator=(const Bullet &bullet);
  virtual ~Bullet();

  const sf::Sprite &getSprite();
  const sf::Vector2f getPos();

  void update();
  void updateBullets();
  void render(sf::RenderTarget *target);



};


#endif //SWAGLORDSOFSPACE_BULLET_H
