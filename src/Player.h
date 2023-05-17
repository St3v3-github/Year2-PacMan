//
// Created by Steven on 25/11/2022.
//

#ifndef PACMANSFML_PLAYER_H
#define PACMANSFML_PLAYER_H
#include <SFML/Graphics.hpp>

class Player
{
 public:
  Player(sf::RenderWindow& window);
  ~Player();

  bool init();
  void update(float dt);
  void render();

  void playerMovement(float dt);
  void wallBounce();

  void spawn();

  void getRect();
  void getFutureRect();

  sf::Sprite player;
  sf::Texture player_texture;

  float player_speed = 100;
  sf::Vector2f player_direction = {0,0};

  bool moveUp = false;
  bool moveDown = false;
  bool moveLeft = false;
  bool moveRight = false;

 private:
  sf::RenderWindow& window;

};

#endif // PACMANSFML_PLAYER_H
