#include "bullet.h"

Bullet::Bullet(float dirX, float dirY, float moveSpeed) {
  // Track that a new bullet has been made
  ++Bullet::m_refCount;

  if (!Bullet::m_texture) {
    Bullet::m_texture = new sf::Texture{};
    if (!Bullet::m_texture->loadFromFile("../Textures/bullet.png")) {
      std::cerr << "Bullet::Bullet() - Loading bullet.png failed!\n";
    }
  }

  m_sprite.setTexture(*Bullet::m_texture);
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
  ++Bullet::m_refCount;
}

void Bullet::update() {

}

void Bullet::render(sf::RenderTarget *target) {
  target->draw(m_sprite);
}
