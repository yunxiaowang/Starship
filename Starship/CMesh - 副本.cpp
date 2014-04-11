#include "stdafx.h"
#include "CMesh.h"

CMesh::CMesh()
	:m_pMesh(NULL), m_materialCount(0), m_pMaterials(NULL), m_ppTextures(NULL)
{
	
}

CMesh::~CMesh()
{
	Release();
}

BOOL CMesh::Initialize(LPDIRECT3DDEVICE9 pDevice, WCHAR * meshFile)
{
	LPD3DXBUFFER pBuffer;
	HRESULT hr;

	m_pDevice = pDevice;

	hr = D3DXLoadMeshFromX(meshFile, D3DXMESH_MANAGED, 
		pDevice, NULL, &pBuffer, NULL, &m_materialCount, &m_pMesh);

	if(FAILED(hr))
	{
		MessageBox(0, L"D3DXLoadMeshFromX FAILED!", L"Error", 0);
		return FALSE;
	}

	D3DXMATERIAL * pMaterials = (D3DXMATERIAL*)(pBuffer->GetBufferPointer());

	m_pMaterials = new D3DMATERIAL9[m_materialCount];
	m_ppTextures = new LPDIRECT3DTEXTURE9[m_materialCount];

	CHAR strTextureFile[100];

	for(int i = 0;i < m_materialCount;i++)
	{
		m_pMaterials[i] = pMaterials[i].MatD3D;
		m_pMaterials[i].Ambient = m_pMaterials[i].Diffuse;

		m_ppTextures[i] = NULL;
		if(pMaterials[i].pTextureFilename)
		{
			sprintf_s(strTextureFile,"media\\%s",pMaterials[i].pTextureFilename);
			hr = D3DXCreateTextureFromFileA(pDevice, strTextureFile, &m_ppTextures[i]);

			if(FAILED(hr))
			{
				MessageBox(0, L"D3DXCreateTextureFromFile FAILED!", L"Error", 0);
				return FALSE;
			}
		}
	}

	pBuffer->Release();

	SetYRotation(D3DX_PI);

	return TRUE;
}

void CMesh::Release()
{
	FAST_DELETE_ARRAY(m_pMaterials);

	if(m_ppTextures)
	{
		for(int i = 0;i < m_materialCount;i++)
			FAST_RELEASE(m_ppTextures[i]);

		FAST_DELETE_ARRAY(m_ppTextures);
	}

	FAST_RELEASE(m_pMesh);
}

void CMesh::Render()
{
	D3DXMATRIX matWorldTrans = GetTransform();
	m_pDevice->SetTransform(D3DTS_WORLD, &matWorldTrans);

	m_pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

	for(int i = 0;i < m_materialCount;i++)
	{
		m_pDevice->SetMaterial(&m_pMaterials[i]);
		m_pDevice->SetTexture(0, m_ppTextures[i]);
		m_pMesh->DrawSubset(i);
	}

	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pDevice->SetRenderState(D3DRS_SPECULARENABLE, FALSE);
}


void CMesh::Update()
{
	if(m_pParent)
	{
		SetXPosition(m_pParent->GetXPosition());
		SetYPosition(m_pParent->GetYPosition() + 2.0f);
		SetZPosition(m_pParent->GetZPosition());
	}
}

void CMesh::setParent(CWorldTransform * pParent)
{
	m_pParent = pParent;
}