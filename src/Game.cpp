#include "Game.h"
#include <iostream>
#include <tmxlite/TileLayer.hpp>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
    ////smart pointers
    mainMenu = std::make_unique<MainMenu>(game_window);
    gameOverMenu = std::make_unique<GameOverMenu>(game_window);

    player = std::make_unique<Player>(game_window);

    // coin = std::make_unique<Coin>(game_window);
    //enemy = std::make_unique<Enemy>(game_window);
    ////tried, but couldn't get smart pointers to play nicely with arrays
    ////used classic pointer instead ~>

    ////coin pointer
    for (int i = 0; i < 30; i++)
    {
      coin_array[i] = new Coin(game_window);
    }

    ////enemy pointer
    for (int j = 0; j < 4; j++)
    {
      enemy_array[j] = new Enemy(game_window);
    }
}


Game::~Game()
{
  ////memory management
  for (int i = 0; i < 30; i++)
  {
    delete coin_array[i];
  }

  for (int j = 0; j < 4; j++)
  {
    delete enemy_array[j];
  }
}


bool Game::init()
{
  ////pointer inits
  mainMenu->init();
  gameOverMenu->init();

  player->init();

  for (int i = 0; i < 30; i++)
  {
    coin_array[i]->init();
    coin_array[i]->setPosition(coin_data[i][0], coin_data[i][1]);
  }

  for (int j = 0; j < 4; j++)
  {
    enemy_array[j]->init();
  }

  //// init Game Music
  if (!tunes.openFromFile(
        "../Data/Audio/Eggy-Toast-Enemies-of-the-People.ogg"))
  {
    std::cout <<  "Game Audio didn't load in :( \n";
  }
  tunes.setLoop(true);
  tunes.setVolume(100);
  tunes.play();

  ///lives stuff init
  Lives_string = std::to_string(Lives_Counter);
  Lives_Text.setString("Lives: " + Lives_string);
  Lives_Text.setFont(font);
  Lives_Text.setCharacterSize(25);
  Lives_Text.setFillColor(sf::Color(250, 250, 250));
  Lives_Text.setPosition(300, 600);

  ////old tilemap load
  //  if(!tileMap.loadFromFile("../Data/tiledProject/platformerart_pixelredux_2/Tilemap/tilemap_packed.png"))
  //  {
  //    std::cout << "Failed to load tileMap" << std::endl;
  //  }

  ////Tile map stuff
  ////Could probably throw all this in a tile class??
  if (!map.load("../Data/tiledProject/Map.tmx"))
  {
    std::cout << "Failed to load map" << std::endl;
  }

  const auto& layers = map.getLayers();
  const auto layer0  = layers[0]->getLayerAs<tmx::TileLayer>();
  const auto& tiles0 = layer0.getTiles();

  for (auto& tileSet : map.getTilesets())
  {
    if (!tileMap.loadFromFile(
          tileSet.getImagePath(),
          sf::IntRect{ 0,
                       0,
                       static_cast<int>(tileSet.getImageSize().x),
                       static_cast<int>(tileSet.getImageSize().y) }))
    {
      std::cout << "Failed to Load Tilemap" << std::endl;
    }

    for (int x = 0; x < layer0.getSize().x; x++)
    {
      for (int y = 0; y < layer0.getSize().y; y++)
      {
        int id = tiles0.at((y * layer0.getSize().x) + x).ID;

        if (id == 640)
        {
          sf::IntRect rect;

          rect.top    = tileSet.getTile(id)->imagePosition.y;
          rect.left   = tileSet.getTile(id)->imagePosition.x;
          rect.width  = tileSet.getTile(id)->imageSize.x;
          rect.height = tileSet.getTile(id)->imageSize.y;

          auto& sprite =
            wallSprites.emplace_back(std::make_unique<sf::Sprite>());

          // sets up sprite for each tile as its corresponding rect within the tile-map
          sprite->setTexture(tileMap);
          sprite->setTextureRect(rect);
          sprite->setPosition(x * TILE_WIDTH, y * TILE_HEIGHT);
        }
      }
    }
  }
  return true;
}


void Game::update(float dt)
{
  switch (current_state)
  {
    case gamePlayState:
    {
      //// pointer updates
      gameOverMenu->update(dt);
      player->update(dt);

      for (int j = 0; j < 4; j++)
      {
        enemy_array[j]->update(dt);
      }

      ////life counter
      //// [Lives = 0] game over condition
      Lives_string = std::to_string(Lives_Counter);
      Lives_Text.setString("Lives:  " + Lives_string);

      if (Lives_Counter == 0)
      {
        gameOverMenu->gameWon = false;
        current_state         = gameOverState;
      }

      ////player/enemy collision
      for (int j = 0; j < 4; j++)
      {
        if (spriteCollisionCheck(player->player, enemy_array[j]->enemy))
        {
          gameReset();
          Lives_Counter--;
        }
      }

      ////player/wall collision
      for (auto& Sprite : wallSprites)
      {
        if (spriteCollisionCheck(player->player, *Sprite))
        {
          // std::cout << "hit" << std::endl; ////Troubleshooting
          player->wallBounce();

          ////variables to help me bounce the sprite out of the wall to stop it getting stuck
          player->moveUp    = false;
          player->moveDown  = false;
          player->moveLeft  = false;
          player->moveRight = false;
        }

        ////enemy/wall collision
        for (int j = 0; j < 4; j++)
        {
          if (spriteCollisionCheck(*Sprite, enemy_array[j]->enemy))
          {
            enemy_array[j]->moveRight = !enemy_array[j]->moveRight;
            //            enemy_array[j]->moveUp = !enemy_array[j]->moveUp;
          }
        }
      }

      ////player/coin collision
      for (int i = 0; i < 30; i++)
      {
        if (coin_array[i]->getIsVisible())
        {
          if (spriteCollisionCheck(player->player, coin_array[i]->coin))
          {
            coin_array[i]->setIsVisible(false);
            gameOverMenu->score++;

            if (gameOverMenu->score == 30)
            {
              gameOverMenu->gameWon = true;
              current_state         = gameOverState;
            }
          }
        }
      }
    }
  }
}

void Game::render()
{
  switch (current_state)
  {
    case mainMenuState:
    {
      mainMenu->render();

      window.draw(TitleText);
      window.draw(menu_Instructions);
    }
    break;

    case gamePlayState:
    {       ////old way of drawing tile sprites - array before new vector implementation
      //  for (int i = 0; i < 26; ++i)
      //  {
      //    for (int j = 0; j < 27; ++j)
      //    {
      //      window.draw(tileSprite0[i][j]);
      //    }
      //  }
      for (auto& Sprite : wallSprites)
      {
        window.draw(*Sprite);
      }

      for (int i = 0; i < 30; i++)
      {
        if (coin_array[i]->getIsVisible())
        {
          coin_array[i]->render();
        }
      }

      for (int j = 0; j < 4; j++)
      {
        enemy_array[j]->render();
      }

      player->render();

      window.draw(game_Instructions);
      window.draw(TitleText);
      window.draw(QuitPrompt);
      window.draw(Lives_Text);
      window.draw(gameOverMenu->ScoreText);
    }
    break;

    case gameOverState:
    {
      gameOverMenu->render();
      window.draw(menu_Instructions);
    }
    break;
  }
}


void Game::keyPressed(sf::Event event)
{
  switch (current_state)
  {
    case mainMenuState:
    {
      mainMenu->keyPressed(event);

      if (event.key.code == sf::Keyboard::Enter)
      {
        if (mainMenu->mainMenuPlaySelected)
        {
          gameReset();
          current_state = gamePlayState;
        }

        else
          window.close();
      }
    }
    break;

    case gamePlayState:
    {
      if (event.key.code == sf::Keyboard::Q)
      {
        gameReset();
        current_state = mainMenuState;
      }

      if (event.key.code == sf::Keyboard::W)
      {
        player->player_direction.y = -1;
        player->player_direction.x = 0;
        player->player_speed       = 100;
        player->moveUp             = true;
      }

      if (event.key.code == sf::Keyboard::S)
      {
        player->player_direction.y = 1;
        player->player_direction.x = 0;
        player->player_speed       = 100;
        player->moveDown           = true;
      }

      if (event.key.code == sf::Keyboard::A)
      {
        player->player_direction.x = -1;
        player->player_direction.y = 0;
        player->player_speed       = 100;
        player->moveLeft           = true;
      }

      if (event.key.code == sf::Keyboard::D)
      {
        player->player_direction.x = 1;
        player->player_direction.y = 0;
        player->player_speed       = 100;
        player->moveRight          = true;
      }
    }
    break;

    case gameOverState:
    {
      gameOverMenu->keyPressed(event);

      if (event.key.code == sf::Keyboard::Enter)
      {
        if (gameOverMenu->gameOverPlaySelected)
        {
          gameReset();
          Lives_Counter = 3;
          current_state = gamePlayState;
        }

        else
          window.close();
      }
    }
    break;
  }
}


bool Game::spriteCollisionCheck(sf::Sprite& sprite1, sf::Sprite& sprite2)
{
  if(
    sprite1.getPosition().x <= sprite2.getPosition().x + sprite2.getGlobalBounds().width &&
    sprite1.getPosition().x + sprite1.getGlobalBounds().width >= sprite2.getPosition().x &&
    sprite1.getPosition().y <= sprite2.getPosition().y + sprite2.getGlobalBounds().height &&
    sprite1.getPosition().y + sprite1.getGlobalBounds().height >= sprite2.getPosition().y)
  {
    return true;
  }

  else
  {
    return false;
  }
}


void Game::gameReset()
{
  player->spawn();

  for (int j = 0; j < 4; j++)
  {
    enemy_array[j]->spawn(enemy_data[j][0], enemy_data[j][1]);
  }

  for (int i = 0; i < 30; i++)
  {
    coin_array[i]->setPosition(coin_data[i][0], coin_data[i][1]);
    coin_array[i]->setIsVisible(true);
  }

  gameOverMenu->score = 0;
}


//// some old code below

//bool Game::collisionCheck(sf::Sprite& importSprite)
//{
//  for (const auto& sprites : collisionSprites)
//  {
//    if (sprites->getGlobalBounds().intersects(importSprite.getGlobalBounds()))
//    {
//      if(importSprite.getGlobalBounds().left == sprites->getGlobalBounds().left * sprites->getGlobalBounds().width - 1)
//      {
//        importSprite.setPosition({importSprite.getPosition().x + 1, importSprite.getPosition().y});
//      }
//
//      else if(importSprite.getGlobalBounds().top == sprites->getGlobalBounds().top + sprites->getGlobalBounds().height -1)
//      {
//        importSprite.setPosition(importSprite.getPosition().x, importSprite.getPosition().y + 1);
//      }
//
//      else if(importSprite.getGlobalBounds().left + importSprite.getGlobalBounds().width == sprites->getGlobalBounds().left + 1)
//      {
//        importSprite.setPosition({importSprite.getPosition().x - 1, importSprite.getPosition().y});
//      }
//
//      else if(importSprite.getGlobalBounds().top + importSprite.getGlobalBounds().height == sprites->getGlobalBounds().top + 1)
//      {
//        importSprite.setPosition({importSprite.getPosition().x, importSprite.getPosition().y - 1});
//      }
//
//      std::cout << "wall Collision!" << std::endl;
//      return true;
//    }
//
//    else
//      return false;
//  }
//}

//bool Game::collisionCheck(const sf::Sprite& sprite1, const sf::Sprite& sprite2)
//{
//  for( const auto&sprites : collisionSprites)
//  {
//    if (sprites.getGlobalBounds().intersects(getFutureRect()))
//    {
//      if (player.getTextureRect().left.int)
//    }
//
//  }
//
//}

//bool Game::collisionCheck(const sf::Sprite& sprite1, const sf::Sprite& sprite2)
//{
//  const auto& layers = map.getLayers();
//
//  const auto layer0  = layers[0]->getLayerAs<tmx::TileLayer>();
//  const auto& tiles0 = layer0.getTiles();
//
//  for (int j = 0; j < tiles0.size(); j++)
//  {
//    idx = j / 27;
//    idy = j % 27;
//
//    int x = ((int(tiles0[j].ID) % 30) * 21) - 21;
//    int y = ((int(tiles0[j].ID) / 30) * 21);
//
//    if (sprite1.getPosition().x == ((x == 766) && (y == 766)))
//    {
//      std::cout << "collision!" << std::endl;
//      return true;
//    }
//
//    //    if ()
//    //    {
//    //      std::cout << "collision!" << std::endl;
//    //      return true;
//    //    }
//    //
//    //    if ()
//    //    {
//    //      std::cout << "collision!" << std::endl;
//    //      return true;
//    //    }
//    //
//    //    if ()
//    //    {
//    //      std::cout << "collision!" << std::endl;
//    //      return true;
//    //    }
//
//    else
//    {
//      return false;
//    }
//  }
//}



//bool Game::playerCollision()
//{
//  for (int i = 0; i < 26; ++i)
//  {
//    for (int j = 0; j < 27; ++j)
//    {
//      if (
//        (player.getPosition().x == tileSprite0[i][j].getPosition().x) ||
//        (player.getPosition().y == tileSprite0[i][j].getPosition().y))
//      {
//        player.setPosition(player.getPosition().x, player.getPosition().y);
//        std::cout<<"collision"<<std::endl;
//      }
//    }
//  }
//}


//void Game::mouseClicked(sf::Event event)
//{
//  //get the click position
//  sf::Vector2i click = sf::Mouse::getPosition(window);
//
//
//}