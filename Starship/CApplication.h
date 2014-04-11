#include "stdafx.h"
#include "CCamera.h"
#include "CSkyBox.h"
#include "CInput.h"
#include "CMesh.h"
//#include "CSnowArea.h"
#include "CTimer.h"
//#include "CTree.h"
#include "CTerrain.h"
#include "CPlatform.h"
#include "CAirplane.h"
#include "CPerson.h"

class CApplication
{
public:
	CApplication();
	virtual ~CApplication();

	BOOL Initialize(HINSTANCE hInstance, WCHAR wndName[], UINT nWidth, UINT nHeight);
	void Release();

	void CreateDevice(LPDIRECT3DDEVICE9 pDevice);
	void ResetDevice(LPDIRECT3DDEVICE9 pDevice);
	void LostDevice(LPDIRECT3DDEVICE9 pDevice);
	void DestroyDevice();

	void Run();

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	void UpdateFrame();//更新图像
	void RenderFrame();//渲染图像

private:
	
	HWND m_hWnd;
	HINSTANCE m_hInstance;

	WCHAR m_wndName[50];//窗口名字
	UINT m_nWindowWidth;//窗口宽度
	UINT m_nWindowHeight;//窗口高度

	LPDIRECT3DDEVICE9 m_pDevice;

	CCamera m_camera;//相机
	float m_fCameraMoveSpeed;//相机移动速度

	CSkyBox m_skybox;//天空盒

	CAirplane m_meshPlane;//

	CPerson m_meshPerson;

	//CSnowArea m_snowArea;//雪花

	CTerrain m_terrain;//地形

	CPlatform m_platform1;

	CPlatform m_platform2;

	//CTree m_tree;//树

	CInput m_input;//鼠标、键盘输入

	CTimer m_timer;//计时器

	D3DLIGHT9 m_light;

	BOOL WindowInit();//显示窗口初始化
	BOOL Direct3DInit();//d3d初始化

	void ProcessInput(float fElapsedTime);//处理鼠标、键盘输入
};