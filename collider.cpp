#include "collider.h"
Collider::Collider(sf::RectangleShape& obj) : obj(obj) {
	this->obj = obj;
}

sf::Vector2f Collider::getObjPos() {
	return obj.getPosition();
}
sf::Vector2f Collider::getObjSize() {
	return obj.getSize();
}

bool Collider::isCollided(Collider& other) {
	sf::Vector2f otherPos = other.getObjPos();
	sf::Vector2f otherSize = other.getObjSize();

	sf::Vector2f thisPos = getObjPos();
	sf::Vector2f thisSize = getObjSize();

	float deltaX = otherPos.x - thisPos.x;
	float deltaY = otherPos.y - thisPos.y;

	float xx = abs(deltaX) - (otherSize.x / 2 + thisSize.x / 2);
	float yy = abs(deltaY) - (otherSize.y / 2 + thisSize.y / 2);

	if (xx < 0 && yy < 0) return true;
	return false;
}