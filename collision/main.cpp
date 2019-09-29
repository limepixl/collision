#include <vector>
#include "polygon.hpp"
#include "circle.hpp"
#include <iostream>

int main()
{
	std::srand((unsigned int)time(nullptr));	// Seed randomness

	const int WIDTH = 1280;
	const int HEIGHT = 720;
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Collision");
	window.setFramerateLimit(60);

	sf::Clock deltaClock;	// Used for delta time

	// Vector that stores all created shapes
	std::vector<Circle> circles
	{
		Circle(50.0f, sf::Vector2f(WIDTH / 4.0f, HEIGHT / 2.0f)),
		Circle(100.0f, sf::Vector2f(WIDTH * 3.0f / 4.0f, HEIGHT / 3.0f))
	};

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
		}

		if(circles.size() > 0)
		{
			// Check collisions between all shapes
			for(size_t i = 0; i < circles.size() - 1; i++)
			for(size_t j = i + 1; j < circles.size(); j++)
			{
				Circle& c1 = circles[i];
				Circle& c2 = circles[j];


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