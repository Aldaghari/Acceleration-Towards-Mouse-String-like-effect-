#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Ball
{
private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float radius;
    sf::Color color;
    sf::CircleShape shape;

public:
    Ball(sf::RenderWindow& window, float r) : position(window.getSize().x / 2, window.getSize().y / 2), velocity (0.0f, 0.0f),
        acceleration(0.0f, 0.0f), radius(r), color (sf::Color::White)
    {
        shape.setOrigin(radius, radius);
        shape.setPosition(position);
        shape.setRadius(radius);
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineThickness(1.0f);
        shape.setOutlineColor(color);
    }

    void accelerationTowardMouse(sf::Mouse& mouse, sf::RenderWindow& window)
    {
        sf::Vector2f directionVector = ((sf::Vector2f) mouse.getPosition(window)) - position;
        float directionMag = sqrt(directionVector.x * directionVector.x + directionVector.y * directionVector.y);
        sf::Vector2f directionVectorNorm = directionVector / directionMag;
       
        //velocity = sf::Vector2f(directionVector.x / 20.0f, directionVector.y / 20.0f);
        velocity = directionVectorNorm;

        acceleration += velocity;
        //acceleration = sf::Vector2f(directionVector.x / 20.0f, directionVector.y / 20.0f);
        //std::cout << "X: " << acceleration.x << " Y: " << acceleration.y << std::endl;

    }

    void move()
    {        
        velocity += acceleration;
        position += velocity;
        std::cout << "X: " << velocity.x << " Y: " << velocity.y << std::endl;
        shape.setPosition(position);

    }

    sf::CircleShape const getShape() { return shape; }

};


int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "My window");
    window.setFramerateLimit(60);

    Ball ball(window, 20.0f);
    sf::Mouse mouse;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }


        // == Update ==
        ball.accelerationTowardMouse(mouse, window);
        ball.move();



        // == Draw ==
        window.clear(sf::Color::Black);
        window.draw(ball.getShape());
        window.display();


    }



    return 0;
}