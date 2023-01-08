#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>

#include "collider.h"
#include <map>

class CVEHICLE;
class CANIMAL;

class CPEOPLE {
	static sf::FileInputStream fis;
	static int characterIndex;
	int mX, mY; // position in the cell-based location system
	int mPrevY = 0; //y truoc do
	bool mState; // state of living (mState = true if player is alive)
	sf::Texture textures[3];
	sf::Sprite sprite;
	unsigned int mDirection; // current direction of moving (default = 0, up = 1, down = 2, right = 3, left = 4)
	sf::Image img;
	int animation;
	float drawVar;
	static constexpr float velocity = 10.0f;
	std::map<int, int> visitedY; //cai nay dung de tinh diem nguoi choi
	void animate();
	sf::Clock clock;
	static float calcX(int X);
	static float calcY(int Y);
public:
	static void loadFile();
	CPEOPLE();
	void setPeople(int mX, int mY, int mDirection, int animation); //cái này dùng cho phần save load
	void loadTexture(); // load texture file
	static int getCharacterIndex();
	void switchCharacter(int index);
	void draw(sf::RenderWindow& window); // draw current object	sf::Vector2i getPosition(); // Return mY, mX in the form of sf::Vector2i
	sf::Vector2i getPosition() const;
	int getPrevY() const;
	sf::Vector2f getPositionInWorld() const;
	unsigned int getDirection() const;
	unsigned int getState() const;
	unsigned int getAnimation() const;
	// signal: 0 = move executed, 1 = animation is currently playing, 2 = hitting border
	int goUp(); // go up
	int goDown(); // go down
	int goRight(); // go right
	int goLeft(); // go left
	bool isFinish();
	bool isDead();
	sf::Sprite getSprite() { return sprite; }
	sf::Texture getTexture() { return textures[0]; }
	sf::Image getImage() { return img; }

	void setPosition(float x, float y);
	bool reinitializedVehicle = false;

	bool collidedWithEnemy(int& collidedIndex);

	float getRealX(float mX); //cai nay chi dung cho cai camera

	friend bool IsNearby(const CPEOPLE& player, const sf::Sprite& otherSprite, float distance);

	friend std::ifstream& operator>>(std::ifstream& ifs, CPEOPLE& people);
	friend std::ofstream& operator<<(std::ofstream& ofs, const CPEOPLE& people);
};
