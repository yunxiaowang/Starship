#ifndef CTERRAIN_H
#define CTERRAIN_H

#include "stdafx.h"
#include "CWorldTransform.h"

#define D3DFVF_TERRAIN (D3DFVF_XYZ | D3DFVF_TEX1)

struct TerrainVertex
{
	float x, y, z;
	float tu, tv ;
	TerrainVertex():x(0), y(0), z(0), tu(0), tv(0){}
	TerrainVertex(float xx, float yy, float zz, float uu, float vv)
		: x(xx), y(yy), z(zz), tu(uu), tv(vv){}
};

class CTerrain : public CWorldTransform
{
public:
	CTerrain();
	virtual ~CTerrain();

	BOOL Initialize(LPDIRECT3DDEVICE9 pDevice, char * strHeightFile, char * strTextureFile);
	void Release();

	void Render();

private:
	LPDIRECT3DDEVICE9 m_pDevice;

	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	UINT m_nVertexNumber;

	LPDIRECT3DINDEXBUFFER9  m_pIndexBuffer;

	UCHAR * m_pHeight;

	LPDIRECT3DTEXTURE9 m_pTexture;

	UINT m_nWidth;
	UINT m_nLength;

	void ConstructVertexBuffer();
	void ConstructIndexBuffer();

};

#endif