#pragma once
#include <SFML/Graphics.hpp>

float Dot(const sf::Vector2f& first, const sf::Vector2f& second);
float Length(const sf::Vector2f& vec);
float RandomNumber(float min, float max);
sf::Vector2f ClosestPointOnLine(const sf::Vector2f& startOfLine, const sf::Vector2f& endOfLine, const sf::Vector2f& otherPoint);