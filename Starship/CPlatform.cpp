#include "stdafx.h"
#include "CPlatform.h"

CPlatform::CPlatform()
{

}

CPlatform::~CPlatform()
{

}

void CPlatform::Initialize(LPDIRECT3DDEVICE9 pDevice, const D3DXVECTOR3 & vecPos, const D3DXVECTOR3 & vecSize, 
				const D3DXCOLOR & colorPlat, const D3DXVECTOR3 & vecSpeed)
{
	ZeroMemory(&m_material, sizeof(D3DMATERIAL9));
	m_material.Diffuse.r = 0.8f;
	m_material.Diffuse.g = 0.8f;
	m_material.Diffuse.b = 0.8f;
	m_material.Diffuse.a = 1.0f;

	// Set the RGBA for ambient reflection.
	m_material.Ambient.r = 0.8f;
	m_material.Ambient.g = 0.8f;
	m_material.Ambient.b = 0.8f;
	m_material.Ambient.a = 1.0f;

	// Set the color and sharpness of specular highlights.
	m_material.Specular.r = 1.0f;
	m_material.Specular.g = 1.0f;
	m_material.Specular.b = 1.0f;
	m_material.Specular.a = 1.0f;
	m_material.Power = 50.0f;

	// Set the RGBA for emissive color.
	m_material.Emissive.r = 0.1f;
	m_material.Emissive.g = 0.0f;
	m_material.Emissive.b = 0.0f;
	m_material.Emissive.a = 0.0f;

	m_pDevice = pDevice;
	SetXPosition(vecPos.x);
	SetYPosition(vecPos.y);
	SetZPosition(vecPos.z);

	//m_vecSize = vecSize;
	SetXScale(vecSize.x);
	SetYScale(vecSize.y);
	SetZScale(vecSize.z);

	m_color = colorPlat;
	m_vecSpeed = vecSpeed;

	PLATFORMVERTEX vertices[] =
	{
		{ -5.0f, 1.0f, -5.0f, 0.0f, 0.0f, -1.0f, D3DCOLOR_XRGB(255, 0, 0)},//0
		{ 5.0f, 1.0f, -5.0f,  0.0f, 0.0f, -1.0f, D3DCOLOR_XRGB(255, 0, 0)},//1
		{ -5.0f, -1.0f, -5.0f, 0.0f, 0.0f, -1.0f, D3DCOLOR_XRGB(255, 0, 0)},//2

		{ -5.0f, -1.0f, -5.0f, 0.0f, 0.0f, -1.0f, D3DCOLOR_XRGB(255, 0, 0)},//2
		{ 5.0f, 1.0f, -5.0f,  0.0f, 0.0f, -1.0f, D3DCOLOR_XRGB(255, 0, 0)},//1
		{ 5.0f, -1.0f, -5.0f, 0.0f, 0.0f, -1.0f, D3DCOLOR_XRGB(255, 0, 0)},//3

		{ -5.0f, 1.0f, 5.0f, -1.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0)}, //4
		{ -5.0f, 1.0f, -5.0f, -1.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0)},//0
		{ -5.0f, -1.0f, 5.0f, -1.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0)}, //6

		{ -5.0f, -1.0f, 5.0f, -1.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0)}, //6
		{ -5.0f, 1.0f, -5.0f, -1.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0)},//0
		{ -5.0f, -1.0f, -5.0f, -1.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0)},//2

		{ 5.0f, -1.0f, 5.0f, 0.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0)},   //7
		{ 5.0f, 1.0f, 5.0f, 0.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0)},	  //5
		{ -5.0f, -1.0f, 5.0f, 0.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0)}, //6

		{ -5.0f, -1.0f, 5.0f, 0.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0)}, //6
		{ 5.0f, 1.0f, 5.0f, 0.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0)},	  //5
		{ -5.0f, 1.0f, 5.0f, 0.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0)}, //4

		{ 5.0f, -1.0f, -5.0f, 1.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0)},  // 3
		{ 5.0f, 1.0f, -5.0f, 1.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0)}, //1
		{ 5.0f, -1.0f, 5.0f, 1.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0)},   //7

		{ 5.0f, -1.0f, 5.0f, 1.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0)},   //7
		{ 5.0f, 1.0f, -5.0f, 1.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0)}, //1
		{ 5.0f, 1.0f, 5.0f, 1.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0)},	  //5

		{ -5.0f, 1.0f, 5.0f, 0.0f, 1.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0)},     // 4
		{ 5.0f, 1.0f, 5.0f, 0.0f, 1.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0)},	  //5
		{ -5.0f, 1.0f, -5.0f, 0.0f, 1.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0)}, //0

		{ -5.0f, 1.0f, -5.0f, 0.0f, 1.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0)}, //0
		{ 5.0f, 1.0f, 5.0f, 0.0f, 1.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0)},	  //5
		{ 5.0f, 1.0f, -5.0f, 0.0f, 1.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0)},//1

		{ 5.0f, -1.0f, -5.0f, 0.0f, -1.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0)},  // 3
		{ 5.0f, -1.0f, 5.0f, 0.0f, -1.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0)},   //7
		{ -5.0f, -1.0f, -5.0f, 0.0f, -1.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0)},   // 2

		{ -5.0f, -1.0f, -5.0f, 0.0f, -1.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0)},   // 2
		{ 5.0f, -1.0f, 5.0f, 0.0f, -1.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0)},   //7
		{ -5.0f, -1.0f, 5.0f, 0.0f, -1.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0)},    //6
	};

	m_pDevice->CreateVertexBuffer(sizeof(vertices),
		0, D3DFVF_PLATFORM, D3DPOOL_MANAGED, &m_pVertexBuffer, NULL);

	void * pVoid;
	m_pVertexBuffer->Lock(0, 0, &pVoid, 0);
	memcpy(pVoid,(void *)vertices,sizeof(vertices));
	m_pVertexBuffer->Unlock();

	//short indices[] =
	//{
	//	0, 1, 2,    // side 1
	//	2, 1, 3,
	//	4, 0, 6,    // side 2
	//	6, 0, 2,
	//	7, 5, 6,    // side 3
	//	6, 5, 4,
	//	3, 1, 7,    // side 4
	//	7, 1, 5,
	//	4, 5, 0,    // side 5
	//	0, 5, 1,
	//	3, 7, 2,    // side 6
	//	2, 7, 6,
	//};
	//m_pDevice->CreateIndexBuffer(36 * sizeof(short),
	//	0,
	//	D3DFMT_INDEX16,
	//	D3DPOOL_MANAGED,
	//	&m_pIndexBuffer,
	//	NULL);

	//// lock i_buffer and load the indices into it
	//m_pIndexBuffer->Lock(0, 0, &pVoid, 0);
	//memcpy(pVoid, indices, sizeof(indices));
	//m_pIndexBuffer->Unlock();
}

void CPlatform::Update(float fElapseTime)
{
	TranslateBy(m_vecSpeed.x * fElapseTime, m_vecSpeed.y * fElapseTime, m_vecSpeed.z * fElapseTime);
}

void CPlatform::Render()
{
	m_pDevice->SetFVF(D3DFVF_PLATFORM);
	m_pDevice->SetStreamSource(0, m_pVertexBuffer, 0,sizeof(PLATFORMVERTEX));
	//m_pDevice->SetIndices(m_pIndexBuffer);

	D3DXMATRIX matWorldTrans = GetTransform();
	m_pDevice->SetTransform( D3DTS_WORLD, &matWorldTrans );

	m_pDevice->LightEnable(0, TRUE);
	m_pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	m_pDevice->SetMaterial(&m_material);

	m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 12);
}
