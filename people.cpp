#include "people.h"
#include "game.h"
sf::Vector2f CPEOPLE::drawPosition(int mX, int mY) {
	float x = (mX / 19.0f) * 1216;
	float y = ((10.0f - mY) / 11.0f) * 640;
	return sf::Vector2f(x, y);
}

CPEOPLE::CPEOPLE() : mX(15), mY(0), mDirection(0), mState(1) {
	texture[0].loadFromFile("player_back.png");
	texture[1].loadFromFile("player_front.png");
	texture[2].loadFromFile("player_right.png");
	texture[3].loadFromFile("player_left.png");
	img = texture[0].copyToImage();
}

void CPEOPLE::loadTexture() {

	sprite.setTexture(texture[0]);
	sprite.setPosition(drawPosition(mX, mY));
}

void CPEOPLE::drawPlayer(sf::RenderWindow& window) {
	sprite.setPosition(drawPosition(mX, mY));
	window.draw(sprite);
}

sf::Vector2i CPEOPLE::getPosition() const {
	return sf::Vector2i(mX, mY);
}

sf::Vector2f CPEOPLE::getPositionInWorld() const {
	return sprite.getPosition();
}

unsigned int CPEOPLE::getDirection() const {
	return mDirection;
}

void CPEOPLE::goUp() {
	//if (mY == 18) return;
	if (mDirection != 1) {
		mDirection = 1;
		sprite.setTexture(texture[0]);
	}
	mPrevY = mY;
	++mY;

}

void CPEOPLE::goDown() {
	if (mY == 0) return;
	if (mDirection != 2) {
		mDirection = 2;
		sprite.setTexture(texture[1]);
	}
	mPrevY = mY;
	--mY;
}

void CPEOPLE::goRight() {
	if (mX == 18) return;
	if (mDirection != 3) {
		mDirection = 3;
		sprite.setTexture(texture[2]);
	}
	++mX;
}

void CPEOPLE::goLeft() {
	if (mX == 0) return;
	if (mDirection != 4) {
		mDirection = 4;
		sprite.setTexture(texture[3]);
	}
	--mX;
}

bool CPEOPLE::isImpact(const CVEHICLE*&)
{
	return false;
}

bool CPEOPLE::isImpact(const CANIMAL*&)
{
	return false;
}

bool CPEOPLE::isFinish()
{
	return false;
}

bool CPEOPLE::isDead()
{
	return false;
}

int CPEOPLE::getPrevY() const {
	return mPrevY;
}

bool CPEOPLE::collidedWithEnemy() {
	for (int i = 0; i < generatedVehicles.size(); i++) {
		if (PixelPerfectCollision(sprite, generatedVehicles[i]->getSprite(), img, generatedVehicles[i]->getImage())) {
			return true;
		}
	}
	return false;
}