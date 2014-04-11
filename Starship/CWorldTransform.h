#ifndef CWORLDMATRIX_H
#define CWORLDMATRIX_H

#include "stdafx.h"

class CWorldTransform
{
public:
	CWorldTransform();
	virtual  ~CWorldTransform();

	void TranslateTo(float x, float y, float z);
	void TranslateBy(float x, float y, float z);
	void RotateTo(float x, float y, float z);
	void RotateBy(float x, float y, float z);
	void ScaleTo(float x, float y, float z);
	void ScaleBy(float x, float y, float z);

	D3DXMATRIX GetTransform();

	float GetXPosition();
	float GetYPosition();
	float GetZPosition();
	float GetXRotation();
	float GetYRotation();
	float GetZRotation();
	float GetXScale();
	float GetYScale();
	float GetZScale();

	D3DXVECTOR3 GetPosition();

	void SetXPosition(float x);
	void SetYPosition(float y);
	void SetZPosition(float z);
	void SetXRotation(float x);
	void SetYRotation(float y);
	void SetZRotation(float z);
	void SetXScale(float x);
	void SetYScale(float y);
	void SetZScale(float z);

	void SetPosition(D3DXVECTOR3 vecPos);

	void SetParent(CWorldTransform * pParent);
	
protected:
	D3DXMATRIX m_translate;
	D3DXMATRIX m_rotate;
	D3DXMATRIX m_scale;
	D3DXMATRIX m_transform;
	float m_rotationX, m_rotationY, m_rotationZ;

	CWorldTransform * m_pParent;
};

#endif