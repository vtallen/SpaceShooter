#include "bullet.h"

Bullet::Bullet(float dirX, float dirY, float x, float y, float moveSpeed) : m_moveSpeed{moveSpeed} {
  // Track that a new bullet has been made
  ++Bullet::m_refCount;

  if (!Bullet::m_texture) {
    Bullet::m_texture = new sf::Texture{};
    if (!Bullet::m_texture->loadFromFile("../Textures/bullet.png")) {
      std::cerr << "Bullet::Bullet() - Loading bullet.png failed!\n";
    }
  }

  m_direction.x = dirX;
  m_direction.y = dirY;
  m_sprite.setTexture(*Bullet::m_texture);
  m_sprite.setPosition(x, y);
}

Bullet::~Bullet() {
  --Bullet::m_refCount;
  if (Bullet::m_refCount == 0) {
    delete Bullet::m_texture;
    Bullet::m_texture = nullptr;
  }
}

// Copy constructor
Bullet::Bullet(const Bullet &bullet) {
  m_sprite = bullet.m_sprite;
  m_direction.x = bullet.m_direction.x;
  m_direction.y = bullet.m_direction.y;
  ++Bullet::m_refCount;
}

Bullet &Bullet::operator=(const Bullet &bullet) {
  m_sprite = bullet.m_sprite;
  m_direction.x = bullet.m_direction.x;
  m_direction.y = bullet.m_direction.y;
  ++Bullet::m_refCount;
  return *this;
}

const sf::Sprite &Bullet::getSprite() {
  return m_sprite;
}

const sf::Vector2f Bullet::getPos() {
  return sf::Vector2f{m_sprite.getGlobalBounds().left, m_sprite.getGlobalBounds().top};
}

void Bullet::update() {
  m_sprite.move(m_moveSpeed * m_direction.x, m_moveSpeed * m_direction.y);
}

void Bullet::render(sf::RenderTarget *target) {
  target->draw(m_sprite);
}
