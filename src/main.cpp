#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <format>
#include <string>

int main() {

  constexpr auto WINDOW_WIDTH = 800;
  constexpr auto WINDOW_HEIGHT = 600;
  constexpr auto WINDOW_TITLE = "Pong";
  constexpr auto WINDOW_STYLE = sf::Style::Close;
  const auto WINDOW_DIMENSION = sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT});
  constexpr auto WINDOW_STATE = sf::State::Windowed;

  sf::RenderWindow window(WINDOW_DIMENSION, WINDOW_TITLE, WINDOW_STYLE,
                          WINDOW_STATE);

  sf::RectangleShape middleLine({1, WINDOW_HEIGHT});
  middleLine.setPosition(
      {(static_cast<float>(WINDOW_WIDTH) / 2) - (middleLine.getSize().x / 2),
       0});

  constexpr auto WINDOW_POSITION = sf::Vector2i(30, 30);
  window.setPosition(WINDOW_POSITION);

  constexpr auto FRAMERATE = 60;
  window.setFramerateLimit(FRAMERATE);

  const auto WINDOW_ICON = sf::Image("assets/logo.png");
  window.setIcon(WINDOW_ICON);

  constexpr auto PADDLE_SIZE = sf::Vector2f(20, 100);
  sf::RectangleShape paddle1(PADDLE_SIZE);
  sf::RectangleShape paddle2(PADDLE_SIZE);

  constexpr auto PLAYER_POSITION =
      sf::Vector2f(0, (WINDOW_HEIGHT / 2.F) - (PADDLE_SIZE.y / 2.F));
  paddle1.setPosition(PLAYER_POSITION);

  constexpr auto OPPONENT_POSITION =
      sf::Vector2f(WINDOW_WIDTH - PADDLE_SIZE.x,
                   (WINDOW_HEIGHT / 2.F) - (PADDLE_SIZE.y / 2.F));
  paddle2.setPosition(OPPONENT_POSITION);

  paddle1.setFillColor(sf::Color::Green);
  paddle2.setFillColor(sf::Color::Red);

  constexpr auto BALL_SIZE = sf::Vector2f(20, 20);
  const auto split = 2.F;
  sf::Vector2f BALL_POSITION((WINDOW_WIDTH / split) - (BALL_SIZE.x / 2),
                             (WINDOW_HEIGHT / split) - (BALL_SIZE.y / 2));
  sf::Vector2f ORIGINAL_POSITION((WINDOW_WIDTH / split) - (BALL_SIZE.x / 2),
                                 (WINDOW_HEIGHT / split) - (BALL_SIZE.y / 2));

  sf::RectangleShape ball(BALL_SIZE);
  ball.setPosition(BALL_POSITION);
  ball.setFillColor(sf::Color::White);

  sf::Vector2i direction(1, 1);

  float paddle2Y = 0.F;
  float paddle1Y = 0.F;

  constexpr auto PLAYER_SPEED_DOWN = sf::Vector2f(0, 5);
  constexpr auto PLAYER_SPEED_UP = sf::Vector2f(0, -5);

  auto yourScore = 0;
  auto opponentScore = 0;

  const sf::Font scoreFont("assets/JetBrainsMono-Bold.ttf");
  constexpr unsigned fontSize = 40;

  std::string yourScoreString;
  std::string opponentScoreString;

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
    window.draw(middleLine);

    yourScoreString = std::format("{}", yourScore);
    opponentScoreString = std::format("{}", opponentScore);

    sf::Text yourScoreText(scoreFont, yourScoreString, fontSize);
    sf::Text otherScoreText(scoreFont, opponentScoreString, fontSize);

    window.draw(yourScoreText);

    otherScoreText.setPosition(
        {static_cast<float>(WINDOW_WIDTH) - fontSize, 0});
    window.draw(otherScoreText);

    // Player paddle movement
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) ||
         sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) &&
        (paddle1.getPosition().y > 0)) {
      paddle1.move(PLAYER_SPEED_UP);
    } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) &&
               (paddle1.getPosition().y < (WINDOW_HEIGHT - PADDLE_SIZE.y))) {
      paddle1.move(PLAYER_SPEED_DOWN);
    }

    // Opponent paddle movement, currently follows the balls center, no speed
    // assigned as of yet
    if (BALL_POSITION.y < WINDOW_HEIGHT - PADDLE_SIZE.y / 2 &&
        BALL_POSITION.y > PADDLE_SIZE.y / 2) {
      paddle2.setPosition(sf::Vector2f(OPPONENT_POSITION.x,
                                       BALL_POSITION.y - (PADDLE_SIZE.y / 2)));
    }

    BALL_POSITION.x += static_cast<float>(direction.x * 1.0);
    BALL_POSITION.y += static_cast<float>(direction.y * 1.0);

    paddle2Y = paddle2.getPosition().y;
    paddle1Y = paddle1.getPosition().y;
    if ((BALL_POSITION.x >= WINDOW_WIDTH - (PADDLE_SIZE.x + BALL_SIZE.x)) &&
        (BALL_POSITION.y >= paddle2Y &&
         BALL_POSITION.y <= paddle2Y + PADDLE_SIZE.y)) {
      direction.x = -1;
    } else if ((BALL_POSITION.x <= PADDLE_SIZE.x) &&
               (BALL_POSITION.y >= paddle1Y &&
                BALL_POSITION.y <= paddle1Y + PADDLE_SIZE.y)) {
      direction.x = 1;
    } else if (BALL_POSITION.x < 0) {
      opponentScore += 1;
      BALL_POSITION = ORIGINAL_POSITION;
    } else if (BALL_POSITION.x > WINDOW_WIDTH) {
      yourScore += 1;
      BALL_POSITION = ORIGINAL_POSITION;
    } else if (BALL_POSITION.y < 0) {
      direction.y = +1;
    } else if (BALL_POSITION.y > WINDOW_HEIGHT - BALL_SIZE.y) {
      direction.y = -1;
    }
    ball.setPosition(BALL_POSITION);

    window.display();
  }

  return 0;
}
