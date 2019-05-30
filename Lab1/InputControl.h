#pragma once
#include <windowsx.h>
class InputControl
{
public:
	InputControl();
	~InputControl();
	//Sets
	void	keypressDOWN(UINT key);
	void	keypressUP(UINT key);
	void	MouseMovement(LPARAM Lparam);
	void	MouseLDown(LPARAM Lparam);
	void	setMouseWheel(WPARAM Wparam);
	void	MouseLUp();

	//Gets
	bool	isKeyPress(UINT key);
	int		getMouseX();
	int		getMouseY();
	float	getMouseWheel();
private:
	float	Wheel = 1.0f;
	bool	press[256];
	bool	mouseL = false;
	int		oldX, oldY;
	int		dX, dY;
	int		oldDx, oldDy;
};

