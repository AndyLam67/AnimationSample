#include "stdafx.h"
#include "InputControl.h"


InputControl::InputControl()
{
}


InputControl::~InputControl()
{
}

void InputControl::keypressDOWN(UINT key)
{
	press[key] = true;
}

void InputControl::keypressUP(UINT key)
{
	press[key] = false;
}

bool InputControl::isKeyPress(UINT key)
{
	return press[key];
}

int InputControl::getMouseX()
{
	return dX;
}

int InputControl::getMouseY()
{
	return dY;
}

float InputControl::getMouseWheel()
{
	return Wheel;
}

void InputControl::MouseMovement(LPARAM Lparam)
{
	if (mouseL == true)
	{
		int mX = GET_X_LPARAM(Lparam);
		int mY = GET_Y_LPARAM(Lparam);
		if (mX != dX)
		{
			dX = oldX - mX+oldDx;
		}
		if (mY != dY)
		{
			dY = oldY - mY+oldDy;
		}
	}
}

void InputControl::MouseLDown(LPARAM Lparam)
{
	mouseL = true;
	oldX = GET_X_LPARAM(Lparam);
	oldY = GET_Y_LPARAM(Lparam);	
}

void InputControl::setMouseWheel(WPARAM Wparam)
{
	float get = GET_WHEEL_DELTA_WPARAM(Wparam);
	Wheel = Wheel + get / 1200.0f;
	if (Wheel < 0.1f)
		Wheel = 0.1f;
	if (Wheel > 2.0f)
		Wheel = 2.0f;
}

void InputControl::MouseLUp()
{
	mouseL = false;
	oldDx = dX;
	oldDy = dY;
}
