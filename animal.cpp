#include "animal.h"

void CANIMAL::Move(float x ,float y)
{
	sprite.move(x,y) ;
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
        this -> mX = x ;
	this-> mY = y ;
}

void CANIMAL::drawInWindow(sf::RenderWindow& window)
{
}

void CBIRD::Tell()
{
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
}

void CDINAUSOR::Tell()
{
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
}
