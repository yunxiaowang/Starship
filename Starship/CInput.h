#ifndef CINPUT_H
#define CINPUT_H

#include "stdafx.h"
#include <dinput.h>

class CInput
{
public:
	CInput();
	virtual ~CInput();

	BOOL Initialize(HWND hWnd, HINSTANCE hInstance);
	void Release();

	void GetUserInput();   //用于获取输入信息的函数

	LONG GetX(); //得到当前鼠标X坐标
	LONG GetY();  //得到当前鼠标Y坐标
	LONG GetXDiff(); //得到鼠标X坐标偏移量
	LONG GetYDiff(); //得到鼠标Y坐标偏移量

	BOOL CheckKeyPressed(INT iKey); //判断某个键盘按钮是否按下
	BOOL CheckButtonPressed(INT iButton); //判断鼠标按钮是否按下

private:
	IDirectInput8 * m_pDirectInput;

	IDirectInputDevice8 * m_pKeyboard;
	CHAR m_keyState[256];

	IDirectInputDevice8 * m_pMouse;
	DIMOUSESTATE m_mouseState;

	LONG m_x, m_y;

	HWND m_hWnd;

	HINSTANCE m_hInstance;
};

#endif