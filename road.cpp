#include "road.h"
#include "people.h"
#include "game.h"
#include <thread>
#include <chrono>
#include <iostream>
#include "effect.h"

#define WINDOW (*windowHandle)

sf::RenderWindow* Road::windowHandle = nullptr;
sf::Texture Road::texture[];

void scale(CVEHICLE* v, float x, float y)
{
	v->sprite.scale(x, y);
}

void scale(CANIMAL* a, float x, float y)
{
	a->sprite.scale(x, y);
}

Road::Road() : side(DICE::flip()) {}

void Road::setWindow(sf::RenderWindow* window)
{
	windowHandle = window;
}

void Road::setPosition(float y)
{
	index = y;
	sprite.setPosition(sf::Vector2f(0.f, ((6.0f - y) / 7.0f) * 700));

}

void Road::drawRoad()
{
	WINDOW.draw(sprite);
}

/////////////////////////////////////////////////////

CVEHICLE* VehicleRoad::VehicleFactory()
{
	CVEHICLE* vehicle;
	// Type
	if (DICE::flip()) vehicle = new CCAR;
	else vehicle = new CTRUCK;
	//side
	if (side) scale(vehicle, -1.f, 1.f);
	//position
	float x;
	if (vQueue.isEmpty()) x = 10.f;
	else x = abs(vQueue[0]->getTexture().getSize().x * vQueue[0]->getSprite().getScale().x) + 20.f;

	if (side)
		x = DICE::random(WINDOW.getSize().x + x, WINDOW.getSize().x + 5 * x);
	else
		x = DICE::random(-x * 5, -x);

	vehicle->setPosition(x, sprite.getPosition().y + 20);
	return vehicle;
}
bool VehicleRoad::checkCollide(sf::RenderWindow& window, CPEOPLE player) {
	//sẽ tối ưu hơn bằng cách chỉ check những xe nào trong phạm vi của người chơi
	for (int i = 0; i < vQueue.size(); i++) {
		if (IsNearby(player, vQueue[i]->getSprite(), 5))
			if (vQueue[i]->CollidedWithPlayer(player)) {
				sf::Clock clock;
				explosion::animateExplosion(clock, window, vQueue[i]->getSprite().getPosition());
				return true;
			}
	}
	return false;
}

VehicleRoad::VehicleRoad() : v(0) {
	isVehicleRoad = true;
}

VehicleRoad::~VehicleRoad()
{
	for (int i = vQueue.size() - 1; i > -1; --i) delete vQueue[i];
}

bool VehicleRoad::loadTexture()
{
	return texture[0].loadFromFile("road1.png");
}

void VehicleRoad::resetSprite()
{
	sprite.setTexture(texture[0]);
	float scale = (float)M_CELL / (sprite.getTexture()->getSize().y);
	sprite.setScale(sf::Vector2f(scale, scale));
	sprite.setOrigin(sf::Vector2f(0.f, (float)M_CELL / 2));
}

void VehicleRoad::setPosition(float y)
{
	// Road position
	Road::setPosition(y);
	// traficLight position
	if (side) traficLight.shape.setPosition(sf::Vector2f(20.f, Road::sprite.getPosition().y));
	else traficLight.shape.setPosition(sf::Vector2f(WINDOW.getSize().x - 20.f, Road::sprite.getPosition().y));
	// Reset queue
	if (!reload) {
		for (int i = vQueue.size() - 1; i > -1; --i) delete vQueue[i];
		vQueue.reset();
	}
}

void VehicleRoad::setVelocity(float velocity)
{
	if (!side) v = velocity;
	else v = -velocity;
}

//void VehicleRoad::save(ofstream& fout)
//{
//	//traficlight, velocity
//	fout.write((char*)&traficLight, sizeof(TF));
//	fout.write((char*)&v, sizeof(float));
//	//Cars
//	int n = vQueue.size();
//	fout.write((char*)&n, sizeof(int));
//	for (int i = 0; i < n; ++i)
//	{
//		bool type = typeid(*vQueue[i]) == typeid(CCAR);
//		fout.write((char*)&type, sizeof(bool));
//		if (type) fout.write((char*)vQueue[i], sizeof(CCAR));
//		else fout.write((char*)vQueue[i], sizeof(CTRUCK));
//	}
//}
//
//void VehicleRoad::load(ifstream& fin)
//{
//	//traficlight, velocity
//	fin.read((char*)&traficLight, sizeof(TF));
//	fin.read((char*)&v, sizeof(float));
//	//Cars
//	int n;
//	fin.read((char*)&n, sizeof(int));
//	for (int i = 0; i < n; ++i)
//	{
//		bool type;
//		CVEHICLE* temp;
//		fin.read((char*)&type, sizeof(bool));
//		if (type)
//		{
//			temp = new CCAR;
//			fin.read((char*)temp, sizeof(CCAR));
//		}
//		else
//		{
//			temp = new CTRUCK;
//			fin.read((char*)temp, sizeof(CTRUCK));
//		}
//		vQueue.push(temp);
//	}
//}

void VehicleRoad::run()
{
	// Trafic light
	if (!reload)
		traficLight.function();
	else {
		traficLight.shape.setFillColor(sf::Color::Red);
	}
	if (!reload && !traficLight.status) return;
	if (reload)
		reload = false;
	// New vehicle
	if (vQueue.size() == 0 || (vQueue.size() < OBJ_MAX && vQueue[0]->getSprite().getPosition().x > 0 && vQueue[0]->getSprite().getPosition().x < WINDOW.getSize().x + 20.f))
		vQueue.push(VehicleFactory());
	// Vehicles
	if ((side && vQueue[vQueue.size() - 1]->getSprite().getPosition().x < -50.f)
		|| (!side && vQueue[vQueue.size() - 1]->getSprite().getPosition().x > WINDOW.getSize().x + 50.f))
		delete vQueue.pop();

	for (int i = vQueue.size() - 1; i > -1; --i)
		vQueue[i]->Move(v, 0);
}

void VehicleRoad::drawObj()
{
	for (int i = 0; i < vQueue.size(); ++i)
		vQueue[i]->drawInWindow(WINDOW);
	WINDOW.draw(traficLight.shape);
}

////////////////////////////////////////////////////////

bool AnimalRoad::checkCollide(sf::RenderWindow& window, CPEOPLE player) {
	for (int i = 0; i < aQueue.size(); i++) {
		if (IsNearby(player, aQueue[i]->getSprite(), 5))
			if (aQueue[i]->CollidedWithPlayer(player)) {
				sf::Clock clock;
				explosion::animateExplosion(clock, window, aQueue[i]->getSprite().getPosition());
				return true;
			}
	}
	return false;
}

CANIMAL* AnimalRoad::AnimalFactory()
{
	CANIMAL* animal;
	// Type
	if (DICE::flip()) animal = new CCAT;
	else animal = new CELEPHANT;
	//side
	if (side) scale(animal, -1.f, 1.f);
	//position
	float x;
	if (aQueue.isEmpty()) x = 10.f;
	else x = abs(aQueue[0]->getTexture().getSize().x * aQueue[0]->getSprite().getScale().x) + 20.f;

	if (side)
		x = DICE::random(WINDOW.getSize().x + x, WINDOW.getSize().x + 5 * x);
	else
		x = DICE::random(-x * 5, -x);

	animal->setPosition(x, sprite.getPosition().y + 20);
	return animal;
}

AnimalRoad::AnimalRoad() : v(0) {
	isVehicleRoad = false;
}

AnimalRoad::~AnimalRoad()
{
	while (!aQueue.isEmpty()) delete aQueue.pop();
}

bool AnimalRoad::loadTexture()
{
	return texture[1].loadFromFile("road2.png");
}

void AnimalRoad::resetSprite()
{
	sprite.setTexture(texture[1]);
	float scale = (float)M_CELL / (sprite.getTexture()->getSize().y);
	sprite.setScale(sf::Vector2f(scale, scale));
	sprite.setOrigin(sf::Vector2f(0.f, (float)M_CELL / 2));
}

void AnimalRoad::setPosition(float y)
{
	// Road position
	Road::setPosition(y);
	// Reset queue
	if (!reload) {
		for (int i = aQueue.size() - 1; i > -1; --i) delete aQueue[i];
		aQueue.reset();
	}
}

void AnimalRoad::setVelocity(float velocity)
{
	if (!side) v = velocity;
	else v = -velocity;
}

//void AnimalRoad::save(ofstream& fout)
//{
//	fout.write((char*)&v, sizeof(float));
//	//Cars
//	int n = aQueue.size();
//	fout.write((char*)&n, sizeof(int));
//	for (int i = 0; i < n; ++i)
//	{
//		bool type = typeid(*aQueue[i]) == typeid(CCAT);
//		fout.write((char*)&type, sizeof(bool));
//		if (type) fout.write((char*)aQueue[i], sizeof(CCAT));
//		else fout.write((char*)aQueue[i], sizeof(CELEPHANT));
//	}
//}
//
//void AnimalRoad::load(ifstream& fin)
//{
//	fin.read((char*)&v, sizeof(float));
//	//Cars
//	int n;
//	fin.read((char*)&n, sizeof(int));
//	for (int i = 0; i < n; ++i)
//	{
//		bool type;
//		CANIMAL* temp;
//		fin.read((char*)&type, sizeof(bool));
//		if (type)
//		{
//			temp = new CCAT;
//			fin.read((char*)temp, sizeof(CCAT));
//		}
//		else
//		{
//			temp = new CELEPHANT;
//			fin.read((char*)temp, sizeof(CELEPHANT));
//		}
//		aQueue.push(temp);
//	}
//}

void AnimalRoad::run()
{
	// New animal
	if (aQueue.size() == 0 || (aQueue.size() < OBJ_MAX && aQueue[0]->getSprite().getPosition().x > 0 && aQueue[0]->getSprite().getPosition().x < WINDOW.getSize().x + 20.f))
		aQueue.push(AnimalFactory());
	// Animals
	if ((side && aQueue[aQueue.size() - 1]->getSprite().getPosition().x < -50.f)
		|| (!side && aQueue[aQueue.size() - 1]->getSprite().getPosition().x > WINDOW.getSize().x + 50.f))
		delete aQueue.pop();

	for (int i = aQueue.size() - 1; i > -1; --i)
		aQueue[i]->Move(v, 0);
}

void AnimalRoad::drawObj()
{
	for (int i = aQueue.size() - 1; i > -1; --i)
		aQueue[i]->drawInWindow(WINDOW);
}

//////////////////////////////
sf::Texture TREE::texture[4];
sf::Sprite TREE::getSprite() {
	return this->sprite;
}
void TREE::loadTexture() {
	texture[0].loadFromFile("tree/1.png");
	texture[1].loadFromFile("tree/2.png");
	texture[2].loadFromFile("tree/3.png");
	texture[3].loadFromFile("tree/4.png");
}

void TREE::drawInWindow(sf::RenderWindow& window) {
	window.draw(sprite);
}
TREE::TREE() {
	srand(time(0));
	int r = rand() % 4;
	sprite = sf::Sprite(texture[r]);
}


void VehicleRoad::input(std::ifstream& ifs) {
	this->traficLight.status = false;

	int size;
	ifs.read((char*)&size, sizeof(int));

	for (int i = size - 1; i > -1; --i)
	{
		bool isCar;
		ifs.read((char*)&isCar, sizeof(bool));

		float x, y;
		ifs.read((char*)&x, sizeof(float));
		ifs.read((char*)&y, sizeof(float));

		CVEHICLE* temp;
		if (isCar)
			temp = new CCAR;
		else
			temp = new CTRUCK;
		temp->isCar = isCar;

		temp->getSprite().setPosition({ x, y });

		vQueue[i] = temp;

		vQueue.sizeInc();
	}

	bool side;
	ifs.read((char*)&side, sizeof(bool));
	this->side = side;

	this->reload = true;
}

void AnimalRoad::input(std::ifstream& ifs) {
	int size;
	ifs.read((char*)&size, sizeof(int));

	for (int i = size - 1; i > -1; --i)
	{
		bool isElephant;
		ifs.read((char*)&isElephant, sizeof(bool));

		float x, y;
		ifs.read((char*)&x, sizeof(float));
		ifs.read((char*)&y, sizeof(float));

		CANIMAL* temp;
		if (isElephant)
			temp = new CELEPHANT;
		else
			temp = new CCAT;
		temp->isElephant = isElephant;

		temp->getSprite().setPosition({ x, y });

		aQueue[i] = temp;
		aQueue.sizeInc();
	}

	bool side;
	ifs.read((char*)&side, sizeof(bool));
	this->side = side;

	this->reload = true;
}

void VehicleRoad::output(std::ofstream& ofs) {


	int size = vQueue.size();
	ofs.write((char*)&size, sizeof(size));

	for (int i = vQueue.size() - 1; i > -1; --i)
	{
		ofs.write((char*)&vQueue[i]->isCar, sizeof(vQueue[i]->isCar));

		float x, y;
		x = vQueue[i]->getCurrentPos().x;
		y = vQueue[i]->getCurrentPos().y;
		ofs.write((char*)&x, sizeof(x));
		ofs.write((char*)&y, sizeof(y));
	}

	ofs.write((char*)&side, sizeof(side));
}

void AnimalRoad::output(std::ofstream& ofs) {
	int size = aQueue.size();
	ofs.write((char*)&size, sizeof(size));

	for (int i = aQueue.size() - 1; i > -1; --i)
	{

		ofs.write((char*)&aQueue[i]->isElephant, sizeof(aQueue[i]->isElephant));

		float x, y;
		x = aQueue[i]->getCurrentPos().x;
		y = aQueue[i]->getCurrentPos().y;
		ofs.write((char*)&x, sizeof(x));
		ofs.write((char*)&y, sizeof(y));
	}

	ofs.write((char*)&side, sizeof(side));
}