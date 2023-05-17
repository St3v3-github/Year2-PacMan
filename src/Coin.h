//
// Created by Steven on 26/11/2022.
//

#ifndef PACMANSFML_COIN_H
#define PACMANSFML_COIN_H
#include <SFML/Graphics.hpp>

class Coin
{
 public:
  Coin(sf::RenderWindow& window);

  bool init();
  void update(float dt);
  void render();
  void setPosition(float x, float y);
  void setIsVisible(bool value);
  bool getIsVisible();

  sf::Sprite coin;
  sf::Texture coin_texture;

  bool is_visible = true;

 private:
  sf::RenderWindow& window;
};

#endif // PACMANSFML_COIN_H
