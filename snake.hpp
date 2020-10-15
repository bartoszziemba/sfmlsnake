#include <list>
#include <SFML/Graphics.hpp>
#include <iostream>

enum direction
{
    up,
    down,
    left,
    right
};

class snake{

    public:
        snake();   
        void tick();
        void draw(sf::RenderWindow&);
        void input(const sf::Keyboard::Key&);
        int score;

    private:
        std::list<sf::RectangleShape> segments;
        sf::RectangleShape fruit;

        direction dir = up;
        direction next_dir = up;
        int segment_size = 20;

        void change_direction(direction);
        void move_snake();
        void grow();
        void eat();
        void die();
        void new_fruit();
        void check_fruit();
        void check_collision();

};