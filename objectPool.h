#pragma once
#include <queue>
template <typename T> class objectPool
{
public:
	virtual T create();

	void checkIn(const T& obj);
private:
	std::queue<T> q;
};

