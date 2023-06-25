#include "game.h"

// Constructor / Destructor
Game::Game(unsigned int width, unsigned int height) : m_width{width}, m_height{height} {

  m_shape.setFillColor(sf::Color::White);
  m_shape.setSize(sf::Vector2f(200, 200));
  m_shape.setPosition(sf::Vector2f(10.f, 10.f));

  initWindow();
  m_player = new Player{};
  m_bullets.push_back(Bullet{10.f, 10.f, 10.f});
  m_bullets.push_back(Bullet{10.f, 10.f, 10.f});
  m_bullets.push_back(Bullet{10.f, 10.f, 10.f});
  m_bullets.push_back(Bullet{10.f, 10.f, 10.f});
  m_bullets.push_back(Bullet{10.f, 10.f, 10.f});
}

Game::~Game() {
  delete m_window;
  delete m_player;
}

// private functions

void Game::initWindow() {
  m_videoMode.width = m_width;
  m_videoMode.height = m_height;

  m_window = new sf::RenderWindow(m_videoMode, "Swaglords Of Space", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
  assert(m_window);
  m_window->setFramerateLimit(144);
  m_window->setVerticalSyncEnabled(false);
}


// Getters
const bool Game::isRunning() const {
  return m_window->isOpen();
}


void Game::update() {
  pollEvents();
  updateMousePositions();

  m_player->update();
}

void Game::render() {
  m_window->clear();
  // Draw game
  m_window->draw(m_shape);
  m_player->render(m_window);
  m_window->display();
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
        std::cout << m_window->getSize().x << "x" << m_window->getSize().y << '\n';
    }
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) m_player->move(-1, 0);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) m_player->move(1, 0);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) m_player->move(0, -1);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) m_player->move(0, 1);
}

void Game::updateMousePositions() {
  m_mousePosWindow = sf::Mouse::getPosition(*m_window);
  m_mousePosView = m_window->mapPixelToCoords(m_mousePosWindow);
}


