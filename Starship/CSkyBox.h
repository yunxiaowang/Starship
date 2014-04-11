#ifndef CSKYBOX_H
#define CSKYBOX_H

#include "stdafx.h"
#include "CWorldTransform.h"

#define D3DFVF_SKYBOX (D3DFVF_XYZ | D3DFVF_TEX1)

struct SKYBOXVERTEX
{
	float x, y, z;
	float tu, tv;
};

class CSkyBox : public CWorldTransform
{
public:
	CSkyBox();
	virtual ~CSkyBox();

	void Initialize(LPDIRECT3DDEVICE9 pDevice, float fWidth, float fRotSpeed, D3DXVECTOR3 vecPos);
	void LoadTexture(WCHAR * pTexFile[], UINT nTexNumber);

	void Release();

	void Update(float fElapseTime);
	void Render();

private:
	LPDIRECT3DDEVICE9 m_pDevice;
	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer; 
	LPDIRECT3DTEXTURE9 m_pTexture[6];
	float m_fRotateSpeed; //��պ���Y����ת�ٶȣ������γ��Ƶ��ƶ�Ч��
};

#endif