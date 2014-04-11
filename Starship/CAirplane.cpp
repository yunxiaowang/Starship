#include "stdafx.h"
#include "CAirplane.h"

CAirplane::CAirplane()
{

}

CAirplane::~CAirplane()
{

}

void CAirplane::Initialize(LPDIRECT3DDEVICE9 pDevice, WCHAR * meshFile, D3DXVECTOR3 vecLocal, CWorldTransform * pParent)
{
	m_pDevice = pDevice;

	m_Mesh.Initialize(pDevice, meshFile);
	//m_vecLocal = vecLocal;
	m_Mesh.SetXPosition(vecLocal.x);
	m_Mesh.SetYPosition(vecLocal.y);
	m_Mesh.SetZPosition(vecLocal.z);

	SetYRotation(D3DX_PI);

	m_pParent = pParent;
}

void CAirplane::Update()
{
	SetXPosition(m_Mesh.GetXPosition() + m_pParent->GetXPosition());
	SetYPosition(m_Mesh.GetYPosition() + m_pParent->GetYPosition());
	SetZPosition(m_Mesh.GetZPosition() + m_pParent->GetZPosition());
}

void CAirplane::Render()
{
	D3DXMATRIX matWorldTrans = GetTransform();
	m_pDevice->SetTransform(D3DTS_WORLD, &matWorldTrans);

	m_Mesh.Render();
}