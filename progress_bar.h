#ifndef PICKUPBALLS_HPBAR_H
#define PICKUPBALLS_HPBAR_H
#include <SFML/Graphics.hpp>

#include <iostream>
class ProgressBar {
private:
   sf::RectangleShape m_outerRect;
   sf::RectangleShape m_barRect;

   sf::Color m_bgColor;
   sf::Color m_fgColor;

   float m_x{};
   float m_y{};
   float m_width{};
   float m_height{};

   int m_maxNum;
   int m_currentNum;


public:
    ProgressBar(float x, float y, float width, float height, int maxNum, const sf::Color bgColor, const sf::Color fgColor);
    ProgressBar();

    ~ProgressBar();

    void setup(float x, float y, float width, float height, int maxNum, const sf::Color &bgColor, const sf::Color &fgColor);

    void setPosition(float x, float y);
    void setSize(float width, float height);

    void update(int currentNum);
    void render(sf::RenderTarget *target);

private:
    void initShapes();

};


#endif //PICKUPBALLS_HPBAR_H
