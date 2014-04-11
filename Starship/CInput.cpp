#include "stdafx.h"
#include "CInput.h"

#include <mmsystem.h>

CInput::CInput()
	: m_pDirectInput(NULL), m_pKeyboard(NULL), m_pMouse(NULL)
{
	memset(m_keyState, 0, sizeof(m_keyState));
	memset(&m_mouseState, 0, sizeof(m_mouseState));
}


CInput::~CInput()
{
	Release();
}

void CInput::Release()
{
	if(m_pKeyboard)
	{
		m_pKeyboard->Unacquire();
		m_pKeyboard->Release();
		m_pKeyboard = NULL;
	}

	if(m_pMouse)
	{
		m_pMouse->Unacquire();
		m_pMouse->Release();
		m_pMouse = NULL;
	}

	FAST_RELEASE(m_pDirectInput);
}

BOOL CInput::Initialize(HWND hWnd, HINSTANCE hInstance)
{
	m_hWnd = hWnd;
	m_hInstance = hInstance;

	//初始化IDirectInput8接口
	if(FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, 
		IID_IDirectInput8, (void**)&m_pDirectInput, NULL)))
		return FALSE;

	//进行键盘设备的初始化
	if(FAILED(m_pDirectInput->CreateDevice( GUID_SysKeyboard, 
		&m_pKeyboard, NULL )))
		return FALSE;

	if(FAILED(m_pKeyboard->SetDataFormat( &c_dfDIKeyboard )))
		return FALSE;

	if(FAILED(m_pKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
		return FALSE;
		
	if(FAILED(m_pKeyboard->Acquire()))
		return FALSE;

	//if(FAILED(m_pKeyboard->Poll()))
	//	return FALSE;

	//进行鼠标设备的初始化
	if(FAILED(m_pDirectInput->CreateDevice( GUID_SysMouse, &m_pMouse, NULL)))
		return FALSE;

	if(FAILED(m_pMouse->SetDataFormat(&c_dfDIMouse)))
		return FALSE;

	if(FAILED(m_pMouse->SetCooperativeLevel(hWnd,DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
		return FALSE;

	if(FAILED(m_pMouse->Acquire()))
		return FALSE;

	//if(FAILED(m_pMouse->Poll()))
	//	return FALSE;

	return TRUE;
}


LONG CInput::GetX()
{
	return m_x;
}

LONG CInput::GetY()
{
	return m_y;
}

LONG CInput::GetXDiff()
{
	return m_mouseState.lX;
}

LONG CInput::GetYDiff()
{
	return m_mouseState.lY;
}



BOOL CInput::CheckKeyPressed(INT iKey)
{
	return m_keyState[iKey] & 0x80;
}

BOOL CInput::CheckButtonPressed(INT iButton)
{
	return m_mouseState.rgbButtons[iButton] & 0x80;
}


void CInput::GetUserInput()
{
	//获取键盘状态
	HRESULT hr = m_pKeyboard->GetDeviceState(sizeof(m_keyState), (LPVOID)&m_keyState); 

	//窗口切换、焦点丢失
	if(FAILED(hr))
	{
		if(hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED)
		{
			m_pKeyboard->Acquire();
			m_pMouse->Acquire();
		}
		return;
	}
	
	//获取鼠标状态
	m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState); 

	POINT ptPos;
	GetCursorPos(&ptPos);
	ScreenToClient(m_hWnd, &ptPos);
	m_x = ptPos.x;
	m_y = ptPos.y;
}
