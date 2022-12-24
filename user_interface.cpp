#include "user_interface.h"

bool RectangleButton::containsMouse() {
	return shape.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*window));
}

RectangleButton::RectangleButton() : window(nullptr) {
	memset(status, false, 2);
}

RectangleButton::RectangleButton(sf::RenderWindow* window) {
	memset(status, false, 2);
	this->window = window;
}

void RectangleButton::setWindow(sf::RenderWindow* window) {
	this->window = window;
}

void RectangleButton::setPosition(float x, float y) {
	auto bounds = shape.getGlobalBounds();
	assert((bounds.height != 0) && (bounds.width != 0));
	assert(text.getCharacterSize() != 0);
	shape.setPosition(x, y);
	text.setPosition(x, y);
	text.setOrigin(-(float)text.getCharacterSize() / 2.f, -bounds.height * 0.15);
}

void RectangleButton::setSize(float width, float height) {
	shape.setSize(sf::Vector2f(width, height));
}

void RectangleButton::setFillColor(const sf::Color& color) {
	shape.setFillColor(color);
}

bool RectangleButton::mouseHover() {
	return status[0];
}

bool RectangleButton::mousePressed() {
	bool tmp = status[1];
	status[1] = false;
	return tmp;
}

void RectangleButton::draw() {
	window->draw(shape);
	window->draw(text);
}

void RectangleButton::eventListener(sf::Event& event) {
	if (event.type == sf::Event::MouseMoved) {
		status[0] = containsMouse();
	}
	if (event.type == sf::Event::MouseButtonPressed) {
		status[1] = containsMouse();
	}
}

sf::Vector2f center(const sf::RectangleShape& shape) {
	sf::FloatRect rect = shape.getGlobalBounds();
	return sf::Vector2f(rect.top + rect.width / 2, rect.left + rect.height / 2);
}
