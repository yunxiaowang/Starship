#ifndef CAIRPLANE_H
#define CAIRPLANE_H

#include "stdafx.h"
#include "CMesh.h"
//#include "CWorldTransform.h"

class CAirplane
{
public:
	CAirplane();
	virtual ~CAirplane();

	void Initialize(LPDIRECT3DDEVICE9 pDevice, WCHAR * meshFile, D3DXVECTOR3 vecLocal, CWorldTransform * pParent);

	void Update();
	void Render();

private:
	CMesh m_Mesh;

	LPDIRECT3DDEVICE9 m_pDevice;

	//D3DXVECTOR3 m_vecLocal;

	//CWorldTransform * m_pParent;
};

#endif