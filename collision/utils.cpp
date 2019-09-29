#include "utils.hpp"
#include <random>

float Dot(const sf::Vector2f& first, const sf::Vector2f& second)
{
	return (first.x * second.x + first.y * second.y);
}

float Length(const sf::Vector2f& vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

float RandomNumber(float min, float max)
{
	std::random_device rd;
	std::default_random_engine generator(rd());
	std::uniform_real_distribution<float> distribution(min, max);

	return distribution(generator);
}

sf::Vector2f ClosestPointOnLine(const sf::Vector2f& startOfLine, const sf::Vector2f& endOfLine, const sf::Vector2f& otherPoint)
{
	// l: y - y1 = k1(x - x1)
	float k1 = (endOfLine.y - startOfLine.x) / (endOfLine.x - startOfLine.x);
	float k2 = -1.0f / k1;

	float x = (-k1 * startOfLine.x + startOfLine.y - otherPoint.y + k2 * otherPoint.x) / (k2 - k1);
	float y = k1 * (x - startOfLine.x) + startOfLine.y;

	return sf::Vector2f(x, y);
}
