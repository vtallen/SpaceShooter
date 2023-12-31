#include "player.h"
/*
 * Constructor / Destructor
 */
Player::Player() {
  initTexture();
  initSprite();
  m_moveSpeed = 10.f;
}

Player::~Player() {
  delete m_texture;
}

float Player::x() {
  return m_sprite.getGlobalBounds().left;
}

float Player::y() {
  return m_sprite.getGlobalBounds().top;
}

float Player::width() {
  return m_sprite.getGlobalBounds().width;
}

float Player::height() {
  return m_sprite.getGlobalBounds().height;
}

const sf::Sprite &Player::getSprite() {
  return m_sprite;
}
/*
 * Private functions
 */
void Player::initTexture() {
  m_texture = new sf::Texture{};
  if (!m_texture->loadFromFile("../Textures/ship.png")) std::cerr << "Player::initTexture() - Unable to load ship.png\n";
}

void Player::initSprite() {
  assert(m_texture && "Player::initSprite() - Texture was null");
  m_sprite.setTexture(*m_texture);
  m_sprite.scale(sf::Vector2f(2.f, 2.f));
}



/*
 * Public functions
 */
void Player::update() {

}

void Player::render(sf::RenderTarget *target) {
  target->draw(m_sprite);
}

void Player::move(const float dirX, const float dirY) {
  m_sprite.move(m_moveSpeed * dirX, m_moveSpeed * dirY);
}
