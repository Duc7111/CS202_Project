#pragma once
#include <cassert>
#include <iostream>
#include <SFML/Graphics.hpp>

sf::Vector2f center(const sf::RectangleShape& shape);

class RectangleButton {
private:
	sf::RenderWindow* window;
	sf::RectangleShape shape;
	bool status[2];
	bool containsMouse();
public:
	sf::Text text;
	RectangleButton();
	RectangleButton(sf::RenderWindow* window);
	void setWindow(sf::RenderWindow* window);
	void setPosition(float x, float y);
	void setSize(float width, float height);
	void setFillColor(const sf::Color& color);
	bool mouseHover();
	bool mousePressed();
	void draw();
	void eventListener(sf::Event& event);
};