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

	void GetUserInput();   //���ڻ�ȡ������Ϣ�ĺ���

	LONG GetX(); //�õ���ǰ���X����
	LONG GetY();  //�õ���ǰ���Y����
	LONG GetXDiff(); //�õ����X����ƫ����
	LONG GetYDiff(); //�õ����Y����ƫ����

	BOOL CheckKeyPressed(INT iKey); //�ж�ĳ�����̰�ť�Ƿ���
	BOOL CheckButtonPressed(INT iButton); //�ж���갴ť�Ƿ���

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