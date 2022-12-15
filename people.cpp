#include "people.h"
#include "game.h"

float CPEOPLE::getRealX(float mX) //cai nay chi dung cho cai camera
{
	return (mX / 13.0f) * 1300;
}

CPEOPLE::CPEOPLE() : mX(6), mY(0), mDirection(0), mState(1), animation(false) {
	texture[0].loadFromFile("player_back.png");
	texture[1].loadFromFile("player_front.png");
	texture[2].loadFromFile("player_right.png");
	texture[3].loadFromFile("player_left.png");
	img = texture[0].copyToImage();
	drawX = (mX / 13.0f) * 1300 + 10;
	drawY = ((6.0f - mY) / 7.0f) * 700 + 10;
	drawVar = 0;
}

void CPEOPLE::loadTexture() {

	sprite.setTexture(texture[0]);
	sprite.setPosition(drawX, drawY);
}

void CPEOPLE::drawPlayer(sf::RenderWindow& window) {
	animate();
	sprite.setPosition(drawX, drawY);
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

int CPEOPLE::goUp() {
	//if (mY == 18) return;
	if (animation) return 1;
	if (mDirection != 1) {
		mDirection = 1;
		sprite.setTexture(texture[0]);
	}
	mPrevY = mY;
	++mY;
	if (!visitedY[mY])
		CGAME::score++;
	visitedY[mY] = true;
	drawVar = ((6.0f - mY) / 7.0f) * 700 + 10;
	animation = true;
	return 0;
}

int CPEOPLE::goDown() {
	if (animation) return 1;
	if (mY == 0) return 2;
	if (mDirection != 2) {
		mDirection = 2;
		sprite.setTexture(texture[1]);
	}
	mPrevY = mY;
	--mY;
	drawVar = ((6.0f - mY) / 7.0f) * 700 + 10;
	animation = true;
	return 0;
}

int CPEOPLE::goRight() {
	if (animation) return 1;
	if (mX == 12) return 2;
	if (mDirection != 3) {
		mDirection = 3;
		sprite.setTexture(texture[2]);
	}
	++mX;
	drawVar = (mX / 13.0f) * 1300 + 10;
	animation = true;
	return 0;
}

int CPEOPLE::goLeft() {
	if (animation) return 1;
	if (mX == 0) return 2;
	if (mDirection != 4) {
		mDirection = 4;
		sprite.setTexture(texture[3]);
	}
	--mX;
	drawVar = (mX / 13.0f) * 1300 + 10;
	animation = true;
	return 0;
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

void CPEOPLE::animate() {
	if (animation) {
		// nested if, same execution time for all cases (branch prediction)
		if (mDirection % 2 == 1) {
			if (mDirection == 1) {
				if (drawY > drawVar) drawY -= velocity;
				else animation = false;
			}
			else {
				if (drawX < drawVar) drawX += velocity;
				else animation = false;
			}
		}
		else {
			if (mDirection == 2) {
				if (drawY < drawVar) drawY += velocity;
				else animation = false;
			}
			else {
				if (drawX > drawVar) drawX -= velocity;
				else animation = false;
			}
		}
	}
}

bool CPEOPLE::collidedWithEnemy(int& collidedIndex) {
	for (int i = 0; i < generatedVehicles.size(); i++) {
		if (PixelPerfectCollision(sprite, generatedVehicles[i]->getSprite(), img, generatedVehicles[i]->getImage())) {
			collidedIndex = i;
			return true;
		}
	}
	return false;
}
bool IsNearby(const CPEOPLE& player, const sf::Sprite& otherSprite, float distance) {
	sf::Vector2f playerBound = sf::Vector2f(player.sprite.getLocalBounds().left, player.sprite.getLocalBounds().top);
	sf::Vector2f otherBound = sf::Vector2f(otherSprite.getLocalBounds().left, otherSprite.getLocalBounds().top);

	if (abs(playerBound.x - otherBound.x) <= distance && abs(playerBound.y - otherBound.y) <= distance)
		return true;
	return false;
}