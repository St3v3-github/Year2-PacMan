//
// Created by Steven on 26/11/2022.
//

#include "Coin.h"
#include <iostream>

Coin::Coin(sf::RenderWindow& game_window)
  : window(game_window) {}

bool Coin::init()
{
  if (!coin_texture.loadFromFile("../Data/Images/coinGold.png"))
  {
    std::cout << "The item Texture didn't load in :( \n";
  }
  coin.setTexture(coin_texture);
  coin.setScale(0.25,0.25);

  return true;
}

void Coin::render()
{
  window.draw(coin);
}

void Coin::setPosition(float x, float y)
{
  coin.setPosition(x,y);
}

void Coin::setIsVisible(bool value)
{
  is_visible = value;
}

bool Coin::getIsVisible()
{
  return is_visible;
}