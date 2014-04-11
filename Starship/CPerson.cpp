#include "stdafx.h"
#include "CPerson.h"

CPerson::CPerson()
{

}

CPerson::~CPerson()
{

}

void CPerson::Initialize(LPDIRECT3DDEVICE9 pDevice, WCHAR * meshFile, D3DXVECTOR3 vecPos, D3DXMATRIX matLocal)
{
	m_pDevice = pDevice;

	m_Mesh.Initialize(pDevice, meshFile);

	SetXPosition(vecPos.x);
	SetYPosition(vecPos.y);
	SetZPosition(vecPos.z);

	m_matLocal = matLocal;

	//m_Mesh.SetXRotation(vecRotate.x);
	//m_Mesh.SetYRotation(vecRotate.y);
	//m_Mesh.SetZRotation(vecRotate.z);
}

void CPerson::Update()
{

}

void CPerson::Render()
{
	D3DXMATRIX matWorldTrans = m_matLocal * GetTransform();
	m_pDevice->SetTransform(D3DTS_WORLD, &matWorldTrans);

	m_Mesh.Render();
}