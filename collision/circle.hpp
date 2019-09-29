#pragma once
#include <SFML/Graphics.hpp>

struct Circle
{
	float radius;
	float mass;
	sf::Vector2f center;
	sf::Vector2f velocity;
	sf::Vector3i color;

	Circle() = default;
	Circle(float r, const sf::Vector2f& c);
};

bool CheckOverlap(Circle& first, Circle& second);