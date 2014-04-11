#include "stdafx.h"
#include "CTerrain.h"

#include <fstream>

CTerrain::CTerrain()
	: m_pDevice(NULL), m_pVertexBuffer(NULL), m_pIndexBuffer(NULL), 
	m_pHeight(NULL), m_nWidth(0),m_nLength(0), m_nVertexNumber(0),m_pTexture(NULL)
{

}

CTerrain::~CTerrain()
{
	Release();
}

//创建顶点缓存区
void CTerrain::ConstructVertexBuffer()
{
	m_pDevice->CreateVertexBuffer( m_nVertexNumber * sizeof(TerrainVertex), 0, 
		D3DFVF_TERRAIN, D3DPOOL_MANAGED, &m_pVertexBuffer, NULL);

	TerrainVertex * pVertex = new TerrainVertex[m_nWidth * m_nLength];
	float fHalfWidth = (m_nWidth - 1) / 2.0f;
	float fHalfLength = (m_nLength - 1) / 2.0f;
	for(int z = 0;z < m_nLength;z++)
		for(int x = 0;x < m_nWidth;x++)
		{
			pVertex[z * m_nWidth + x] = TerrainVertex(
				x - fHalfWidth,
				m_pHeight[z * m_nWidth + x],
				z - fHalfLength,
				(float)x / (m_nWidth - 1),
				(float)z / (m_nLength - 1));
		}

	VOID * pVertexBuffer;
	int nCpySize = m_nWidth * m_nLength * sizeof(TerrainVertex);
	m_pVertexBuffer->Lock(0, nCpySize, (void **)&pVertexBuffer, 0);
	memcpy(pVertexBuffer, pVertex, nCpySize);
	m_pVertexBuffer->Unlock();

	delete [] pVertex;
}

//创建索引缓存区
void CTerrain::ConstructIndexBuffer()
{
	UINT nIndexNumber = 6 * (m_nWidth - 1) * (m_nLength - 1);
	m_pDevice->CreateIndexBuffer(nIndexNumber * sizeof(DWORD), D3DUSAGE_WRITEONLY, 
		D3DFMT_INDEX32, D3DPOOL_MANAGED, &m_pIndexBuffer, NULL);

	DWORD * pIndex = NULL;
	int ind = 0;
	m_pIndexBuffer->Lock(0, 0, (void **)&pIndex, 0);
	for(int z = 0;z < m_nLength - 1;z++)
		for(int x = 0;x < m_nWidth - 1;x++)
		{
			pIndex[ind++] = z * m_nWidth + x;
			pIndex[ind++] = z * m_nWidth + x + m_nWidth;
			pIndex[ind++] = z * m_nWidth + x + 1;

			pIndex[ind++] = z * m_nWidth + x + 1;
			pIndex[ind++] = z * m_nWidth + x + m_nWidth;
			pIndex[ind++] = z * m_nWidth + x + m_nWidth + 1;
		}

	m_pIndexBuffer->Unlock();
}

BOOL CTerrain::Initialize(LPDIRECT3DDEVICE9 pDevice, char * strHeightFile, char * strTextureFile)
{
	Release();

	m_pDevice = pDevice;

	std::ifstream fin;
	fin.open(strHeightFile, std::ios::binary);
	if (fin.fail())
	{
		MessageBox(0, L"Can not find terrain height file!", L"Error", 0);
		return FALSE;
	}

	fin.seekg(0, std::ios::end);
	m_nVertexNumber = fin.tellg();
	fin.seekg(0, std::ios::beg);

	m_pHeight = new UCHAR[m_nVertexNumber];
	fin.read((char *)m_pHeight, m_nVertexNumber);
	fin.close();

	//m_nWidth = m_nLength = (int)sqrt((float)m_nVertexNumber);
	m_nWidth = m_nLength = 200;
	odPrintfA("m_nWidth:%d",m_nWidth);

	ConstructVertexBuffer();

	ConstructIndexBuffer();

	if (FAILED(D3DXCreateTextureFromFileA(pDevice, strTextureFile, &m_pTexture)))
	{
		MessageBox(0, L"Can not find terrain texture file!", L"Error", 0);
		return FALSE;
	}

	return TRUE;
}

void CTerrain::Release()
{
	FAST_DELETE_ARRAY(m_pHeight);
	FAST_RELEASE(m_pVertexBuffer);
	FAST_RELEASE(m_pIndexBuffer);
	FAST_RELEASE(m_pTexture);
}

void CTerrain::Render()
{
	m_pDevice->SetRenderState( D3DRS_SHADEMODE, D3DSHADE_GOURAUD );  
	m_pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	D3DXMATRIX matWorldTrans = GetTransform();
	m_pDevice->SetTransform( D3DTS_WORLD, &matWorldTrans );

	m_pDevice->SetTexture( 0, m_pTexture );
	m_pDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(TerrainVertex));

	m_pDevice->SetFVF(D3DFVF_TERRAIN);
	m_pDevice->SetIndices(m_pIndexBuffer);
	m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_nVertexNumber,
		0, 2 * (m_nLength - 1) * (m_nWidth - 1));
}