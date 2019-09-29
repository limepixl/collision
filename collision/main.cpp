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
			if(event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Right)
			{
				sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
				circles.emplace_back(float(rand() % 30 + 30), mousePos, sf::Vector2f(RandomNumber(-5.0f, 5.0f), RandomNumber(-5.0f, 5.0f)));
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

				if(CheckOverlap(c1, c2)) // overlap
				{
					sf::Vector2f delta = c1.center - c2.center;
					delta += sf::Vector2f(1.0f, 1.0f);
					delta /= Length(delta);

					sf::Vector2f midPoint = (c1.center + c2.center) / 2.0f;
					c1.center = midPoint + c1.radius * delta;
					c2.center = midPoint - c2.radius * delta;
				} else if((c1.IsMoving() && !c2.IsMoving()) || (!c1.IsMoving() && c2.IsMoving()))
				{
					Circle* first;
					Circle* second;
					if(c1.IsMoving())
					{
						first = &c1;
						second = &c2;
					} else
					{
						first = &c2;
						second = &c1;
					}

					sf::Vector2f closestPoint = ClosestPointOnLine(first->center, first->center + first->velocity, first->center);
					float closestDist = Length(second->center - first->center);
					if(closestDist <= first->radius + second->radius)	// collision
					{
						float backwardsDist = first->radius + second->radius - closestDist;
						float velLength = Length(first->velocity);
						sf::Vector2f newCenter = sf::Vector2f(closestPoint - backwardsDist * (first->velocity / velLength));

						// Response
						sf::Vector2f direction = newCenter - second->center;
						direction /= Length(direction);

						float p = 2.0f * Dot(first->velocity, direction) / (first->mass + second->mass);
						float newVx = first->velocity.x - p * first->mass * direction.x - p * second->mass * direction.x;
						float newVy = second->velocity.y - p * first->mass * direction.y - p * second->mass * direction.y;

						first->velocity = sf::Vector2f(newVx, newVy);
						first->center = closestPoint;
					}
					
				} else if(c1.IsMoving() && c2.IsMoving())
				{
					Circle* first = &c1;
					Circle* second = &c2;

					bool collision = false;
					std::vector<sf::Vector2f> closestPoints;

					for(int i = 0; i < 2; i++)
					{
						if(i == 1)
						{
							first = &c2;
							second = &c1;
						}

						sf::Vector2f closestPoint = ClosestPointOnLine(first->center, first->center + first->velocity, first->center);
						float closestDist = Length(second->center - first->center);
						if(closestDist <= first->radius + second->radius)	// collision
						{
							float backwardsDist = first->radius + second->radius - closestDist;
							float velLength = Length(first->velocity);
							sf::Vector2f newCenter = sf::Vector2f(closestPoint - backwardsDist * (first->velocity / velLength));

							closestPoints.push_back(newCenter);
							collision = true;
						}
					}

					if(collision)
					{
					// At this point we have both points at which the collision occurs
						sf::Vector2f direction = closestPoints[0] - closestPoints[1];
						direction /= Length(direction);

						float p = 2.0f * (Dot(first->velocity, direction) - Dot(second->velocity, direction)) / (first->mass + second->mass);

						sf::Vector2f tempv1 = first->velocity - p * first->mass * direction;
						sf::Vector2f tempv2 = second->velocity + p * second->mass * direction;

						first->velocity = tempv1;
						second->velocity = tempv2;
					}
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

			// Apply velocity
			c.center += c.velocity;

			// Check for collision with wall
			if(c.center.x - c.radius < 0 || c.center.x + c.radius > WIDTH)
				c.velocity.x *= -1.0f;
			if(c.center.y - c.radius < 0 || c.center.y + c.radius > HEIGHT)
				c.velocity.y *= -1.0f;
		}
		window.display();
	}

	return 0;
}