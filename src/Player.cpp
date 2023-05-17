//
// Created by Steven on 25/11/2022.
//

#include "Player.h"
#include <iostream>

Player::Player(sf::RenderWindow& game_window)
  : window(game_window) {}

Player::~Player() = default;

bool Player::init()
{
  ////player stuff begins
  if (!player_texture.loadFromFile("../Data/Images/pacman.png"))
  {
    std::cout << "The Player Texture didn't load in :( \n";
  }

  player.setTexture(player_texture);
  player.setScale(0.035 ,0.035);
  player.setOrigin(player.getGlobalBounds().width / 2, player.getGlobalBounds().height /2);
  player.setPosition((window.getSize().x / 2) - (player.getGlobalBounds().width / 2), (window.getSize().y/2 - 50));

  return false;
}


void Player::update(float dt)
{
  playerMovement(dt);
}


void Player::render()
{
  window.draw(player);
}


void Player::playerMovement(float dt)
{
  player.move(player_direction.x * player_speed * dt, 0);
  player.move(0, player_direction.y * player_speed * dt);

  ////edge teleport
  if (player.getPosition().x < 0)
  {
    player.setPosition(window.getSize().x, player.getPosition().y);
  }

  if (player.getPosition().x > window.getSize().x)
  {
    player.setPosition(0, player.getPosition().y);
  }
}

void Player::wallBounce()
{
  if (moveUp)
  {
    player.setPosition(player.getPosition().x,player.getPosition().y + 3.5);
  }

  if (moveDown)
  {
    player.setPosition(player.getPosition().x,player.getPosition().y - 3.5);
  }

  if (moveLeft)
  {
    player.setPosition(player.getPosition().x + 3.5, player.getPosition().y);
  }

  if (moveRight)
  {
    player.setPosition(player.getPosition().x - 3.5, player.getPosition().y);
  }

  player_direction = {0,0};

}

void Player::spawn()
{
  player.setPosition((window.getSize().x / 2) - (player.getGlobalBounds().width / 2), (window.getSize().y/2 - 50));
  player_speed = 0;
}


void Player::getRect()
{
  sf::IntRect rect;

  rect.top    = player.getGlobalBounds().top;
  rect.left   = player.getGlobalBounds().left;
  rect.width  = player.getGlobalBounds().width;
  rect.height = player.getGlobalBounds().height;

}


void Player::getFutureRect()
{
  sf::IntRect rect;

  rect.top    = player.getGlobalBounds().top; //(player_speed * player_direction);
  rect.left   = player.getGlobalBounds().left;
  rect.width  = player.getGlobalBounds().width;
  rect.height = player.getGlobalBounds().height;
}
