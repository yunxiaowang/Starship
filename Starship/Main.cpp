// Snowman.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
//#include "Snowman.h"
#include "CApplication.h"


int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	CApplication * pApp = new CApplication();

	pApp->Initialize(hInstance, L"Starship", 1280, 960);

	pApp->Run();

	FAST_RELEASE( pApp );

	return 0;
}