#ifndef CPLATFORM_H
#define CPLATFORM_H

#include "stdafx.h"
#include "CWorldTransform.h"

#define D3DFVF_PLATFORM (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE)

struct PLATFORMVERTEX
{
	float x, y, z;
	float nx, ny, nz;
	DWORD diffuse;
};

class CPlatform: public CWorldTransform
{
public:
	CPlatform();
	//CPlatform(const D3DXVECTOR3 & vecPos, const D3DXVECTOR3 & vecSize, const D3DXCOLOR & colorSkin);

	virtual ~CPlatform();

	void Initialize(LPDIRECT3DDEVICE9 pDevice, const D3DXVECTOR3 & vecPos, const D3DXVECTOR3 & vecSize, 
		const D3DXCOLOR & colorPlat, const D3DXVECTOR3 & vecSpeed);

	void Update(float fElapseTime);
	void Render();

private:
	LPDIRECT3DDEVICE9 m_pDevice;
	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer; 
	//LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;

	//D3DXVECTOR3 m_vecSize;
	D3DMATERIAL9 m_material;
	D3DXCOLOR m_color;
	D3DXVECTOR3 m_vecSpeed;

	
};

#endif