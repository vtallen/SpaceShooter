#ifndef SWAGLORDSOFSPACE_ALIEN_H
#define SWAGLORDSOFSPACE_ALIEN_H
#include <SFML/Graphics.hpp>

#include <iostream>

class Alien {
private:
    sf::Sprite m_sprite;
    sf::Texture *m_texture;
    float m_moveSpeed;

    int m_maxHp;
    int m_hp;

    float m_damageTimerMax;
    float m_damageTimer{};

    void initTexture();
    void initSprite();
public:
    Alien(int maxHp);
    virtual ~Alien();

    float x();
    float y();
    float width();
    float height();

    const sf::Sprite &getSprite();

    int getHp();

    void takeDamage(int amt);

    float &getDamageTimer();
    void resetDamageTimer();

    void update();
    void render(sf::RenderTarget *target);

    void move(const float dirX, const float dirY);
};


#endif //SWAGLORDSOFSPACE_PLAYER_H
