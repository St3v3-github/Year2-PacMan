//
// Created by Steven on 27/11/2022.
//
#include "GameOverMenu.h"

GameOverMenu::GameOverMenu(sf::RenderWindow &window): window(window)
{
  //init();
}

GameOverMenu::~GameOverMenu() = default;

bool GameOverMenu::init()
{
  // init Font
  if (!font.loadFromFile("../Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "The Font didn't load in :( \n";
  }

  gameOverWinText.setString("You Win!");
  gameOverWinText.setFont(font);
  gameOverWinText.setCharacterSize(75);
  gameOverWinText.setFillColor(sf::Color(250, 250, 250));
  gameOverWinText.setPosition(((window.getSize().x / 2) - (gameOverWinText.getGlobalBounds().width) / 2),200);

  gameOverLoseText.setString("Game Over :(");
  gameOverLoseText.setFont(font);
  gameOverLoseText.setCharacterSize(75);
  gameOverLoseText.setFillColor(sf::Color(250, 250, 250));
  gameOverLoseText.setPosition(((window.getSize().x / 2) -(gameOverLoseText.getGlobalBounds().width) / 2),200);


  gameOverPlayOption.setString("Replay?");
  gameOverPlayOption.setFont(font);
  gameOverPlayOption.setCharacterSize(20);
  gameOverPlayOption.setFillColor(sf::Color(250, 250, 250));
  gameOverPlayOption.setPosition(((window.getSize().x / 2) - (gameOverPlayOption.getGlobalBounds().width)),450);

  gameOverQuitOption.setString("Quit");
  gameOverQuitOption.setFont(font);
  gameOverQuitOption.setCharacterSize(20);
  gameOverQuitOption.setFillColor(sf::Color(250, 250, 250));
  gameOverQuitOption.setPosition(((window.getSize().x / 2) + (gameOverQuitOption.getGlobalBounds().width) * 0.5),450);

  score_str = std::to_string(score);
  ScoreText.setString("Points:  " + score_str);
  ScoreText.setFont(font);
  ScoreText.setCharacterSize(25);
  ScoreText.setFillColor(sf::Color(250, 250, 250));
  ScoreText.setPosition(50, 600);

}

void GameOverMenu::update(float dt)
{
  score_str = std::to_string(score);
  ScoreText.setString("Points:  " + score_str);
}

void GameOverMenu::render()
{
  if (gameWon)
  {
    window.draw(gameOverWinText);
  }

  else
  {
    window.draw(gameOverLoseText);
  }

  window.draw(gameOverTitleText);
  window.draw(gameOverPlayOption);
  window.draw(gameOverQuitOption);
  window.draw(ScoreText);
}

void GameOverMenu::keyPressed(sf::Event event)
{
  if ((event.key.code == sf::Keyboard::A) || (event.key.code == sf::Keyboard::D))
  {
    gameOverPlaySelected = !gameOverPlaySelected;

    if (gameOverPlaySelected)
    {
      gameOverPlayOption.setString(">Replay? ");
      gameOverQuitOption.setString("  Quit");
    }

    else
    {
      gameOverPlayOption.setString("Replay? ");
      gameOverQuitOption.setString(" >Quit");
    }
  }
}
