//
// Created by Steven on 04/01/2022.
//
#include "Ball.h"

Ball::Ball(sf::RenderWindow &window): window(window)
{
  init();
}

Ball::~Ball()
{

}

bool Ball::init()
{
  if (!ball_texture.loadFromFile("Data/Images/ballGrey.png"))
  {
    std::cout << "The Ball Texture didn't load in :( \n";
  }

  ball.setTexture(ball_texture);
  ball.setPosition(960, 500);
  ball.setScale(2.5, 2.5);

  return true;
}

void Ball::update(float dt)
{
  if (ball_move_right)
  {
    ball.move(1.0f * ball_speed * dt, 0);
  }

  else
  {
    ball.move(-1.0f * ball_speed * dt, 0);
  }

  if ((ball.getPosition().y > (window.getSize().y - ball.getGlobalBounds().height)) || (ball.getPosition().y < 0))
  {
    ball_move_up = !ball_move_up;
  }

  if (ball_move_up)
  {
    ball.move(0 * ball_speed * dt, 3.0f);
  }

  else
  {
    ball.move(0 * ball_speed * dt, -3.0f);
  }
}

void Ball::render()
{
  window.draw(ball);
}

void Ball::spawn()
{
//  sf::sleep(sf::seconds(50 * dt));  //ball delay doesn't work right
  ball.setPosition(960,500);
}
