#include "stdafx.h"
#include "CTimer.h"

CTimer::CTimer()
{
	QueryPerformanceFrequency(&m_largeInterger);
	m_i64Frequency = m_largeInterger.QuadPart;
	odPrintfA("m_i64Frequency:%d",m_i64Frequency);

	m_bStoped = TRUE;
}

CTimer::~CTimer()
{
}

void CTimer::Start()
{
	m_bStoped = FALSE;
	m_nFPS = 0;
	m_i64TimeAddup = 0;
	m_nFrameCount = 0;

	QueryPerformanceCounter(&m_largeInterger);
	m_i64CurrentTime = m_i64LastTime = m_largeInterger.QuadPart;
}

void CTimer::Tick()
{
	if(m_bStoped)
		return;

	m_i64LastTime = m_i64CurrentTime;
	QueryPerformanceCounter(&m_largeInterger);
	m_i64CurrentTime = m_largeInterger.QuadPart;

	m_i64TimeAddup += m_i64CurrentTime - m_i64LastTime;
	m_nFrameCount ++;
	if(m_i64TimeAddup > m_i64Frequency)
	{
		m_nFPS = (float)m_nFrameCount * m_i64Frequency / m_i64TimeAddup;
		//odPrintfA("FPS:%f",m_nFPS);
		m_i64TimeAddup = 0;
	}

	m_fElapsedTime = (float)(m_i64CurrentTime - m_i64LastTime) / m_i64Frequency;
}

void CTimer::Stop()
{
	m_bStoped = TRUE;
}

float CTimer::GetElapsedTime()
{
	return m_fElapsedTime;
}

float CTimer::GetFPS()
{
	return m_nFPS;
}