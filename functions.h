#pragma once

#include <Windows.h>
#include <cmath>
//#include <iostream>
//#include <math.h>
#include "parameters.h"

class Graphic2D {
public:
	virtual void DrawLine(Vector2 A, Vector2 B) {}
	virtual void DrawRect(Vector2 A, Vector2 B) {}
};

class SetUpPixels{
public:
	virtual void SetPixels(int x, int y) {}
};
