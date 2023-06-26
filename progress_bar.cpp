#include "progress_bar.h"

ProgressBar::ProgressBar(float x, float y, float width, float height, int maxNum, const sf::Color bgColor, const sf::Color fgColor)
  : m_x{x},
  m_y{y},
  m_width{width},
  m_height{height},
  m_maxNum{maxNum},
  m_bgColor{bgColor},
  m_fgColor{fgColor} {

  initShapes();
}

ProgressBar::ProgressBar() {

}

ProgressBar::~ProgressBar() {

}
void ProgressBar::setPosition(float x, float y) {
  m_x = x;
  m_y = y;

  initShapes();
}

void ProgressBar::setSize(float width, float height) {
  m_width = width;
  m_height = height;

  initShapes();
}

void ProgressBar::setup(float x, float y, float width, float height, int maxNum, const sf::Color &bgColor, const sf::Color &fgColor) {
  m_x = x;
  m_y = y;
  m_width = width;
  m_height = height;

  m_maxNum = maxNum;

  m_bgColor = bgColor;
  m_fgColor = fgColor;

  initShapes();
}

void ProgressBar::initShapes() {
  m_outerRect.setFillColor(m_bgColor);
  m_outerRect.setPosition(m_x, m_y);
  m_outerRect.setSize(sf::Vector2f(m_width, m_height));

  m_barRect.setPosition(m_x + 5.f, m_y + 5.f);
  m_barRect.setSize(sf::Vector2f(m_width - 10.f, m_height - 10.f));
  m_barRect.setOutlineThickness(1.f);
  m_barRect.setFillColor(m_fgColor);
  m_barRect.setOutlineColor(m_fgColor);
}

void ProgressBar::update(int currentNum) {
  m_currentNum = currentNum;
  float pxPerHp{(m_width - 20.f) / m_maxNum};
  m_barRect.setSize(sf::Vector2f(m_currentNum * pxPerHp, m_height - 10.f));
}

void ProgressBar::render(sf::RenderTarget *target) {
  target->draw(m_outerRect);
  target->draw(m_barRect);
}


