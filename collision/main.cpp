#include <vector>
#include "circle.hpp"
#include "utils.hpp"

int main()
{
	std::srand((unsigned int)time(nullptr));	// Seed randomness

	const int WIDTH = 1280;
	const int HEIGHT = 720;
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Collision");
	window.setFramerateLimit(60);

	sf::Clock deltaClock;	// Used for delta time

	// Vector that stores all created shapes
	std::vector<Circle> circles;

	while(window.isOpen())
	{
		// Delta time calculations
		sf::Time dt = deltaClock.restart();
		float deltaTime = dt.asSeconds();

		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
			if(event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
			{
				sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
				circles.emplace_back(float(rand() % 30 + 30), mousePos);
			}
		}

		if(circles.size() > 0)
		{
			// Check collisions between all shapes
			for(size_t i = 0; i < circles.size() - 1; i++)
			for(size_t j = i + 1; j < circles.size(); j++)
			{
				Circle& c1 = circles[i];
				Circle& c2 = circles[j];

				if(CheckOverlap(c1, c2))
				{
					sf::Vector2f delta = c1.center - c2.center;
					delta += sf::Vector2f(1.0f, 1.0f);
					delta /= Length(delta);

					sf::Vector2f midPoint = (c1.center + c2.center) / 2.0f;
					c1.center = midPoint + c1.radius * delta;
					c2.center = midPoint - c2.radius * delta;
				}
			}
		}

		window.clear();
		for(auto& c : circles)
		{
			sf::CircleShape circleShape(c.radius);
			circleShape.setOrigin(c.radius, c.radius);
			circleShape.setPosition(c.center);
			circleShape.setFillColor(sf::Color(c.color.x, c.color.y, c.color.z, 255));
			window.draw(circleShape); // Draw shape
		}
		window.display();
	}

	return 0;
}