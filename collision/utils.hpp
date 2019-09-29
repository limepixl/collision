#pragma once
#include <SFML/Graphics.hpp>

inline float Dot(const sf::Vector2f& first, const sf::Vector2f& second)
{
	return (first.x * second.x + first.y * second.y);
}