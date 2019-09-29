#include "circle.hpp"

Circle::Circle(float r, const sf::Vector2f& c) : radius(r), center(c)
{
	color = sf::Vector3i(rand() % 200 + 56, rand() % 200 + 56, rand() % 200 + 56);
}
