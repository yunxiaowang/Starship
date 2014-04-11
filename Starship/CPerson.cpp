#include "stdafx.h"
#include "CPerson.h"

CPerson::CPerson()
{

}

CPerson::~CPerson()
{

}

void CPerson::Initialize(LPDIRECT3DDEVICE9 pDevice, WCHAR * meshFile, D3DXVECTOR3 vecPos/*, D3DXMATRIX matLocal*/)
{
	m_pDevice = pDevice;

	m_Mesh.Initialize(pDevice, meshFile);

	m_vecPos = vecPos;
	SetPosition(vecPos);

	m_Mesh.SetXRotation(-D3DX_PI / 2);
	m_Mesh.SetYRotation(D3DX_PI);
	m_Mesh.SetXScale(0.2f);
	m_Mesh.SetYScale(0.2f);
	m_Mesh.SetZScale(0.2f);

	//m_matLocal = matLocal;

	//m_Mesh.SetXRotation(vecRotate.x);
	//m_Mesh.SetYRotation(vecRotate.y);
	//m_Mesh.SetZRotation(vecRotate.z);
}

void CPerson::Update()
{

}

void CPerson::Render()
{
	D3DXMATRIX matWorldTrans = m_Mesh.GetTransform() * this->GetTransform();
	m_pDevice->SetTransform(D3DTS_WORLD, &matWorldTrans);

	m_Mesh.Render();
}