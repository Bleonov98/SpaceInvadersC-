#pragma once
#include "GameObject.h"
class MyCharGun: public GameObject
{
private:

public:

	MyCharGun(char vBuf[][150], int width, int height, int x, int y) : GameObject(vBuf, width, height, x, y) {
	};

	void MoveMyGun();

	void RunGun();

};

