#include "stdafx.h"
#include "CCamera.h"

CCamera::CCamera() 
	: CControlObject()
{
	
}

CCamera::CCamera(const D3DXVECTOR3 & vecPos, const D3DXVECTOR3 & vecLook, 
	const D3DXVECTOR3 & vecUp, const D3DXVECTOR3 & vecRight)
	: CControlObject(vecPos, vecLook, vecUp, vecRight)
{

}

CCamera::~CCamera()
{
}

