#pragma once

class CFrequency : public CSingleton<CFrequency>
{
	friend class CSingleton<CFrequency>;

	enum { MAX = 100 };
public:
	VOID Update();
	FLOAT GetFrequency()	{ return m_fFrequency; }
	FLOAT GetFrameTime()	{ return m_fFrametime; }

private:
	CFrequency();
	virtual ~CFrequency();

	LARGE_INTEGER Frequency;
	LARGE_INTEGER StartCounter, EndCounter;

	FLOAT m_fFrequency;
	FLOAT m_fFrametime;
	INT m_nCount;
};
