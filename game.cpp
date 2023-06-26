#include "game.h"

/*
 * Constructor / Destructor
 */
Game::Game(unsigned int width, unsigned int height) {
  // Init the window
  m_initRes.x = width;
  m_initRes.y = height;

  m_currentRes.x = width;
  m_currentRes.y = width;

  initWindow();

  // Init the game elements
  m_player = new Player{};

  m_ammoReloadTimerMax = 50.f;
  m_ammoReloadTimer = m_ammoReloadTimerMax;
  m_maxAmmo = 500;
  m_ammo = 455;

  // load fonts
  if (!m_font.loadFromFile("../Minecraft.ttf")) {
    std::cout << "Game::Game() - Error loading Minecraft.ttf\n";
  }
  m_ammoText.setFont(m_font);
  m_ammoText.setCharacterSize(10);
  m_ammoText.setString("Ammo: ");
  m_ammoText.setFillColor(sf::Color::White);
  updateGUISize();

  m_enemies.push_back(new Alien());
  m_enemies.back()->move(10.f, 10.f);
}

Game::~Game() {
  delete m_window;
  delete m_player;

  for (auto bullet : m_bullets) delete bullet;
  for (auto enemy : m_enemies) delete enemy;
}

// Getters
bool Game::isRunning() const {
  return m_window->isOpen();
}

// private functions
void Game::initWindow() {
  m_videoMode.width = m_initRes.x;
  m_videoMode.height = m_initRes.y;

  m_window = new sf::RenderWindow(m_videoMode, "Swaglords Of Space", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
  assert(m_window);
  m_window->setFramerateLimit(144);
  m_window->setVerticalSyncEnabled(false);
}

void Game::updateGUISize() {
  m_ammoText.setPosition(10, m_window->getSize().y - 50);
  std::cout << "WIDTH" << m_ammoText.getGlobalBounds().width << '\n';

  m_ammoBar.setup(m_ammoText.getGlobalBounds().left + m_ammoText.getGlobalBounds().width + 10, m_ammoText.getGlobalBounds().top + m_ammoText.getGlobalBounds().height / 2 - 5 , 150.f, 10.f, m_maxAmmo, sf::Color{255,255,255}, sf::Color{255, 0, 0});
}

void Game::snapWindowToAspectRatio(const sf::Vector2u& newSize) {
  // Get the current width and height of the window
  const unsigned int currentWidth = newSize.x;
  const unsigned int currentHeight = newSize.y;

  // Calculate the original aspect ratio
  const float originalAspect = static_cast<float>(m_initRes.x) / m_initRes.y;

  // Calculate the current aspect ratio
  const float currentAspect = static_cast<float>(currentWidth) / currentHeight;

  // Calculate the new width and height to maintain the original aspect ratio
  unsigned int newWidth = currentWidth;
  unsigned int newHeight = currentHeight;

  if (currentAspect > originalAspect)
  {
    // The current aspect ratio is wider than the original, so we need to adjust the width
    newWidth = static_cast<unsigned int>(originalAspect * currentHeight);
  }
  else if (currentAspect < originalAspect)
  {
    // The current aspect ratio is taller than the original, so we need to adjust the height
    newHeight = static_cast<unsigned int>(currentWidth / originalAspect);
  }

  // Set the new size of the window
  m_window->setSize(sf::Vector2u(newWidth, newHeight));
  m_currentRes.x = currentWidth;
  m_currentRes.y = currentHeight;
}

/*
 * Update and rendering functions
 */

void Game::update() {
  pollEvents();
  updateMousePositions();
  updateShooting();

  m_player->update();
  for (auto bullet : m_bullets) {
    bullet->update();
  }
  for (auto &i : m_enemies) i->update();

  updateEnemyCollision();
  updateGUI();
}

void Game::pollEvents() {
  while (m_window->pollEvent(m_ev)) {
    switch (m_ev.type) {
      case sf::Event::Closed:
        m_window->close();
        break;
      case sf::Event::KeyPressed:
        if (m_ev.key.code == sf::Keyboard::Escape) m_window->close();
        break;
      case sf::Event::Resized:
        Game::snapWindowToAspectRatio(m_window->getSize());
        std::cout << m_window->getSize().x << "x" << m_window->getSize().y << '\n';
    }
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) m_player->move(-0.5, 0);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) m_player->move(0.5, 0);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) m_player->move(0, -1);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) m_player->move(0, 1);

}

void Game::updateShooting() {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_ammo > 0) {
    m_bullets.push_back(new Bullet{0.f, -1.f, m_player->x() + 32, m_player->y() - 32, 10});
    --m_ammo;
    if (m_ammo == 0) m_ammoReloadTimer = m_ammoReloadTimerMax;
  } else {

    if (m_ammo < m_maxAmmo) {
      if (m_ammoReloadTimer == 0) {
        ++m_ammo;
        m_ammoReloadTimer = m_ammoReloadTimerMax;
      } else {
        //std::cout << "Decrementing timer: " << m_ammoReloadTimer << '\n';
        --m_ammoReloadTimer;
      }
    }
  }

  for (int i{0}; i < m_bullets.size(); ++i) {
    if (m_bullets[i]->getPos().y <= 0) {
      delete m_bullets[i];
      m_bullets.erase(m_bullets.begin() + i);
    }
  }
}

void Game::updateMousePositions() {
  m_mousePosWindow = sf::Mouse::getPosition(*m_window);
  m_mousePosView = m_window->mapPixelToCoords(m_mousePosWindow);
}

void Game::updateGUI() {
  m_ammoBar.update(m_ammo);
}


void Game::updateEnemyCollision() {
  for (int i{0}; i < m_enemies.size(); ++i) {
    for (auto bullet : m_bullets) {
      if (m_enemies[i]->getSprite().getGlobalBounds().intersects(bullet->getSprite().getGlobalBounds())) {
        delete m_enemies[i];
        m_enemies.erase(m_enemies.begin() + i);
      }
    }

    if (m_enemies[i]->getSprite().getGlobalBounds().intersects(m_player->getSprite().getGlobalBounds())) {
      // Kill the player, end the game
    }
  }
}

void Game::render() {
  m_window->clear();
  // Draw game
  for (auto bullet : m_bullets) {
    bullet->render(m_window);
  }
  m_player->render(m_window);
  for (auto &i : m_enemies) i->render(m_window);
  renderGUI();
  m_window->display();
}

void Game::renderGUI() {
  m_ammoBar.render(m_window);
  m_window->draw(m_ammoText);
}




