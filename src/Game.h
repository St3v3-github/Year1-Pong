
#ifndef PONG_GAME_H
#define PONG_GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ball.h"
#include "Paddle.h"

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


 private:
  sf::RenderWindow& window;

  sf::Sprite background;

  Ball *ball = nullptr;
  Paddle *paddle = nullptr;
  Paddle *paddle2 = nullptr;

  sf::Font font;
  sf::Text title_text;
  sf::Text quit_text;

  //bool in_menu;  //the old menu change bool
  //The below enum controls the new menu navigation
  //better - able to scale better if/when more menus are required

  enum MenuEnum
  {mainMenu, gameplay};

  MenuEnum Menu = mainMenu;

  bool play_selected = true;
  sf::Text menu_text;
  sf::Text play_option;
  sf::Text quit_option;

  sf::Text red_score_text;
  sf::Text blue_score_text;
  std::string red_score_str;
  std::string blue_score_str;
  int red_score = 0;
  int blue_score = 0;
};

#endif // PONG_GAME_H
