#pragma once
#include <SFML/Graphics.hpp>

float Dot(const sf::Vector2f& first, const sf::Vector2f& second);
float Length(const sf::Vector2f& vec);
sf::Vector2f ClosestPointOnLine(sf::Vector2f& startOfLine, sf::Vector2f& endOfLine, sf::Vector2f& otherPoint);