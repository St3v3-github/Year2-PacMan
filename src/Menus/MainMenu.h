//
// Created by Steven on 27/11/2022.
//

#ifndef PACMANSFML_MAINMENU_H
#define PACMANSFML_MAINMENU_H
#include <SFML/Graphics.hpp>
#include <iostream>

class MainMenu
{
 public:
  MainMenu(sf::RenderWindow& window);
  ~MainMenu();

  bool init();
  void update(float dt);
  void render();
  void keyPressed(sf::Event event);

  bool mainMenuPlaySelected = true;

 private:
  sf::RenderWindow& window;

  sf::Font font;
  sf::Text mainMenuIntroText;
  sf::Text mainMenuPlayOption;
  sf::Text mainMenuQuitOption;

};


#endif // PACMANSFML_MAINMENU_H
