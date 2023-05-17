//
// Created by Steven on 05/01/2022.
//
#include "Paddle.h"

Paddle::Paddle(sf::RenderWindow &window, bool _is_on_left): window(window)
{
  is_on_left = _is_on_left;
  init();
}

Paddle::~Paddle()
{

}

bool Paddle::init()
{
  //init red_paddle
  if (is_on_left)
  {
    if (!paddle_texture.loadFromFile("Data/Images/paddleRed.png"))
    {
      std::cout << "The Red Paddle Texture didn't load in :( \n";
    }

    paddle.setPosition(200, 500);
  }

  //init blue_paddle
  if (!is_on_left)
  {
    if (!paddle_texture.loadFromFile("Data/Images/paddleBlue.png"))
    {
      std::cout << "The Blue Paddle Texture didn't load in :( \n";
    }
    paddle.setPosition(1700, 500);
  }

  paddle.setTexture(paddle_texture);

  return false;
}

void Paddle::update(float dt)
{
  if (paddle.getPosition().y > (window.getSize().y - paddle.getGlobalBounds().height))
  {
    paddle.move(0, -2 * paddle_speed * dt);
  }

  if (paddle.getPosition().y < 0)
  {
    paddle.move(0, 2 * paddle_speed * dt);
  }

  else
  {
    paddle.move(0, paddle_direction.y * paddle_speed * dt);
  }

}

void Paddle::render()
{
    window.draw(paddle);
}

void Paddle::keyPressed(sf::Event event)
{
  if (is_on_left)
  {
    if (event.key.code == sf::Keyboard::W)
    {
      paddle_direction.y = -1;
    }

    if (event.key.code == sf::Keyboard::S)
    {
      paddle_direction.y = 1;
    }
  }

  if (!is_on_left)
  {
    if (event.key.code == sf::Keyboard::Up)
    {
      paddle_direction.y = -1;
    }

    if (event.key.code == sf::Keyboard::Down)
    {
      paddle_direction.y = 1;
    }
  }
}

void Paddle::keyReleased(sf::Event event)
{
  if (is_on_left)
  {
    if ((event.key.code == sf::Keyboard::W) || (event.key.code == sf::Keyboard::S))
    {
      paddle_direction.y = 0;
    }
  }

  if (!is_on_left)
  {
    if ((event.key.code == sf::Keyboard::Up) || (event.key.code == sf::Keyboard::Down))
    {
      paddle_direction.y = 0;
    }
  }
}