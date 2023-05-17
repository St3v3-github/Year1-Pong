#ifndef PONGSFML_BALL_H
#define PONGSFML_BALL_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Ball
{
 public:
  Ball(sf::RenderWindow &window);
  ~Ball();

  bool init();
  void update(float dt);
  void render();
  void spawn();

  sf::RenderWindow &window;

  sf::Sprite ball;
  sf::Texture ball_texture;

  float ball_speed = 450;
  bool ball_move_right = true;
  bool ball_move_up = true;
};

#endif // PONGSFML_BALL_H
