#include "stdafx.h"
#include "CSkyBox.h"
#include <DxErr.h>

CSkyBox::CSkyBox()
{
	m_fRotateSpeed = 0.0f;
}

CSkyBox::~CSkyBox()
{
	Release();
}

void CSkyBox::Initialize(LPDIRECT3DDEVICE9 pDevice, float fWidth, float fRotSpeed, D3DXVECTOR3 vecPos)
{
	m_pDevice = pDevice;
	m_fRotateSpeed = fRotSpeed;

	SetXScale(fWidth);
	SetYScale(fWidth);
	SetZScale(fWidth);
	SetXPosition(vecPos.x);
	SetYPosition(vecPos.y);
	SetZPosition(vecPos.z);

	SKYBOXVERTEX skyboxVertex[] =
	{	
		{0.5f, -0.5f,  0.5f,   0.0f, 1.0f},		//Right
		{0.5f,  0.5f,  0.5f,   0.0f, 0.0f},		
		{0.5f, -0.5f, -0.5f,   1.0f, 1.0f},		
		{0.5f,  0.5f, -0.5f,   1.0f, 0.0f},

		{0.5f, -0.5f, -0.5f,   0.0f, 1.0f},		//Back 
		{0.5f,  0.5f, -0.5f,   0.0f, 0.0f},
		{-0.5f, -0.5f, -0.5f,  1.0f, 1.0f},		
		{-0.5f,  0.5f, -0.5f,  1.0f, 0.0f},

		{-0.5f, -0.5f, -0.5f,  0.0f, 1.0f},		//Left
		{-0.5f,  0.5f, -0.5f,  0.0f, 0.0f},
		{-0.5f, -0.5f,  0.5f,  1.0f, 1.0f},		
		{-0.5f,  0.5f,  0.5f,  1.0f, 0.0f},

		{-0.5f, -0.5f,  0.5f,  0.0f, 1.0f},		//Front
		{-0.5f,  0.5f,  0.5f,  0.0f, 0.0f},
		{0.5f, -0.5f,  0.5f,   1.0f, 1.0f},	
		{0.5f,  0.5f,  0.5f,   1.0f, 0.0f},

		{0.5f,  0.5f,  0.5f,   0.0f, 0.0f},		//up
		{-0.5f,  0.5f,  0.5f,  1.0f, 0.0f},		
		{0.5f,  0.5f, -0.5f,   0.0f, 1.0f},	     
		{-0.5f,  0.5f, -0.5f,  1.0f, 1.0f},

		{-0.5f, -0.5f,  0.5f,  0.0f, 0.0f},		//down
		{0.5f, -0.5f,  0.5f,   0.0f, 1.0f},
		{-0.5f, -0.5f, -0.5f,  1.0f, 0.0f},	
		{0.5f, -0.5f, -0.5f,   1.0f, 1.0f},
	};

	m_pDevice->CreateVertexBuffer(sizeof(skyboxVertex), 0, 
		D3DFVF_SKYBOX, D3DPOOL_MANAGED, &m_pVertexBuffer,NULL);
	
	void * pVertices;
	m_pVertexBuffer->Lock(0, 0, &pVertices, 0);
	memcpy(pVertices,(void *)skyboxVertex,sizeof(skyboxVertex));
	m_pVertexBuffer->Unlock();
}

void CSkyBox::LoadTexture(WCHAR * pTexFile[], UINT nTexNumber)
{
	if(6 != nTexNumber)
	{
		MessageBoxA(0, "SkyBox texture number must be 6!", "Error", 0);
		return;
	}

	for(int i = 0;i < 6;i++)
	{
		if(FAILED(D3DXCreateTextureFromFile( m_pDevice , pTexFile[i], &m_pTexture[i])))
		{
			MessageBox(0, L"D3DXCreateTextureFromFileA skybox FAILED!", L"Error", 0);
			return;
		}
	}
}

void CSkyBox::Release()
{
	FAST_RELEASE(m_pVertexBuffer);

	for(int i = 0;i < 5;i++)
	{
		FAST_RELEASE(m_pTexture[i]);
	}
}

void CSkyBox::Update(float fElapseTime)
{
	RotateBy(0, m_fRotateSpeed * fElapseTime, 0);
}

void CSkyBox::Render()
{
	m_pDevice->SetTexture(0, 0);

	//m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	D3DXMATRIX matWorldTrans = GetTransform();
	m_pDevice->SetTransform( D3DTS_WORLD, &matWorldTrans );

	m_pDevice->SetFVF(D3DFVF_SKYBOX);
	m_pDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(SKYBOXVERTEX));		

	HRESULT hr;
	for(int i = 0;i < 6;i++)
	{
		m_pDevice->SetTexture(0, m_pTexture[i]);
		hr = m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);
	}
}