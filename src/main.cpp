#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH (800)
#define WINDOW_HEIGHT (600)
#define WINDOW_TITLE ("Pong")
#define WINDOW_STYLE (sf::Style::Titlebar | sf::Style::Close)
#define WINDOW_STATE (sf::State::Windowed)
#define WINDOW_DIMENSION (sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}))
#define WINDOW_POSITION (sf::Vector2i(30, 30))
#define FRAMERATE (60)
#define PADDLE_SIZE (sf::Vector2f(20, 100))
#define OPPONENT_POSITION (sf::Vector2f(WINDOW_WIDTH - PADDLE_SIZE.x, WINDOW_HEIGHT / 2 - PADDLE_SIZE.y / 2))
#define PLAYER_POSITION (sf::Vector2f(0, WINDOW_HEIGHT / 2 - PADDLE_SIZE.y / 2))
#define BALL_SIZE (sf::Vector2f(20, 20))
#define BALL_POSITION (sf::Vector2f(WINDOW_WIDTH / 2 - BALL_SIZE.x / 2, WINDOW_HEIGHT / 2 - BALL_SIZE.y / 2))
#define PLAYER_SPEED_UP (sf::Vector2f(0, -5))
#define PLAYER_SPEED_DOWN (sf::Vector2f(0, 5))
#define WINDOW_ICON (sf::Image("assets/logo.png"))

int main()
{
    sf::RenderWindow window(WINDOW_DIMENSION, WINDOW_TITLE, WINDOW_STYLE, WINDOW_STATE);
    window.setPosition(WINDOW_POSITION);
    window.setFramerateLimit(FRAMERATE);
    window.setIcon(WINDOW_ICON);

    sf::RectangleShape paddle1(PADDLE_SIZE);
    sf::RectangleShape paddle2(PADDLE_SIZE);

    paddle1.setPosition(PLAYER_POSITION);
    paddle2.setPosition(OPPONENT_POSITION);

    paddle1.setFillColor(sf::Color::Green);
    paddle2.setFillColor(sf::Color::Red);

    sf::RectangleShape ball(BALL_SIZE);
    ball.setPosition(BALL_POSITION);
    ball.setFillColor(sf::Color::White);

    while (window.isOpen()) {
        while (std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color::Cyan);

        window.draw(paddle1);
        window.draw(paddle2);
        window.draw(ball);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            if (paddle1.getPosition().y > 0) {
                paddle1.move(PLAYER_SPEED_UP);
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            if (paddle1.getPosition().y < (WINDOW_HEIGHT - PADDLE_SIZE.y))
            {paddle1.move(PLAYER_SPEED_DOWN);}
        }


        window.display();
    }




    return 0;
}
