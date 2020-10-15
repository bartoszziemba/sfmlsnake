#include <SFML/Graphics.hpp>
#include "snake.hpp"


int main()
{
    srand(time(nullptr));

    sf::RenderWindow window(sf::VideoMode(800, 800), "River snake");
    window.setFramerateLimit(15);
    snake sn;
    sf::Font font;
    font.loadFromFile("./fonts/arial.ttf");
    sf::Text scoreText("Score: 0",font);
    scoreText.setPosition(0,0);

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                sn.input(event.key.code);
            }
        }

        sn.tick();

        window.clear();

        sn.draw(window);
        scoreText.setString("Score: "+std::to_string(sn.score));
        window.draw(scoreText);

        window.display();
    }

    return 0;
}