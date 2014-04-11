#ifndef CPERSON_H
#define CPERSON_H

#include "stdafx.h"
#include "CMesh.h"
#include "CWorldTransform.h"
#include "CControlObject.h"

class CPerson : public CControlObject
{
public:
	CPerson();
	virtual ~CPerson();

	void Initialize(LPDIRECT3DDEVICE9 pDevice, WCHAR * meshFile, D3DXVECTOR3 vecPos/*, D3DXMATRIX matLocal*/);

	void Update();
	void Render();

private:
	CMesh m_Mesh;

	//D3DXMATRIX m_matLocal;

	LPDIRECT3DDEVICE9 m_pDevice;
};

#endif