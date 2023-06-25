#include "player.h"
/*
 * Constructor / Destructor
 */
Player::Player() {
  m_texture = new sf::Texture{};
  initTexture();
  initSprite();
}

Player::~Player() {
  delete m_texture;
}

/*
 * Private functions
 */
void Player::initTexture() {

}

void Player::initSprite() {
  assert(m_texture && "Player::initSprite() - Texture was null");
  m_sprite.setTexture(*m_texture);
}

/*
 * Public functions
 */
void Player::update() {

}

void Player::render(sf::RenderTarget *target) {
  target->draw(m_sprite);
}
