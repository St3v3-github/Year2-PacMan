//
// Created by Steven on 25/11/2022.
//

#include "Enemy.h"
#include <iostream>

#include <cmath>
#include <random>
#include <cstdlib>

Enemy::Enemy(sf::RenderWindow& game_window)
  : window(game_window) {}


Enemy::~Enemy()
{

}


bool Enemy::init()
{
  ////enemy stuff begins
  if (!enemy_texture1.loadFromFile("../Data/Images/Ghost1.png"))
  {
    std::cout << "The Enemy Texture didn't load in :( \n";
  }
  enemy.setTexture(enemy_texture1);
  enemy.setScale(0.075 ,0.075);
  return false;
}

void Enemy::update(float dt)
{
  enemyMovement(dt);
}

void Enemy::render()
{
  window.draw(enemy);
}

void Enemy::enemyMovement(float dt)
{
  ////edge teleport
  if (enemy.getPosition().x < 0)
  {
    enemy.setPosition(window.getSize().x, enemy.getPosition().y);
  }

  if (enemy.getPosition().x > window.getSize().x)
  {
    enemy.setPosition(0, enemy.getPosition().y);
  }

  if (enemy.getPosition().y < 0)
  {
    enemy.setPosition(window.getSize().x, enemy.getPosition().y);
  }

  if (enemy.getPosition().y > window.getSize().y)
  {
    enemy.setPosition(enemy.getPosition().x, 0);
  }


  ////movement

  if (moveUp)
  {
    enemy.setPosition(enemy.getPosition().x, enemy.getPosition().y +- 1.5);
    enemy_direction = {0,-1};
  }

  if (moveRight)
  {
    enemy.setPosition(enemy.getPosition().x +- 1.5, enemy.getPosition().y);
    enemy_direction = {1,0};
  }

  enemy.move(
    enemy_direction.x * enemy_speed * dt,
    enemy_direction.y * enemy_speed * dt);
}


void Enemy::spawn(float x, float y)
{
  enemy.setPosition(x,y);
}


//  moveUp = false;
//  moveDown = false;
//  moveLeft = false;
//  moveRight = false;


//void Enemy::enemyMovement(float dt)
//{
//  if (enemyRight = true)
//  {
//    enemy1.move(1.0f * enemy_speed * dt, 0);
//    enemy2.move(1.0f * enemy_speed * dt, 0);
//    enemy3.move(1.0f * enemy_speed * dt, 0);
//    enemy4.move(1.0f * enemy_speed * dt, 0);
//  }
//
//  else
//  {
//    enemy1.move(-1.0f * enemy_speed * dt, 0);
//    enemy2.move(-1.0f * enemy_speed * dt, 0);
//    enemy3.move(-1.0f * enemy_speed * dt, 0);
//    enemy4.move(-1.0f * enemy_speed * dt, 0);
//  }
//
//  if (enemyUp = true)
//  {
//    enemy1.move(0,1.0f * enemy_speed * dt);
//    enemy2.move(0,1.0f * enemy_speed * dt);
//    enemy3.move(0,1.0f * enemy_speed * dt);
//    enemy4.move(0,1.0f * enemy_speed * dt);
//  }
//
//  else
//  {
//    enemy1.move(0,-1.0f * enemy_speed * dt);
//    enemy2.move(0,-1.0f * enemy_speed * dt);
//    enemy3.move(0,-1.0f * enemy_speed * dt);
//    enemy4.move(0,-1.0f * enemy_speed * dt);
//  }
//}


//void Enemy::enemyMovement(float dt)
//{
//  enemy1.move(enemy_direction.x * enemy_speed * dt, 0);
//  enemy1.move(0, enemy_direction.y * enemy_speed * dt);
//
//  ////edge teleport
//  if (enemy1.getPosition().x || enemy2.getPosition().x || enemy3.getPosition().x || enemy4.getPosition().x < 0)
//  {
//    enemy1.setPosition(window.getSize().x, enemy1.getPosition().y);
//    enemy2.setPosition(window.getSize().x, enemy2.getPosition().y);
//    enemy3.setPosition(window.getSize().x, enemy3.getPosition().y);
//    enemy4.setPosition(window.getSize().x, enemy4.getPosition().y);
//  }
//
//  if (enemy1.getPosition().x || enemy2.getPosition().x || enemy3.getPosition().x || enemy4.getPosition().x> window.getSize().x)
//  {
//    enemy1.setPosition(0, enemy1.getPosition().y);
//    enemy2.setPosition(0, enemy2.getPosition().y);
//    enemy3.setPosition(0, enemy3.getPosition().y);
//    enemy4.setPosition(0, enemy4.getPosition().y);
//  }
//}

//void Enemy::wallBounce()
//{
//
//}
