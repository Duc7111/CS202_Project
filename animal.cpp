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
	return this->sprite;
}

void CANIMAL::setPosition(float x, float y)
{
	this->sprite.setPosition({ x,y });
}

void CANIMAL::drawInWindow(sf::RenderWindow& window)
{
}

CCAT::CCAT() {
	CANIMAL::sprite = sf::Sprite(CGAME::catTexture);
	sf::Vector2u size = CGAME::catTexture.getSize();
	sprite.setOrigin(size.x / 2, size.y / 2);
	sprite.scale(sf::Vector2f(0.25f, 0.25f));
}

void CCAT::Tell()
{
}

void CCAT::setSpeed(float speed) {
	this->speed = speed;
}
sf::Vector2f CCAT::getPosition() {
	sf::Vector2f position(this->mX, this->mY);
	return position;
}
sf::Texture CCAT::getTexture()
{
	return CGAME::catTexture;
}

sf::Sprite CCAT::getSprite()
{
	return this->sprite;
}

void CCAT::drawInWindow(sf::RenderWindow& window)
{
	window.draw(sprite);
}
bool CCAT::CollidedWithPlayer(CPEOPLE player) {
	return PixelPerfectCollision(sprite, player.getSprite(), CGAME::catImage, player.getImage());
}


/// /////////////////

CELEPHANT::CELEPHANT() {
	CANIMAL::sprite = sf::Sprite(CGAME::elephantTexture);
	sf::Vector2u size = CGAME::elephantTexture.getSize();
	sprite.setOrigin(size.x / 2, size.y / 2);
	sprite.scale(sf::Vector2f(0.25f, 0.25f));
}

void CELEPHANT::Tell()
{
}

void CELEPHANT::setSpeed(float speed) {
	this->speed = speed;
}
sf::Vector2f CELEPHANT::getPosition() {
	sf::Vector2f position(mX, mY);
	return position;
}
sf::Texture CELEPHANT::getTexture()
{
	return CGAME::elephantTexture;
}

sf::Sprite CELEPHANT::getSprite()
{
	return this->sprite;
}

void CELEPHANT::drawInWindow(sf::RenderWindow& window)
{
	window.draw(sprite);
}
bool CELEPHANT::CollidedWithPlayer(CPEOPLE player) {
	return PixelPerfectCollision(sprite, player.getSprite(), CGAME::elephantImage, player.getImage());
}
