#ifndef CMESH_H
#define CMESH_H

#include "stdafx.h"
#include "CWorldTransform.h"

class CMesh : public CWorldTransform
{
public:
	CMesh();
	virtual ~CMesh();

	BOOL Initialize(LPDIRECT3DDEVICE9 pDevice, WCHAR * meshFile);
	void Release();

	void Update();

	void Render();

	void setParent(CWorldTransform * pParent);

private:
	LPD3DXMESH m_pMesh;
	DWORD m_materialCount;
	D3DMATERIAL9 * m_pMaterials;
	LPDIRECT3DTEXTURE9 * m_ppTextures;

	LPDIRECT3DDEVICE9 m_pDevice;

	CWorldTransform * m_pParent;
};

#endif