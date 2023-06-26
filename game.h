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
#include "alien.h"
#include "bullet.h"
#include "progress_bar.h"

class Game {
private:
    // Window Variables
    sf::RenderWindow *m_window{nullptr};
    sf::VideoMode m_videoMode;
    sf::Event m_ev;

    sf::Vector2u m_initRes;
    sf::Vector2u m_currentRes;

    // Mouse Position
    sf::Vector2i m_mousePosWindow;
    sf::Vector2f m_mousePosView;

    // GUI data
    ProgressBar m_ammoBar;
    sf::Font m_font;
    sf::Text m_ammoText;

    // Game data
    Player *m_player{nullptr};
    std::vector<Bullet*> m_bullets;
    std::vector<Alien*>m_enemies;

    int m_ammo{};
    int m_maxAmmo{};
    float m_ammoReloadTimer{};
    float m_ammoReloadTimerMax{};

    // Private functions
    void initWindow();
    void updateGUISize();
    void snapWindowToAspectRatio(const sf::Vector2u& newSize);

public:
    // Constructors / Destructors
    Game(unsigned int width, unsigned int height);
    virtual ~Game();

    // Getters
    [[nodiscard]] bool isRunning() const;

    // Functions
    void pollEvents();
    void updateShooting();
    void updateMousePositions();
    void updateEnemies();
    void updateEnemyCollision();
    void updateGUI();
    void update();


    void render();
    void renderGUI();
};


#endif //HELLOSFML_GAME_H
