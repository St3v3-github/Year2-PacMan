
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <memory>
#include "ResourceHandler.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <tmxlite/Map.hpp>
#include "cmath"

#include "Player.h"
#include "Enemy.h"
#include "Coin.h"
#include "Menus/GameOverMenu.h"
#include "Menus/MainMenu.h"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();

  bool init();
  void update(float dt);
  void render();

  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);

  bool spriteCollisionCheck(sf::Sprite& sprite1, sf::Sprite& sprite2);
  //bool collisionCheck(sf::Sprite& importSprite);

  void gameReset();

  ////smart pointers
  std::unique_ptr<MainMenu>mainMenu;
  std::unique_ptr<GameOverMenu>gameOverMenu;

  //std::unique_ptr<ResourceHandler> resources;
  std::unique_ptr<Player>player;
  std::unique_ptr<Enemy>enemy;
  //std::unique_ptr<Coin>coin;

  enum StateEnum
  {
    mainMenuState,
    gamePlayState,
    gameOverState
  };

  StateEnum current_state = mainMenuState;

 private:
  sf::RenderWindow& window;

  //// Setting up DT
  sf::Clock clock;
  sf::Time time = clock.restart();
  float dt = time.asSeconds();

  sf::Font font;
  sf::Text TitleText;
  sf::Text QuitPrompt;

  sf::Text menu_Instructions;
  sf::Text game_Instructions;

  ////lives stuff
  int Lives_Counter= 3;
  sf::Text Lives_Text;
  std::string Lives_string;

  //// Setting up Tile Map
  tmx::Map map;
  sf::Texture tileMap;
  //std::vector<std::unique_ptr<sf::Sprite>> tileSprite0;
  //int idx = 0, idy = 0;

  //std::vector<sf::Sprite> baseTileSprites;
  std::vector<std::unique_ptr<sf::Sprite>> wallSprites;
  std::vector<std::unique_ptr<sf::Sprite>> pathSprites;

  static const int TILE_WIDTH = 21;
  static const int TILE_HEIGHT = 21;
  static const int MAP_SIZE = 30;

  ////coin biz
  Coin* coin_array[30];
  float coin_data[30] [2] =
    {
      {50, 45},
      {150, 45},
      {250, 45},
      {300, 45},
      {400, 45},
      {500, 45},

      {50, 170},
      {150, 170},
      {250, 150},
      {300, 150},
      {400, 170},
      {500, 170},

      {50, 255},
      {150, 255},
      {210, 255},
      {340, 255},
      {400, 255},
      {500, 255},

      {50, 340},
      {150, 340},
      {250, 340},
      {300, 340},
      {400, 340},
      {500, 340},

      {50, 485},
      {150, 485},
      {250, 485},
      {300, 485},
      {400, 485},
      {500, 485},
    };

  Enemy* enemy_array[4];
  float enemy_data[4] [2] =
    {
      {45, 45},
      {510, 255},
      {60, 340},
      {340, 485}
    };


  ////music - remember to put sfml openal32.dll in orange cmake folder
  sf::Music tunes;

  ////animation?
  sf::Clock animationClock;

};

#endif // PLATFORMER_GAME_H
