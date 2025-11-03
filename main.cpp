#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Food.h"
#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int SEGMENT_SIZE = 20;
const int GRID_WIDTH = WINDOW_WIDTH / SEGMENT_SIZE;
const int GRID_HEIGHT = WINDOW_HEIGHT / SEGMENT_SIZE;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake Game");
    window.setFramerateLimit(10); // Slow down the game

    // Disable vertical sync to avoid the warning (framerate limit is better for this game)
    window.setVerticalSyncEnabled(false);

    // Initialize game objects
    Snake snake({GRID_WIDTH / 2, GRID_HEIGHT / 2}, SEGMENT_SIZE);
    Food food(SEGMENT_SIZE);
    food.generate(GRID_WIDTH, GRID_HEIGHT, snake);

    int score = 0;
    bool game_over = false;

    // Font for score display (optional)
    sf::Font font;
    sf::Text score_text;
    bool font_loaded = false;

    // Try to load a font (optional - game works without it)
    if (font.loadFromFile("arial.ttf") || font.loadFromFile("Roboto-Regular.ttf") ||
        font.loadFromFile("C:/Windows/Fonts/arial.ttf") || font.loadFromFile("C:/Windows/Fonts/calibri.ttf"))
    {
        score_text.setFont(font);
        score_text.setCharacterSize(24);
        score_text.setFillColor(sf::Color::White);
        score_text.setPosition(10, 10);
        font_loaded = true;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // Handle input
            if (event.type == sf::Event::KeyPressed && !game_over)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    snake.setDirection(Direction::UP);
                    break;
                case sf::Keyboard::Down:
                    snake.setDirection(Direction::DOWN);
                    break;
                case sf::Keyboard::Left:
                    snake.setDirection(Direction::LEFT);
                    break;
                case sf::Keyboard::Right:
                    snake.setDirection(Direction::RIGHT);
                    break;
                }
            }

            // Restart game
            if (event.type == sf::Event::KeyPressed && game_over)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    snake.reset({GRID_WIDTH / 2, GRID_HEIGHT / 2});
                    food.generate(GRID_WIDTH, GRID_HEIGHT, snake);
                    score = 0;
                    game_over = false;
                }
            }
        }

        if (!game_over)
        {
            // Move snake
            sf::Vector2i old_head = snake.getHead();

            // Check if snake will eat food
            bool will_eat = false;
            sf::Vector2i next_head = old_head;
            // Calculate next position based on current direction 
            // You might want to add this logic to Snake class

            if (snake.getHead() == food.getPosition())
            {
                snake.grow();
                food.generate(GRID_WIDTH, GRID_HEIGHT, snake);
                score++;
            }
            else
            {
                snake.move();
            }

            // Check collisions
            sf::Vector2i head = snake.getHead();

            // Wall collision
            if (head.x < 0 || head.x >= GRID_WIDTH ||
                head.y < 0 || head.y >= GRID_HEIGHT)
            {
                game_over = true;
            }

            // Self collision
            if (snake.checkSelfCollision())
            {
                game_over = true;
            }
        }

        // Render
        window.clear(sf::Color::Black);

        if (!game_over)
        {
            snake.draw(window);
            food.draw(window);
        }

        // Draw score and game state
        if (font_loaded)
        {
            score_text.setString("Score: " + std::to_string(score));
            if (game_over)
            {
                score_text.setString("Game Over! Score: " + std::to_string(score) + " Press SPACE to restart");
            }
            window.draw(score_text);
        }
        else
        {
            // Simple visual feedback without fonts
            if (game_over)
            {
                // Draw a red overlay to indicate game over
                sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
                overlay.setFillColor(sf::Color(255, 0, 0, 50)); // Semi-transparent red
                window.draw(overlay);
            }
        }

        window.display();
    }

    return 0;
}