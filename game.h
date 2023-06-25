/*
 * Class that is responsible for the game engine
 */

#ifndef HELLOSFML_GAME_H
#define HELLOSFML_GAME_H
#include <iostream>
#include <vector>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "player.h"
#include "bullet.h"

class Game {
private:
    // Window Variables
    sf::RenderWindow *m_window{nullptr};
    sf::VideoMode m_videoMode;
    sf::Event m_ev;

    const sf::Vector2f m_refRes{1920.f, 1080.f};

    unsigned int m_width;
    unsigned int m_height;

    // Mouse Position
    sf::Vector2i m_mousePosWindow;
    sf::Vector2f m_mousePosView;

    sf::RectangleShape m_shape{};

    // Game data
    Player *m_player{nullptr};
    std::vector<Bullet> m_bullets;

    // Private functions
    void initWindow();


public:
    // Constructors / Destructors
    Game(unsigned int width, unsigned int height);
    virtual ~Game();

    // Functions
    void update();
    void render();
    void updateMousePositions();
    void pollEvents();
    // Getters
    const bool isRunning() const;
};


#endif //HELLOSFML_GAME_H
