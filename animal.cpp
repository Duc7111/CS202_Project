#include "animal.h"
#include "game.h"

void CANIMAL::Move(float x, float y)
{
	sf::Vector2f pos = sprite.getPosition();
	sprite.setPosition(pos.x + x, pos.y + y);
	currentPos = { pos.x + x,pos.y + y };
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
sf::Vector2f CANIMAL::getCurrentPos() {
	return currentPos;
}
void CANIMAL::drawInWindow(sf::RenderWindow& window)
{
}

CCAT::CCAT() {
	CANIMAL::isElephant = false;
	CANIMAL::sprite = sf::Sprite(CGAME::catTexture);
	sf::Vector2u size = CGAME::catTexture.getSize();
	sprite.setOrigin(size.x / 2, size.y / 2);
	sprite.scale(sf::Vector2f(0.15f, 0.15f));
}

void CCAT::Tell()
{
	if (isSetSound == false) {
		if (!tellBuffer.loadFromFile(". / sound / sound_bird.wav")) {
			cout << "Wrong location . File does not existed" ;
		}
		tell.setBuffer(tellBuffer);
		tell.setVolume(80.f);
		isSetSound = true;
	}
	tell.play();

	cout << "telling";
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
	CANIMAL::isElephant = true;

	CANIMAL::sprite = sf::Sprite(CGAME::elephantTexture);
	sf::Vector2u size = CGAME::elephantTexture.getSize();
	sprite.setOrigin(size.x / 2, size.y / 2);
	sprite.scale(sf::Vector2f(0.15f, 0.15f));
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
