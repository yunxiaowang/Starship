#ifndef CCAMERA_H
#define CCAMERA_H

#include "stdafx.h"
#include "CControlObject.h"

class CCamera : public CControlObject
{
public:
	CCamera();
	CCamera(const D3DXVECTOR3 & vecPos, const D3DXVECTOR3 & vecLook, 
		const D3DXVECTOR3 & vecUp, const D3DXVECTOR3 & vecRight);

	virtual ~CCamera();
};


#endif