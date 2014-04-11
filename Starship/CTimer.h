#ifndef CTIMER_H
#define CTIMER_H

#include "stdafx.h"

class CTimer
{
public:
	CTimer();
	virtual ~CTimer();

	void Start();
	void Stop();
	void Tick();

	float GetElapsedTime();
	float GetFPS();

private:
	INT64 m_i64Frequency;

	INT64 m_i64CurrentTime;
	INT64 m_i64LastTime;

	float m_fElapsedTime;

	LARGE_INTEGER m_largeInterger;

	BOOL m_bStoped;

	float m_nFPS;
	INT m_nFrameCount;
	INT64 m_i64TimeAddup;
};

#endif