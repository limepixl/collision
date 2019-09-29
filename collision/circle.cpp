#include "circle.hpp"
#include "utils.hpp"

Circle::Circle(float r, const sf::Vector2f& c, const sf::Vector2f& v) : radius(r), mass(r), center(c), velocity(v)
{
	color = sf::Vector3i(rand() % 200 + 56, rand() % 200 + 56, rand() % 200 + 56);
}

bool Circle::IsMoving()
{
	return velocity != sf::Vector2f(0.0f, 0.0f);
}

bool CheckOverlap(Circle& first, Circle& second)
{
	if(first.IsMoving() || second.IsMoving())
		return false;

	float dist = Length(first.center - second.center);
	if(dist < first.radius + second.radius - 1.0f)
		return true;

	return false;
}
