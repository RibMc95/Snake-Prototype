#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <deque>
#include <vector>

enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Snake
{
private:
    std::deque<sf::Vector2i> body; // Snake segments (grid positions)
    Direction direction;
    Direction next_direction;
    int segment_size;
    sf::Color snake_color;

public:
    // Constructor
    Snake(sf::Vector2i start_pos, int seg_size = 20)
        : direction(Direction::RIGHT), next_direction(Direction::RIGHT),
          segment_size(seg_size), snake_color(sf::Color::Green)
    {
        // Initialize snake with 3 segments
        body.push_back(start_pos);
        body.push_back({start_pos.x - 1, start_pos.y});
        body.push_back({start_pos.x - 2, start_pos.y});
    }

    // Move the snake
    void move()
    {
        direction = next_direction;

        sf::Vector2i head = body.front();
        sf::Vector2i new_head = head;

        switch (direction)
        {
        case Direction::UP:
            new_head.y--;
            break;
        case Direction::DOWN:
            new_head.y++;
            break;
        case Direction::LEFT:
            new_head.x--;
            break;
        case Direction::RIGHT:
            new_head.x++;
            break;
        }

        body.push_front(new_head); // Add new head
        body.pop_back();           // Remove tail (unless growing)
    }

    // Grow the snake (don't remove tail this time)
    void grow()
    {
        sf::Vector2i head = body.front();
        sf::Vector2i new_head = head;

        switch (direction)
        {
        case Direction::UP:
            new_head.y--;
            break;
        case Direction::DOWN:
            new_head.y++;
            break;
        case Direction::LEFT:
            new_head.x--;
            break;
        case Direction::RIGHT:
            new_head.x++;
            break;
        }

        body.push_front(new_head); // Add new head, keep tail
    }

    // Set direction (with validation to prevent reversing)
    void setDirection(Direction new_dir)
    {
        if ((direction == Direction::UP && new_dir != Direction::DOWN) ||
            (direction == Direction::DOWN && new_dir != Direction::UP) ||
            (direction == Direction::LEFT && new_dir != Direction::RIGHT) ||
            (direction == Direction::RIGHT && new_dir != Direction::LEFT))
        {
            next_direction = new_dir;
        }
    }

    // Get head position
    sf::Vector2i getHead() const
    {
        return body.front();
    }

    // Get tail position
    sf::Vector2i getTail() const
    {
        return body.back();
    }

    // Get all body segments
    const std::deque<sf::Vector2i> &getBody() const
    {
        return body;
    }

    // Check if snake collides with itself
    bool checkSelfCollision() const
    {
        sf::Vector2i head = body.front();
        for (auto it = body.begin() + 1; it != body.end(); ++it)
        {
            if (head == *it)
            {
                return true;
            }
        }
        return false;
    }

    // Check if position is occupied by snake
    bool occupiesPosition(sf::Vector2i pos) const
    {
        for (const auto &segment : body)
        {
            if (segment == pos)
            {
                return true;
            }
        }
        return false;
    }

    // Get snake length
    size_t getLength() const
    {
        return body.size();
    }

    // Draw the snake
    void draw(sf::RenderWindow &window) const
    {
        sf::RectangleShape segment(sf::Vector2f(segment_size - 1, segment_size - 1));
        segment.setFillColor(snake_color);

        for (size_t i = 0; i < body.size(); ++i)
        {
            // Make head slightly different color
            if (i == 0)
            {
                segment.setFillColor(sf::Color(0, 150, 0)); // Darker green for head
            }
            else
            {
                segment.setFillColor(snake_color);
            }

            segment.setPosition(
                body[i].x * segment_size,
                body[i].y * segment_size);
            window.draw(segment);
        }
    }

    // Reset snake to initial state
    void reset(sf::Vector2i start_pos)
    {
        body.clear();
        body.push_back(start_pos);
        body.push_back({start_pos.x - 1, start_pos.y});
        body.push_back({start_pos.x - 2, start_pos.y});
        direction = Direction::RIGHT;
        next_direction = Direction::RIGHT;
    }
};

#endif // SNAKE_H
