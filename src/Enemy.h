//
// Created by Steven on 25/11/2022.
//

#ifndef PACMANSFML_ENEMY_H
#define PACMANSFML_ENEMY_H
#include <SFML/Graphics.hpp>

class Enemy
{
 public:
  Enemy(sf::RenderWindow& window);
  ~Enemy();

  bool init();
  void update(float dt);
  void render();

  int randNum();

  void spawn(float x, float y);

  void enemyMovement(float dt);
  void wallBounce();

  //// Setting up Enemies
  sf::Sprite enemy;
  sf::Texture enemy_texture1;

  float enemy_speed = 25;
  sf::Vector2f enemy_direction = {2,0};

  bool moveUp;
  bool moveRight;

 private:
  sf::RenderWindow& window;


};

#endif // PACMANSFML_ENEMY_H
