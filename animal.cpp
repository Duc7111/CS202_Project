#include "animal.h"
#include "game.h"

void CANIMAL::Move(float x, float y)
{
	this->sprite.move(x, y);
}

void CANIMAL::Tell()
{
}

sf::Sprite CANIMAL::getSprite()
{
	return sf::Sprite();
}
sf::Texture CANIMAL::getTexture()
{
	return sf::Texture();
}

void CANIMAL::setPosition(float x, float y)
{
	this->mX = x;
	this->mY = y;
}

void CANIMAL::drawInWindow(sf::RenderWindow& window)
{
}

CBIRD::CBIRD() {
	CANIMAL::sprite = sf::Sprite(CGAME::catTexture);
	sf::Vector2u size = CGAME::catTexture.getSize();
	sprite.setOrigin(size.x / 2, size.y / 2);
	sprite.scale(sf::Vector2f(0.25f, 0.25f));
}

void CBIRD::Tell()
{
}

void CBIRD::setSpeed(float speed) {
	this->speed = speed;
}
sf::Vector2f CBIRD::getPosition() {
	sf::Vector2f position(this->mX, this->mY);
	return position;
}
sf::Texture CBIRD::getTexture()
{
	return sf::Texture();
}

sf::Sprite CBIRD::getSprite()
{
	return sf::Sprite();
}

void CBIRD::drawInWindow(sf::RenderWindow& window)
{
	window.draw(sprite);
}



/// /////////////////

CDINAUSOR::CDINAUSOR() {
	CANIMAL::sprite = sf::Sprite(CGAME::elephantTexture);
	sf::Vector2u size = CGAME::elephantTexture.getSize();
	sprite.setOrigin(size.x / 2, size.y / 2);
	sprite.scale(sf::Vector2f(0.25f, 0.25f));
}

void CDINAUSOR::Tell()
{
}

void CDINAUSOR::setSpeed(float speed) {
	this->speed = speed;
}
sf::Vector2f CDINAUSOR::getPosition() {
	sf::Vector2f position(mX, mY);
	return position;
}
sf::Texture CDINAUSOR::getTexture()
{
	return sf::Texture();
}

sf::Sprite CDINAUSOR::getSprite()
{
	return sf::Sprite();
}

void CDINAUSOR::drawInWindow(sf::RenderWindow& window)
{
	window.draw(sprite);
}
