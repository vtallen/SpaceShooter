#include "alien.h"
/*
 * Constructor / Destructor
 */
Alien::Alien(int maxHp) {
  initTexture();
  initSprite();
  m_moveSpeed = 10.f;

  m_maxHp = maxHp;
  m_hp = m_maxHp;

  m_damageTimer = 0.f;
  m_damageTimerMax = 30.f;
}

Alien::~Alien() {
  delete m_texture;
}

float Alien::x() {
  return m_sprite.getGlobalBounds().left;
}

float Alien::y() {
  return m_sprite.getGlobalBounds().top;
}

float Alien::width() {
  return m_sprite.getGlobalBounds().width;
}

float Alien::height() {
  return m_sprite.getGlobalBounds().height;
}

const sf::Sprite &Alien::getSprite() {
  return m_sprite;
}

int Alien::getHp() {
  return m_hp;
}

void Alien::takeDamage(int amt) {
  if ((m_hp - amt) >= 0) {
    m_hp -= amt;
  } else {
    m_hp = 0;
  }
  m_damageTimer = m_damageTimerMax;
}

float &Alien::getDamageTimer() {
  return m_damageTimer;
}

/*
 * Private functions
 */
void Alien::initTexture() {
  m_texture = new sf::Texture{};
  if (!m_texture->loadFromFile("../Textures/alien.png")) std::cerr << "Alien::initTexture() - Unable to load alien.png\n";
}

void Alien::initSprite() {
  assert(m_texture && "Alien::initSprite() - Texture was null");
  m_sprite.setTexture(*m_texture);
  m_sprite.scale(sf::Vector2f(2.f, 2.f));
}



/*
 * Public functions
 */
void Alien::update() {
  if (m_damageTimer > 0) {
    m_damageTimer--;
  }
}

void Alien::render(sf::RenderTarget *target) {
  target->draw(m_sprite);
}

void Alien::move(const float dirX, const float dirY) {
  m_sprite.move(m_moveSpeed * dirX, m_moveSpeed * dirY);
}
