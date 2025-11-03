#ifndef FOOD_H
#define FOOD_H

#include <SFML/Graphics.hpp>
#include <random>

class Food
{
private:
    sf::Vector2i position;
    int segment_size;
    sf::Color food_color;
    std::mt19937 rng;

public:
    Food(int seg_size = 20)
        : segment_size(seg_size), food_color(sf::Color::Red), rng(std::random_device{}())
    {
    }

    // Generate food at random position
    void generate(int grid_width, int grid_height, const class Snake &snake)
    {
        std::uniform_int_distribution<int> dist_x(0, grid_width - 1);
        std::uniform_int_distribution<int> dist_y(0, grid_height - 1);

        do
        {
            position = {dist_x(rng), dist_y(rng)};
        } while (snake.occupiesPosition(position));
    }

    // Get food position
    sf::Vector2i getPosition() const
    {
        return position;
    }

    // Draw the food
    void draw(sf::RenderWindow &window) const
    {
        sf::CircleShape food_shape(segment_size / 2.0f - 1);
        food_shape.setFillColor(food_color);
        food_shape.setPosition(
            position.x * segment_size + 1,
            position.y * segment_size + 1);
        window.draw(food_shape);
    }
};

#endif // FOOD_H