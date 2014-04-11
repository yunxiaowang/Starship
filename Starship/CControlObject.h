#ifndef CCONTROLOBJECT_H
#define CCONTROLOBJECT_H

#include "stdafx.h"
#include "CWorldTransform.h"

class CControlObject : public CWorldTransform
{
public:
	CControlObject();
	CControlObject(const D3DXVECTOR3 & vecPos, const D3DXVECTOR3 & vecLook, 
		const D3DXVECTOR3 & vecUp, const D3DXVECTOR3 & vecRight);

	virtual ~CControlObject();

	void GoRight(float fDistance); //往右移动
	void GoUp(float fDistance); //向上移动
	void GoForward(float fDistance); //向前移动

	void Pitch(float fAngle); // 绕right vector旋转
	void Yaw(float fAngle);   // 绕up vector旋转
	void Roll(float fAngle);  // 绕look vector旋转

	D3DMATRIX getViewMatrix(D3DXMATRIX * pmatView = NULL);

	D3DXVECTOR3 getPosition(D3DXVECTOR3 * pvecPos = NULL);
	void setPosition(const D3DXVECTOR3 * const pvecPos);

	D3DXVECTOR3 getRight(D3DXVECTOR3 * pvecRight = NULL);
	D3DXVECTOR3 getUp(D3DXVECTOR3 * pvecUp = NULL);
	D3DXVECTOR3 getLook(D3DXVECTOR3 * pvecLook = NULL);

protected:
	D3DXVECTOR3 m_vecRight;
	D3DXVECTOR3 m_vecUp;
	D3DXVECTOR3 m_vecLook;
	D3DXVECTOR3 m_vecPos;
};

#endif