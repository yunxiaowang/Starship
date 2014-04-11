#include "stdafx.h"
#include "CApplication.h"

#include <mmsystem.h>

CApplication::CApplication()
{
	m_nWindowWidth = 0;
	m_nWindowHeight = 0;

	swprintf_s(m_wndName,L"%s",L"Starship");
}

CApplication::~CApplication()
{
	Release();
}

BOOL CApplication::WindowInit()
{
	// Define the window
	WNDCLASSEX wcex = {0};
	wcex.cbSize         = sizeof( WNDCLASSEX ); 
	wcex.style          = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc    = (WNDPROC)CApplication::WndProc;
	wcex.cbClsExtra     = 0;
	wcex.cbWndExtra     = 0;
	wcex.hInstance      = m_hInstance;
	wcex.hIcon          = LoadIcon(m_hInstance, MAKEINTRESOURCE( IDI_STARSHIP ) );
	wcex.hCursor        = LoadCursor(NULL, IDC_ARROW );
	wcex.hbrBackground  = (HBRUSH)GetStockObject( BLACK_BRUSH );
	wcex.lpszMenuName   = NULL;
	wcex.lpszClassName  = m_wndName;
	wcex.hIconSm        = LoadIcon(m_hInstance, MAKEINTRESOURCE( IDI_SMALL ) );

	// Register the window
	if( !RegisterClassEx(&wcex))				//设计完窗口后，需要对窗口类进行注册，这样才能创建该类型的窗口
		return -1;
	
	m_hWnd = CreateWindow(m_wndName, m_wndName, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, m_nWindowWidth, m_nWindowHeight, NULL, NULL, m_hInstance, NULL);

	if (!m_hWnd)
	{
		return FALSE;
	}

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return TRUE;
}

//initialize d3d
BOOL CApplication::Direct3DInit()
{
	//create d3d
	LPDIRECT3D9 pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(NULL == pD3D)
		return E_FAIL;

	//get hardware information
	D3DCAPS9 d3dCap;
	int vertexProcess = 0;
	
	HRESULT hr = pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dCap);
	if(FAILED(hr))
		return E_FAIL;

	if(d3dCap.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vertexProcess = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vertexProcess = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	//fill in D3DPRESENT_PARAMETERS
	D3DPRESENT_PARAMETERS d3dParam;
	ZeroMemory(&d3dParam, sizeof(d3dParam));

	d3dParam.BackBufferWidth = m_nWindowWidth;
	d3dParam.BackBufferHeight = m_nWindowHeight;
	d3dParam.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dParam.BackBufferCount = 2;
	d3dParam.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dParam.MultiSampleQuality = 0;
	d3dParam.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dParam.hDeviceWindow = m_hWnd;
	d3dParam.Windowed = TRUE;
	d3dParam.EnableAutoDepthStencil = TRUE;
	d3dParam.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dParam.Flags = 0;
	d3dParam.FullScreen_RefreshRateInHz = 0;
	d3dParam.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//create d3dDevice
	hr = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, vertexProcess,
		&d3dParam, &m_pDevice);
	if(FAILED(hr))
		return E_FAIL;

	//get display card info
	D3DADAPTER_IDENTIFIER9 Adapter;
	pD3D->GetAdapterIdentifier(0, 0, &Adapter);
	odPrintfA("display card info: %s",Adapter.Description);

	FAST_RELEASE(pD3D);

	return S_OK;
}

BOOL CApplication::Initialize(HINSTANCE hInstance, WCHAR wndName[], UINT nWidth, UINT nHeight)
{
	m_hInstance = hInstance;

	m_nWindowWidth = nWidth;
	m_nWindowHeight = nHeight;

	WindowInit();
	Direct3DInit();

	CreateDevice(m_pDevice);
	ResetDevice(m_pDevice);

	
	//custom initialization
	return TRUE;
}

void CApplication::Release()
{
	FAST_RELEASE(m_pDevice);
	UnregisterClass(m_wndName, m_hInstance);
}

void CApplication::Run()
{
	MSG msg;

	ZeroMemory(&msg, sizeof(MSG));

	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			UpdateFrame();
			RenderFrame();
		}
	}
}

LRESULT CALLBACK CApplication::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_KEYDOWN:
		{
			switch( wParam )
			{
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;
			}
		}
		break;

	case WM_CLOSE:
		{
			PostQuitMessage(0);
		}
		break;

	case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		break;

	default:
		{
			return DefWindowProc( hWnd, msg, wParam, lParam );
		}
		break;
	}

	return 0;
}

void CApplication::CreateDevice(LPDIRECT3DDEVICE9 pDevice)
{
	//D3DXVECTOR3 vecPos(0.0f, 50.0f, -80.0f);
	//D3DXVECTOR3 vecLook(0.0f, -0.2f, 1.0f);
	//D3DXVECTOR3 vecUp(0.0f, 1.0f, 0.2f);
	//D3DXVECTOR3 vecRight(1.0f, 0.0f, 0.0f);

	//D3DXVECTOR3 vecPos(0.0f, 5.0f, -80.0f);
	//D3DXVECTOR3 vecLook(0.0f, 0.0f, 1.0f);
	//D3DXVECTOR3 vecUp(0.0f, 1.0f, 0.0f);
	//D3DXVECTOR3 vecRight(1.0f, 0.0f, 0.0f);

	//m_camera = CCamera(vecPos,vecLook,vecUp,vecRight);
	//m_fCameraMoveSpeed = 25.0f;

	//m_skybox.Initialize(pDevice, 50000.0, 0.02f, vecPos);
	//WCHAR * pTexFile[] = {
	//	L"media\\cloudy_noon_LF.jpg",
	//	L"media\\cloudy_noon_FR.jpg",
	//	L"media\\cloudy_noon_RT.jpg",
	//	L"media\\cloudy_noon_BK.jpg",
	//	L"media\\cloudy_noon_UP.jpg",
	//	L"media\\cloudy_noon_DN.jpg"
	//};
	//m_skybox.LoadTexture(pTexFile, 6);

	D3DXVECTOR3 platPos1(0.0f, 2.0f, -70.0f);
	D3DXVECTOR3 vecSize(1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 vecSpeed1(0.5f, 0.0f, 0.5f);

	m_platform1.Initialize(pDevice,platPos1,vecSize,D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),vecSpeed1);

	D3DXVECTOR3 platPos2(5.0f, 2.0f, -50.0f);
	D3DXVECTOR3 vecSpeed2(-0.5f, 0.0f, -0.5f);
	m_platform2.Initialize(pDevice,platPos2,vecSize,D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),vecSpeed2);
	
	D3DXVECTOR3 vecPlaneLocal(0.0f, 2.0f, 0.0f);
	m_meshPlane.Initialize(pDevice, L"media\\airplane.x", vecPlaneLocal, dynamic_cast<CWorldTransform *>(&m_platform1));
	//m_meshPlane.setParent(dynamic_cast<CWorldTransform *>(&m_platform1));
	
	//CWorldTransform localTrans;
	//localTrans.SetXRotation(-D3DX_PI / 2);
	//localTrans.SetXScale(0.2f);
	//localTrans.SetYScale(0.2f);
	//localTrans.SetZScale(0.2f);
	D3DXVECTOR3 vecPersonPos(-5.0f, 0.0f, -65.0f);
	m_meshPerson.Initialize(pDevice, L"media\\SnowMan.X",vecPersonPos/*, localTrans.GetTransform()*/);

	D3DXVECTOR3 vecPos(0.0f, 5.0f, -10.0f);
	D3DXVECTOR3 vecLook(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3 vecUp(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 vecRight(1.0f, 0.0f, 0.0f);

	m_camera = CCamera(vecPos,vecLook,vecUp,vecRight);
	m_camera.SetParent(dynamic_cast<CWorldTransform *>(&m_meshPerson));
	m_fCameraMoveSpeed = 25.0f;

	m_skybox.Initialize(pDevice, 50000.0, 0.02f, vecPos);
	WCHAR * pTexFile[] = {
		L"media\\cloudy_noon_LF.jpg",
		L"media\\cloudy_noon_FR.jpg",
		L"media\\cloudy_noon_RT.jpg",
		L"media\\cloudy_noon_BK.jpg",
		L"media\\cloudy_noon_UP.jpg",
		L"media\\cloudy_noon_DN.jpg"
	};
	m_skybox.LoadTexture(pTexFile, 6);

	m_terrain.Initialize(pDevice, "media\\heightMap.raw", "media\\terrain.jpg");
	m_terrain.ScaleTo(50.0f, 0.003f, 50.0f);

	//设置光照
	ZeroMemory(&m_light, sizeof(m_light));  
	m_light.Type          = D3DLIGHT_DIRECTIONAL;  
	m_light.Ambient       = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);  
	m_light.Diffuse       = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  
	m_light.Specular      = D3DXCOLOR(0.17f, 0.17f, 0.17f, 1.0f);  
	m_light.Direction     = D3DXVECTOR3(1.0f, -1.0f, 1.0f);  
	m_pDevice->SetLight(0, &m_light);  
	m_pDevice->LightEnable(0, TRUE); 

	m_timer.Start();
}


void CApplication::ResetDevice(LPDIRECT3DDEVICE9 pDevice)
{
	m_pDevice = pDevice;

	D3DXMATRIX matView = m_camera.getViewMatrix();
	pDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIX projection;
	float aspect = (float)(m_nWindowWidth) / m_nWindowHeight;
	D3DXMatrixPerspectiveFovLH( &projection, D3DX_PI / 3.0f, aspect, 0.1f, 300000.0f );
	pDevice->SetTransform( D3DTS_PROJECTION, &projection );

	m_input.Initialize(m_hWnd, m_hInstance);
}

void CApplication::LostDevice(LPDIRECT3DDEVICE9 pDevice)
{

}

void CApplication::DestroyDevice()
{

}

void CApplication::UpdateFrame()
{
	D3DXMATRIX matView;
	D3DXVECTOR3 matCameraPos;

	m_timer.Tick();

	float fElapsedTime = m_timer.GetElapsedTime();

	ProcessInput(fElapsedTime);

	matView = m_camera.getViewMatrix();
	m_pDevice->SetTransform(D3DTS_VIEW, &matView);
	
	matCameraPos = m_camera.GetPosition();
	m_skybox.TranslateTo(matCameraPos.x, matCameraPos.y, matCameraPos.z);
	m_skybox.Update(fElapsedTime);

	m_platform1.Update(fElapsedTime);
	m_platform2.Update(fElapsedTime);

	m_meshPlane.Update();
}

void CApplication::RenderFrame()
{
	m_pDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB( 100, 200, 255 ), 1.0f, 0 ); 
	m_pDevice->BeginScene();


	m_skybox.Render();

	m_meshPlane.Render();

	m_meshPerson.Render();

	m_terrain.Render();


	m_platform1.Render();
	m_platform2.Render();

	//m_meshPerson.Render();

	//m_snowArea.Render();

	//m_tree.Render();


	m_pDevice->EndScene();
	m_pDevice->Present( 0, 0, 0, 0 );
}

void CApplication::ProcessInput(float fElapsedTime)
{
	m_input.GetUserInput();

	if(m_input.CheckButtonPressed(0)) //left bottom down
	{
		
		LONG Dx = m_input.GetXDiff();
		LONG Dy = m_input.GetYDiff();
		m_meshPerson.Yaw(-Dx * 0.01f);
		m_meshPerson.Pitch(-Dy * 0.001f);
	}
	else
	{
		LONG Dx = m_input.GetXDiff();
		LONG Dy = m_input.GetYDiff();
		m_camera.YawY(Dx * 0.01f);

		//m_camera.Pitch(Dy * 0.001f);
	}

	if(m_input.CheckKeyPressed(DIK_UP)) //up key
	{
		m_camera.GoForward(m_fCameraMoveSpeed * fElapsedTime);
	}

	if(m_input.CheckKeyPressed(DIK_DOWN)) //down key
	{
		m_camera.GoForward(-m_fCameraMoveSpeed * fElapsedTime);
	}

	if(m_input.CheckKeyPressed(DIK_LEFT)) //left key
	{
		m_camera.GoRight(-m_fCameraMoveSpeed * fElapsedTime);
	}

	if(m_input.CheckKeyPressed(DIK_RIGHT)) //right key
	{
		m_camera.GoRight(m_fCameraMoveSpeed * fElapsedTime);
	}

	if(m_input.CheckKeyPressed(DIK_HOME)) //home key
	{
		m_camera.GoUp(m_fCameraMoveSpeed * fElapsedTime);
	}

	if(m_input.CheckKeyPressed(DIK_END)) //end key
	{
		m_camera.GoUp(-m_fCameraMoveSpeed * fElapsedTime);
	}

	if(m_input.CheckKeyPressed(DIK_W)) //W key
	{
		//m_camera.Pitch(-0.5f * fElapsedTime);
		m_meshPerson.GoForward(0.5f * fElapsedTime);
		//m_meshPerson.TranslateBy(0.0f, 0.0f, 0.5f * fElapsedTime);
	}

	if(m_input.CheckKeyPressed(DIK_S)) //S key
	{
		//m_camera.Pitch(0.5f * fElapsedTime);
		m_meshPerson.GoForward(-0.5f * fElapsedTime);
		//m_meshPerson.TranslateBy(0.0f, 0.0f, -0.5f * fElapsedTime);
	}

	if(m_input.CheckKeyPressed(DIK_A)) //A key
	{
		//m_camera.Yaw(-0.5f * fElapsedTime);
		m_meshPerson.GoRight(-0.5f * fElapsedTime);
		//m_meshPerson.TranslateBy(-0.5f * fElapsedTime, 0.0f, 0.0f);
	}

	if(m_input.CheckKeyPressed(DIK_D)) //D key
	{
		//m_camera.Yaw(0.5f * fElapsedTime);
		m_meshPerson.GoRight(0.5f * fElapsedTime);
		//m_meshPerson.TranslateBy(0.5f * fElapsedTime, 0.0f, 0.0f);

	}
}

