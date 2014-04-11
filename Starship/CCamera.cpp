#include "stdafx.h"
#include "CCamera.h"

CCamera::CCamera()
{
	m_vecPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_vecUp    = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_vecLook  = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
}

CCamera::CCamera(const D3DXVECTOR3 & vecPos, const D3DXVECTOR3 & vecLook, 
	const D3DXVECTOR3 & vecUp, const D3DXVECTOR3 & vecRight)
{
	m_vecPos = vecPos;
	m_vecLook = vecLook;
	m_vecUp = vecUp;
	m_vecRight = vecRight;
}

CCamera::~CCamera()
{
}

void CCamera::GoRight(float fDistance)
{
	m_vecPos += m_vecRight * fDistance;
}

void CCamera::GoUp(float fDistance)
{
	m_vecPos += m_vecUp * fDistance;
}

void CCamera::GoForward(float fDistance)
{
	m_vecPos += m_vecLook * fDistance;
}

// rotate on right vector
void CCamera::Pitch(float fAngle)
{
	D3DXMATRIX mat;
	D3DXMatrixRotationAxis(&mat, &m_vecRight,	fAngle);

	// rotate up and look vector
	D3DXVec3TransformCoord(&m_vecUp,&m_vecUp, &mat);
	D3DXVec3TransformCoord(&m_vecLook,&m_vecLook, &mat);
}

// rotate on up vector
void CCamera::Yaw(float fAngle)
{
	D3DXMATRIX mat;

	D3DXMatrixRotationAxis(&mat, &m_vecUp, fAngle);
	// rotate right and look vector
	D3DXVec3TransformCoord(&m_vecRight,&m_vecRight, &mat);
	D3DXVec3TransformCoord(&m_vecLook,&m_vecLook, &mat);
}

// rotate on look vector
void CCamera::Roll(float fAngle)
{
	D3DXMATRIX mat;
	D3DXMatrixRotationAxis(&mat, &m_vecLook, fAngle);

	// rotate up and right vector
	D3DXVec3TransformCoord(&m_vecRight,&m_vecRight, &mat);
	D3DXVec3TransformCoord(&m_vecUp,&m_vecUp, &mat);
}

D3DMATRIX CCamera::getViewMatrix(D3DXMATRIX * pmatView)
{
	D3DXMATRIX matView;

	D3DXVec3Normalize(&m_vecLook, &m_vecLook);

	D3DXVec3Cross(&m_vecUp, &m_vecLook, &m_vecRight);
	D3DXVec3Normalize(&m_vecUp, &m_vecUp);

	D3DXVec3Cross(&m_vecRight, &m_vecUp, &m_vecLook);
	D3DXVec3Normalize(&m_vecRight, &m_vecRight);

	float x = -D3DXVec3Dot(&m_vecRight, &m_vecPos);
	float y = -D3DXVec3Dot(&m_vecUp, &m_vecPos);
	float z = -D3DXVec3Dot(&m_vecLook, &m_vecPos);

	matView(0,0) = m_vecRight.x; matView(0, 1) = m_vecUp.x; matView(0, 2) = m_vecLook.x; matView(0, 3) = 0.0f;
	matView(1,0) = m_vecRight.y; matView(1, 1) = m_vecUp.y; matView(1, 2) = m_vecLook.y; matView(1, 3) = 0.0f;
	matView(2,0) = m_vecRight.z; matView(2, 1) = m_vecUp.z; matView(2, 2) = m_vecLook.z; matView(2, 3) = 0.0f;
	matView(3,0) = x;        matView(3, 1) = y;     matView(3, 2) = z; matView(3, 3) = 1.0f; 

	if(pmatView)
		* pmatView = matView;

	return matView;
}

D3DXVECTOR3 CCamera::getPosition(D3DXVECTOR3 * pvecPos)
{
	if(pvecPos)
		* pvecPos = m_vecPos;
	
	return m_vecPos;
}

void CCamera::setPosition(const D3DXVECTOR3 * const pvecPos)
{
	m_vecPos = * pvecPos;
}

D3DXVECTOR3 CCamera::getRight(D3DXVECTOR3 * pvecRight)
{
	if(pvecRight)
		* pvecRight = m_vecRight;
	
	return m_vecRight;
}

D3DXVECTOR3 CCamera::getUp(D3DXVECTOR3 * pvecUp)
{
	if(pvecUp)
		* pvecUp = m_vecUp;

	return m_vecUp;
}
D3DXVECTOR3 CCamera::getLook(D3DXVECTOR3 * pvecLook)
{
	if(pvecLook)
		* pvecLook = m_vecLook;

	return m_vecLook;
}