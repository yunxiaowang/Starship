#include "stdafx.h"
#include "CWorldTransform.h"

CWorldTransform::CWorldTransform()
{
	D3DXMatrixIdentity( &m_translate );
	D3DXMatrixIdentity( &m_rotate );
	D3DXMatrixIdentity( &m_scale );
	D3DXMatrixIdentity( &m_transform );
	m_rotationX = m_rotationY = m_rotationZ = 0.0f;

	m_pParent = NULL;
}

CWorldTransform::~CWorldTransform()
{

}

void CWorldTransform::TranslateTo(float x, float y, float z)
{
	m_translate._41 = x;
	m_translate._42 = y;
	m_translate._43 = z;
}

void CWorldTransform::TranslateBy(float x, float y, float z)
{
	m_translate._41 += x;
	m_translate._42 += y;
	m_translate._43 += z;
}

void CWorldTransform::RotateTo(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
	D3DXMatrixRotationYawPitchRoll( &m_rotate, y, x, z );
}

void CWorldTransform::RotateBy(float x, float y, float z)
{
	m_rotationX += x;
	m_rotationY += y;
	m_rotationZ += z;
	D3DXMatrixRotationYawPitchRoll(&m_rotate,  m_rotationY,  m_rotationX,  m_rotationZ);
}

void CWorldTransform::ScaleTo(float x, float y, float z)
{
	m_scale._11 = x;
	m_scale._22 = y;
	m_scale._33 = z;
}

void CWorldTransform::ScaleBy(float x, float y, float z)
{
	m_scale._11 += x;
	m_scale._22 += y;
	m_scale._33 += z;
}

D3DXMATRIX CWorldTransform::GetTransform()
{
	m_transform = m_scale * m_rotate * m_translate; 
	
	if(m_pParent)
		return m_transform * m_pParent->GetTransform();

	return m_transform;
}

float CWorldTransform::GetXPosition() 
{
	return m_translate._41; 
}

float CWorldTransform::GetYPosition() 
{
	return m_translate._42; 
}

float CWorldTransform::GetZPosition() 
{
	return m_translate._43; 
}

float CWorldTransform::GetXRotation() 
{
	return m_rotationX; 
}

float CWorldTransform::GetYRotation() 
{ 
	return m_rotationY; 
}

float CWorldTransform::GetZRotation() 
{ 
	return m_rotationZ; 
}

float CWorldTransform::GetXScale()    
{ 
	return m_scale._11; 
}

float CWorldTransform::GetYScale()    
{ 
	return m_scale._22;
}

float CWorldTransform::GetZScale()    
{ 
	return m_scale._33; 
}

void CWorldTransform::SetXPosition( float x ) 
{ 
	m_translate._41 = x; 
}

void CWorldTransform::SetYPosition( float y ) 
{ 
	m_translate._42 = y;
}

void CWorldTransform::SetZPosition( float z ) 
{ 
	m_translate._43 = z; 
}

void CWorldTransform::SetXRotation( float x ) 
{ 
	RotateTo( x, m_rotationY, m_rotationZ );
}

void CWorldTransform::SetYRotation( float y ) 
{ 
	RotateTo( m_rotationX, y, m_rotationZ ); 
}

void CWorldTransform::SetZRotation( float z ) 
{ 
	RotateTo( m_rotationX, m_rotationY, z ); 
}

void CWorldTransform::SetXScale( float x )   
{
	m_scale._11 = x;
}

void CWorldTransform::SetYScale( float y )    
{  
	m_scale._22 = y; 
}

void CWorldTransform::SetZScale( float z )    
{
	m_scale._33 = z; 
}

void CWorldTransform::SetPosition(D3DXVECTOR3 vecPos)
{
	m_translate._41 = vecPos.x; 
	m_translate._42 = vecPos.y;
	m_translate._43 = vecPos.z; 
}


void CWorldTransform::SetParent(CWorldTransform * pParent)
{
	m_pParent = pParent;
}

D3DXVECTOR3 CWorldTransform::GetPosition()
{
	D3DXVECTOR3 vecPos = D3DXVECTOR3(m_translate._41, m_translate._42, m_translate._43);
	if(m_pParent)
		vecPos += m_pParent->GetPosition();
	return vecPos;
}
