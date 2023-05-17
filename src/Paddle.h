#ifndef PONGSFML_PADDLE_H
#define PONGSFML_PADDLE_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Paddle
{
 public:
  Paddle(sf::RenderWindow &window, bool _is_on_left);
  ~Paddle();

  bool init();
  void update(float dt);
  void render();
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);

  sf::RenderWindow &window;

  float paddle_speed = 500;

  sf::Sprite paddle;
  sf::Texture paddle_texture;
  sf::Vector2f paddle_direction = {0,0};

  bool is_on_left;
};

#endif // PONGSFML_PADDLE_H
