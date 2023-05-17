
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window) : window(game_window)
{
  srand(time(nullptr));
  ball = new Ball(game_window);
  paddle = new Paddle(game_window, true);
  paddle2 = new Paddle(game_window, false);
}

Game::~Game()
{
  delete ball;
  delete paddle;
  delete paddle2;
}

bool Game::init()
{
  //init text
  if(!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
      {
        std::cout <<"The Font didn't load in :( \n";
      }

  if (Menu == mainMenu)
  {
    menu_text.setString("PONG");
    menu_text.setFont(font);
    menu_text.setCharacterSize(100);
    menu_text.setFillColor(sf::Color(240, 240, 240));
    menu_text.setPosition(((window.getSize().x / 2 ) - (menu_text.getGlobalBounds().width)/2),300);

    play_option.setString("Play");
    play_option.setFont(font);
    play_option.setCharacterSize(40);
    play_option.setFillColor(sf::Color(240, 240, 240));
    play_option.setPosition(((window.getSize().x / 2 ) - (play_option.getGlobalBounds().width)),450);

    quit_option.setString("Quit");
    quit_option.setFont(font);
    quit_option.setCharacterSize(40);
    quit_option.setFillColor(sf::Color(240, 240, 240));
    quit_option.setPosition(((window.getSize().x / 2 ) + (quit_option.getGlobalBounds().width) * 0.5),450);
  }

  title_text.setString("PONG");
  title_text.setFont(font);
  title_text.setCharacterSize(50);
  title_text.setFillColor(sf::Color(240, 240, 240));
  title_text.setPosition(((window.getSize().x / 2) - (title_text.getGlobalBounds().width) / 2),10);

  quit_text.setString("Q to Quit");
  quit_text.setFont(font);
  quit_text.setCharacterSize(30);
  quit_text.setFillColor(sf::Color(240, 240, 240));
  quit_text.setPosition(((window.getSize().x / 2) - (quit_text.getGlobalBounds().width) / 2),1010);

  return true;
}

void Game::update(float dt)
{
  if (Menu == gameplay)
  {
    // This first set string is mainly to reset the scores on any restarts
    // - not my most elegant solution, but it works
    // - would be better to have menu objects and create and delete instances as needed
    // - or even score objects and create and delete those as needed
    red_score_str = std::to_string(red_score);
    red_score_text.setString(red_score_str);

    blue_score_str = std::to_string(blue_score);
    blue_score_text.setString(blue_score_str);

    ball->update(dt);
    paddle->update(dt);
    paddle2->update(dt);

    // Collision Calculations
    if (
      (ball->ball.getPosition().x) < (paddle->paddle.getPosition().x + ball->ball.getGlobalBounds().width) &&
      (ball->ball.getPosition().y) > (paddle->paddle.getPosition().y - ball->ball.getGlobalBounds().height) &&
      (ball->ball.getPosition().y) < (paddle->paddle.getPosition().y + ball->ball.getGlobalBounds().height))
    {
      ball->ball_move_right = true;
    }

    if ((ball->ball.getPosition().x) > (paddle2->paddle.getPosition().x - ball->ball.getGlobalBounds().width) &&
      (ball->ball.getPosition().y) > (paddle2->paddle.getPosition().y - ball->ball.getGlobalBounds().height) &&
      (ball->ball.getPosition().y) < (paddle2->paddle.getPosition().y + ball->ball.getGlobalBounds().height))
    {
      ball->ball_move_right = !ball->ball_move_right;
    }

    // scoring
    if (
      ball->ball.getPosition().x >
      (window.getSize().x - ball->ball.getGlobalBounds().width))
    {
      red_score = red_score + 1;

      red_score_str = std::to_string(red_score);
      red_score_text.setString(red_score_str);
      red_score_text.setFont(font);
      red_score_text.setCharacterSize(60);
      red_score_text.setFillColor(sf::Color(255, 0, 0));
      red_score_text.setPosition(200, 10);

      ball->spawn();
      ball->ball_move_right = !ball->ball_move_right;
    }

    if (ball->ball.getPosition().x < 0)
    {
      blue_score = blue_score + 1;

      blue_score_str = std::to_string(blue_score);
      blue_score_text.setString(blue_score_str);
      blue_score_text.setFont(font);
      blue_score_text.setCharacterSize(60);
      blue_score_text.setFillColor(sf::Color(0, 175, 255));
      blue_score_text.setPosition(1700, 10);

      ball->spawn();
      ball->ball_move_right = !ball->ball_move_right;
    }
  }
}

void Game::render()
{
  //render menu
  if (Menu == mainMenu)
  {
    window.draw(background);
    window.draw(menu_text);
    window.draw(play_option);
    window.draw(quit_option);
  }

  //render gameplay
  if (Menu == gameplay)
  {
    window.draw(background);
    window.draw(title_text);
    window.draw(quit_text);
    window.draw(red_score_text);
    window.draw(blue_score_text);

    ball->render();
    paddle->render();
    paddle2->render();


  }
}


void Game::keyPressed(sf::Event event)
{
  //paddle controls - see paddle class
  paddle -> keyPressed(event);
  paddle2 -> keyPressed(event);

  //menu options
  if (Menu == mainMenu)
  {
    if (
      (event.key.code == sf::Keyboard::Left) ||
      (event.key.code == sf::Keyboard::Right))
    {
      play_selected = !play_selected;

      if (play_selected)
      {
        play_option.setString(">Play ");
        quit_option.setString("  Quit");
      }

      else
      {
        play_option.setString("Play  ");
        quit_option.setString(" >Quit");
      }
    }

    else if (event.key.code == sf::Keyboard::Enter)
    {
      if (play_selected)
      {
        Menu = gameplay;
        red_score = 0;
        blue_score = 0;
        ball->spawn();
        paddle->paddle.setPosition(200,500);
        paddle2->paddle.setPosition(1700,500);
      }

      else
      {
        window.close();
      }
    }
  }

  //quit to menu
  else
  {
    if (event.key.code == sf::Keyboard::Q)
    {
      Menu = mainMenu;
    }
  }
}

void Game::keyReleased(sf::Event event)
{
  //paddle controls - see paddle class
  paddle->keyReleased(event);
  paddle2->keyReleased(event);
}