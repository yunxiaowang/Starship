#include "stdafx.h"
#include "CControlObject.h"

CControlObject::CControlObject()
	: CWorldTransform()
{
	m_vecPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_vecUp    = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_vecLook  = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
}

CControlObject::CControlObject(const D3DXVECTOR3 & vecPos, const D3DXVECTOR3 & vecLook, 
				 const D3DXVECTOR3 & vecUp, const D3DXVECTOR3 & vecRight)
{
	m_vecPos = vecPos;
	m_vecLook = vecLook;
	m_vecUp = vecUp;
	m_vecRight = vecRight;

	SetPosition(vecPos);
}

CControlObject::~CControlObject()
{
}

void CControlObject::GoRight(float fDistance)
{
	m_vecPos += m_vecRight * fDistance;
	SetPosition(m_vecPos);
}

void CControlObject::GoUp(float fDistance)
{
	m_vecPos += m_vecUp * fDistance;
	SetPosition(m_vecPos);
}

void CControlObject::GoForward(float fDistance)
{
	m_vecPos += m_vecLook * fDistance;
	SetPosition(m_vecPos);
}

// rotate on right vector
void CControlObject::Pitch(float fAngle)
{
	D3DXMATRIX mat;
	D3DXMatrixRotationAxis(&mat, &m_vecRight,	fAngle);
	m_rotate = m_rotate * mat;


	// rotate up and look vector
	D3DXVec3TransformCoord(&m_vecUp,&m_vecUp, &mat);
	D3DXVec3TransformCoord(&m_vecLook,&m_vecLook, &mat);

	//todo
}

// rotate on up vector
void CControlObject::Yaw(float fAngle)
{
	D3DXMATRIX mat;

	D3DXMatrixRotationAxis(&mat, &m_vecUp, fAngle);
	m_rotate = m_rotate * mat;


	// rotate right and look vector
	D3DXVec3TransformCoord(&m_vecRight,&m_vecRight, &mat);
	D3DXVec3TransformCoord(&m_vecLook,&m_vecLook, &mat);

	//todo
}

// rotate on look vector
void CControlObject::Roll(float fAngle)
{
	D3DXMATRIX mat;
	//D3DXMatrixRotationAxis(&mat, &m_vecLook, fAngle);
	D3DXMatrixRotationAxis(&mat, &m_vecLook, fAngle);
	m_rotate = m_rotate * mat;

	// rotate up and right vector
	D3DXVec3TransformCoord(&m_vecRight,&m_vecRight, &mat);
	D3DXVec3TransformCoord(&m_vecUp,&m_vecUp, &mat);

	//todo
}

D3DMATRIX CControlObject::getViewMatrix(D3DXMATRIX * pmatView)
{
	D3DXMATRIX matView;

	D3DXVec3Normalize(&m_vecLook, &m_vecLook);

	D3DXVec3Cross(&m_vecUp, &m_vecLook, &m_vecRight);
	D3DXVec3Normalize(&m_vecUp, &m_vecUp);

	D3DXVec3Cross(&m_vecRight, &m_vecUp, &m_vecLook);
	D3DXVec3Normalize(&m_vecRight, &m_vecRight);

	//D3DXVECTOR3 matWorldPos = this->GetPosition();

	////float x = -D3DXVec3Dot(&m_vecRight, &m_vecPos);
	////float y = -D3DXVec3Dot(&m_vecUp, &m_vecPos);
	////float z = -D3DXVec3Dot(&m_vecLook, &m_vecPos);
	//float x = -D3DXVec3Dot(&m_vecRight, &matWorldPos);
	//float y = -D3DXVec3Dot(&m_vecUp, &matWorldPos);
	//float z = -D3DXVec3Dot(&m_vecLook, &matWorldPos);

	//matView(0,0) = m_vecRight.x; matView(0, 1) = m_vecUp.x; matView(0, 2) = m_vecLook.x; matView(0, 3) = 0.0f;
	//matView(1,0) = m_vecRight.y; matView(1, 1) = m_vecUp.y; matView(1, 2) = m_vecLook.y; matView(1, 3) = 0.0f;
	//matView(2,0) = m_vecRight.z; matView(2, 1) = m_vecUp.z; matView(2, 2) = m_vecLook.z; matView(2, 3) = 0.0f;
	//matView(3,0) = x;        matView(3, 1) = y;     matView(3, 2) = z; matView(3, 3) = 1.0f; 

	D3DXMATRIX matWorld = GetTransform();
	D3DXMatrixInverse(&matView, 0, &matWorld);

	if(pmatView)
		* pmatView = matView;

	return matView;
}

//D3DXVECTOR3 CControlObject::getPosition(D3DXVECTOR3 * pvecPos)
//{
//	D3DXVECTOR3 worldPos = m_vecPos;
//	if(m_pParent)
//		worldPos += m_pParent->GetPosition();
//
//	if(pvecPos)
//		* pvecPos = worldPos;
//
//	return worldPos;
//}

void CControlObject::setPosition(const D3DXVECTOR3 * const pvecPos)
{
	m_vecPos = * pvecPos;
	SetPosition(m_vecPos);
}

D3DXVECTOR3 CControlObject::getRight(D3DXVECTOR3 * pvecRight)
{
	if(pvecRight)
		* pvecRight = m_vecRight;

	return m_vecRight;
}

D3DXVECTOR3 CControlObject::getUp(D3DXVECTOR3 * pvecUp)
{
	if(pvecUp)
		* pvecUp = m_vecUp;

	return m_vecUp;
}
D3DXVECTOR3 CControlObject::getLook(D3DXVECTOR3 * pvecLook)
{
	if(pvecLook)
		* pvecLook = m_vecLook;

	return m_vecLook;
}

void CControlObject::PitchX(float fAngle)
{

}

void CControlObject::YawY(float fAngle)
{
	//odPrintfA("fAngle:%f", fAngle);

	D3DXMATRIX mat;

	D3DXMatrixRotationY(&mat, fAngle);

	m_transform = m_transform * mat;

	//if(fAngle < 0.0f)
	//{
	//	m_transform = m_translate * mat;
	//}

	m_vecRight = D3DXVECTOR3(m_transform._11, m_transform._12, m_transform._13);
	//odPrintfA("m_vecRight: %f %f %f", m_transform._11, m_transform._12,m_transform._13);
	m_vecUp = D3DXVECTOR3(m_transform._21, m_transform._22, m_transform._23);
	m_vecLook = D3DXVECTOR3(m_transform._31, m_transform._32, m_transform._33);
	m_vecPos = D3DXVECTOR3(m_transform._41, m_transform._42, m_transform._43);

	SetPosition(m_vecPos);

	D3DXMatrixInverse(&mat, 0, &m_scale);
	D3DXMATRIX matRotate = mat;
	matRotate = matRotate * m_transform;
	D3DXMatrixInverse(&mat, 0, &m_translate);
	m_rotate = matRotate * mat;
}

void CControlObject::RollZ(float fAngle)
{

}