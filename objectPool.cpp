#include "objectPool.h"
template <typename T>
T objectPool<T>::create() {
	T finalT = q.front();
	q.pop();
	return finalT; //lay T dau tien
}

template <typename T>
void objectPool<T>::checkIn(const T& obj) {
	q.push(obj); //day lai vao queue
}