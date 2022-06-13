////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_

#include"cameraclass.h"
#include <dinput.h>
#include <directxmath.h>
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
using namespace DirectX;
#pragma once

////////////////////////////////////////////////////////////////////////////////
// Class name: InputClass
////////////////////////////////////////////////////////////////////////////////
class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	void Initialize();

	void KeyDown(unsigned int);
	void KeyUp(unsigned int);

	bool IsKeyDown(unsigned int);

private:
	bool m_keys[256];

public:
	void DetectInput(double time, HWND hwnd, CameraClass* camera);

private:
	//IDirectInputDevice8* DIKeyboard;
	//IDirectInputDevice8* DIMouse;

	DIMOUSESTATE mouseLastState;

private:

	float moveLeftRight;
	float moveBackForward;

	float camYaw;
	float camPitch;


public:
	bool InitDirectInput(HINSTANCE hInstance, HWND hwnd);

	LPDIRECTINPUT8 DirectInput;
	IDirectInputDevice8* DIKeyboard;
	IDirectInputDevice8* DIMouse;
};

#endif