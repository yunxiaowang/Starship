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

	void UpdateFrame();//����ͼ��
	void RenderFrame();//��Ⱦͼ��

private:
	
	HWND m_hWnd;
	HINSTANCE m_hInstance;

	WCHAR m_wndName[50];//��������
	UINT m_nWindowWidth;//���ڿ��
	UINT m_nWindowHeight;//���ڸ߶�

	LPDIRECT3DDEVICE9 m_pDevice;

	CCamera m_camera;//���
	float m_fCameraMoveSpeed;//����ƶ��ٶ�

	CSkyBox m_skybox;//��պ�

	CAirplane m_meshPlane;//

	CPerson m_meshPerson;

	//CSnowArea m_snowArea;//ѩ��

	CTerrain m_terrain;//����

	CPlatform m_platform1;

	CPlatform m_platform2;

	//CTree m_tree;//��

	CInput m_input;//��ꡢ��������

	CTimer m_timer;//��ʱ��

	D3DLIGHT9 m_light;

	BOOL WindowInit();//��ʾ���ڳ�ʼ��
	BOOL Direct3DInit();//d3d��ʼ��

	void ProcessInput(float fElapsedTime);//������ꡢ��������
};