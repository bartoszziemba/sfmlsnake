#include "snake.hpp"

snake::snake()
{
    segments.clear();
    score = 0;

    sf::RectangleShape segment(sf::Vector2f(segment_size, segment_size));
    segment.setFillColor(sf::Color::Yellow);
    segment.setOutlineColor(sf::Color::Black);
    segment.setOutlineThickness(-3.f);
    segment.setPosition(400, 400);

    segments.push_back(segment);

    fruit = sf::RectangleShape(sf::Vector2f(segment_size, segment_size));
    fruit.setFillColor(sf::Color::Green);
    new_fruit();
}

void snake::tick()
{
    dir = next_dir;
    move_snake();
    check_collision();
    check_fruit();
}

void snake::input(const sf::Keyboard::Key &key)
{
    if (key == sf::Keyboard::A)
        change_direction(left);
    if (key == sf::Keyboard::D)
        change_direction(right);
    if (key == sf::Keyboard::W)
        change_direction(up);
    if (key == sf::Keyboard::S)
        change_direction(down);
//    if (key == sf::Keyboard::G)
//        grow();
}

void snake::change_direction(direction k)
{
    if (k == up and dir != down)
        next_dir = k;
    if (k == down and dir != up)
        next_dir = k;
    if (k == left and dir != right)
        next_dir = k;
    if (k == right and dir != left)
        next_dir = k;
}

void snake::draw(sf::RenderWindow &window)
{
    for (auto &s : segments)
        window.draw(s);
    window.draw(fruit);
}

void snake::move_snake()
{

    sf::RectangleShape &head = segments.front();
    sf::Vector2f headPos = head.getPosition();


    if (segments.size() != 1)
    {
        sf::RectangleShape last = segments.back();

        last.setPosition(headPos);
        last.setOutlineThickness(head.getOutlineThickness());
        segments.pop_back();
        segments.insert(std::next(segments.begin()), last);
    }

    head.setOutlineThickness(-3.f);



    if (dir == up)
        headPos += sf::Vector2f(0, -20);
    if (dir == down)
        headPos += sf::Vector2f(0, 20);
    if (dir == left)
        headPos += sf::Vector2f(-20, 0);
    if (dir == right)
        headPos += sf::Vector2f(20, 0);

    if (headPos.x >= 800)
        headPos = sf::Vector2f(0, headPos.y);
    if (headPos.y >= 800)
        headPos = sf::Vector2f(headPos.x, 0);
    if (headPos.y < 0)
        headPos = sf::Vector2f(headPos.x, 780);
    if (headPos.x < 0)
        headPos = sf::Vector2f(780, headPos.y);

    head.setPosition(headPos);
}

void snake::check_collision()
{
    sf::RectangleShape &head = segments.front();
    std::list<sf::RectangleShape>::iterator it = ++segments.begin();
    for (; it != segments.end(); ++it)
        if ((*it).getPosition() == head.getPosition())
        {
            die();
            break;
        }
}

void snake::check_fruit()
{
    sf::RectangleShape &head = segments.front();

    if (head.getPosition() == fruit.getPosition())
    {
        head.setOutlineThickness(-1.f);
        eat();
    }
}
void snake::die()
{

    std::cout << "snake died\n";
    score = 0;
    while (segments.size() > 1)
        segments.pop_back();
}

void snake::eat()
{
    grow();
    score+=1;
    new_fruit();
}

void snake::grow()
{
    sf::RectangleShape &head = segments.front();

    sf::RectangleShape segment(sf::Vector2f(segment_size, segment_size));
    segment.setFillColor(sf::Color::Red);
    segment.setOutlineColor(sf::Color::Black);
    segment.setOutlineThickness(-3.f);
    segment.setPosition(segments.back().getPosition());

    segments.push_back(segment);
}

void snake::new_fruit()
{
    do
    {
        fruit.setPosition(rand() % 40 * 20, rand() % 40 * 20);
    } while (fruit.getPosition() == segments.front().getPosition());
}
