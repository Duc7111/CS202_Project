#include "people.h"
#include "game.h"

float CPEOPLE::getRealX(float mX) //cai nay chi dung cho cai camera
{
	return (mX / 13.0f) * 1300;
}
void CPEOPLE::setPeople(int mX, int mY, int mDirection, int animation) {
	this->mX = mX;
	this->mY = mY;
	this->mDirection = mDirection;
	this->mState = mState;
	this->animation = animation;
	loadTexture();
}
CPEOPLE::CPEOPLE() : mX(6), mY(0), mDirection(0), mState(1), animation(false) {
	texture[0].loadFromFile("player_back.png");
	texture[1].loadFromFile("player_front.png");
	texture[2].loadFromFile("player_right.png");
	texture[3].loadFromFile("player_left.png");
	img = texture[0].copyToImage();
	drawVar = 0;
}

void CPEOPLE::loadTexture() {
	int index;
	if (mDirection == 0)
		index = 0;
	else
		index = mDirection - 1;
	sprite.setTexture(texture[index]);
	sprite.setPosition(calcX(mX), calcY(mY));
}

void CPEOPLE::draw(sf::RenderWindow& window, sf::Clock& clock) {
	if (clock.getElapsedTime().asMicroseconds() >= 8333) { // 120 fps
		animate();
		clock.restart();
	}
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
unsigned int CPEOPLE::getState() const {
	return mState;
}
unsigned int CPEOPLE::getAnimation() const {
	return animation;
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
	drawVar = calcY(mY);
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
	drawVar = calcY(mY);
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
	drawVar = calcX(mX);
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
	drawVar = calcX(mX);
	animation = true;
	return 0;
}

float CPEOPLE::calcX(int X) {
	return (X / 13.0f) * 1300 + 10;
}

float CPEOPLE::calcY(int Y) {
	return ((6.0f - Y) / 7.0f) * 700 + 10;
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
		sf::Vector2f position = sprite.getPosition();
		// nested if, same execution time for all cases (branch prediction)
		if (mDirection % 2 == 1) {
			if (mDirection == 1) {
				if (position.y > drawVar) sprite.move(0, -velocity);
				else animation = false;
			}
			else {
				if (position.x < drawVar) sprite.move(velocity, 0);
				else animation = false;
			}
		}
		else {
			if (mDirection == 2) {
				if (position.y < drawVar) sprite.move(0, velocity);
				else animation = false;
			}
			else {
				if (position.x > drawVar) sprite.move(-velocity, 0);
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
std::ifstream& operator>>(std::ifstream& ifs, CPEOPLE& people) {
	ifs.read((char*)&people.mX, sizeof(int));
	ifs.read((char*)&people.mY, sizeof(int));
	ifs.read((char*)&people.mDirection, sizeof(int));
	ifs.read((char*)&people.animation, sizeof(int));
	ifs.read((char*)&people.mPrevY, sizeof(int));
	int size;
	ifs.read((char*)&size, sizeof(int));
	for (int i = 0; i < size; i++) {
		int a, b;
		ifs.read((char*)&a, sizeof(int));
		ifs.read((char*)&b, sizeof(int));
		people.visitedY[a] = b;
	}
	people.loadTexture();

	return ifs;
}
std::ofstream& operator<<(std::ofstream& ofs, const CPEOPLE& people) {
	ofs.write((char*)&people.mX, sizeof(int));
	ofs.write((char*)&people.mY, sizeof(int));
	ofs.write((char*)&people.mDirection, sizeof(int));
	ofs.write((char*)&people.animation, sizeof(int));
	ofs.write((char*)&people.mPrevY, sizeof(int));
	int size = people.visitedY.size();
	ofs.write((char*)&size, sizeof(int));
	std::map<int, int> m = people.visitedY;
	for (std::map<int, int>::iterator it = m.begin(); it != m.end(); ++it) {
		ofs.write((char*)&it->first, sizeof(it->first));
		ofs.write((char*)&it->second, sizeof(it->second));
	}
	return ofs;
}