#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>

#include "collider.h"
#include <map>

class CVEHICLE;
class CANIMAL;

class CPEOPLE {
	int mX, mY; // position in the cell-based location system
	int mPrevY = 0; //y truoc do
	bool mState; // state of living (mState = true if player is alive)
	sf::Texture texture[4];
	sf::Sprite sprite;
	unsigned int mDirection; // current direction of moving (default = 0, up = 1, down = 2, right = 3, left = 4)
	sf::Image img;
	int animation;
	float drawVar;
	static constexpr float velocity = 5.0f;
	std::map<int, int> visitedY; //cai nay dung de tinh diem nguoi choi
	void animate();
	static float calcX(int X);
	static float calcY(int Y);
public:
	CPEOPLE();
	void loadTexture(); // load texture
	void drawPlayer(sf::RenderWindow& window); // draw current object	sf::Vector2i getPosition(); // Return mY, mX in the form of sf::Vector2i
	sf::Vector2i getPosition() const;
	int getPrevY() const;
	sf::Vector2f getPositionInWorld() const;
	unsigned int getDirection() const;
	// signal: 0 = move executed, 1 = animation is currently playing, 2 = hitting border
	int goUp(); // go up
	int goDown(); // go down
	int goRight(); // go right
	int goLeft(); // go left
	bool isFinish();
	bool isDead();
	sf::Sprite getSprite() { return sprite; }
	sf::Texture getTexture() { return texture[0]; }
	sf::Image getImage() { return img; }


	bool reinitializedVehicle = false;

	bool collidedWithEnemy(int& collidedIndex);

	float getRealX(float mX); //cai nay chi dung cho cai camera

	friend bool IsNearby(const CPEOPLE& player, const sf::Sprite& otherSprite, float distance);
};
