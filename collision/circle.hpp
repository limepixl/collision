#pragma once
#include <SFML/Graphics.hpp>

struct Circle
{
	float radius;
	sf::Vector2f center;
	sf::Vector3i color;

	Circle() = default;
	Circle(float r, const sf::Vector2f& c);
};