//
// Created by Steven on 27/11/2022.
//

#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow &window): window(window)
{
  //init();
}

MainMenu::~MainMenu() = default;

bool MainMenu::init()
{
  // init Font
  if (!font.loadFromFile("../Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "The Font didn't load in :( \n";
  }
  mainMenuIntroText.setString("PACMAN");
  mainMenuIntroText.setFont(font);
  mainMenuIntroText.setCharacterSize(75);
  mainMenuIntroText.setFillColor(sf::Color(250, 250, 250));
  mainMenuIntroText.setPosition(((window.getSize().x / 2) - (mainMenuIntroText.getGlobalBounds().width) / 2),200);

  mainMenuPlayOption.setString("Play");
  mainMenuPlayOption.setFont(font);
  mainMenuPlayOption.setCharacterSize(20);
  mainMenuPlayOption.setFillColor(sf::Color(250, 250, 250));
  mainMenuPlayOption.setPosition(((window.getSize().x / 2) - (mainMenuPlayOption.getGlobalBounds().width) - 50),450);

  mainMenuQuitOption.setString("Quit");
  mainMenuQuitOption.setFont(font);
  mainMenuQuitOption.setCharacterSize(20);
  mainMenuQuitOption.setFillColor(sf::Color(250, 250, 250));
  mainMenuQuitOption.setPosition(((window.getSize().x / 2) + (mainMenuQuitOption.getGlobalBounds().width) * 0.5),450);

}

void MainMenu::update(float dt)
{

}

void MainMenu::render()
{
  window.draw(mainMenuIntroText);
  window.draw(mainMenuPlayOption);
  window.draw(mainMenuQuitOption);
}

void MainMenu::keyPressed(sf::Event event)
{
  if ((event.key.code == sf::Keyboard::A) || (event.key.code == sf::Keyboard::D))
  {
    mainMenuPlaySelected = !mainMenuPlaySelected;

    if (mainMenuPlaySelected)
    {
      mainMenuPlayOption.setString(">Play ");
      mainMenuQuitOption.setString("  Quit");
    }

    else
    {
      mainMenuPlayOption.setString("Play ");
      mainMenuQuitOption.setString(" >Quit");
    }
  }
}

