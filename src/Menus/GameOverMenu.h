//
// Created by Steven on 27/11/2022.
//

#ifndef PACMANSFML_GAMEOVERMENU_H
#define PACMANSFML_GAMEOVERMENU_H


#include <iostream>
#include <SFML/Graphics.hpp>

class GameOverMenu
{
 public:
  GameOverMenu(sf::RenderWindow &window);
  ~GameOverMenu();

  bool init();
  void update(float dt);
  void render();

  void keyPressed(sf::Event event);

  bool gameOverPlaySelected = true;

  bool gameWon;

  int score = 0;
  sf::Text ScoreText;
  std::string score_str;

 private:
  sf::RenderWindow&window;

  sf::Font font;
  sf::Text gameOverTitleText;
  sf::Text gameOverWinText;
  sf::Text gameOverLoseText;
  sf::Text gameOverPlayOption;
  sf::Text gameOverQuitOption;
};

#endif // PACMANSFML_GAMEOVERMENU_H
