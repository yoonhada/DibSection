#include "stdafx.h"

CFrequency::CFrequency() 
: m_fFrequency( 0.0f ) 
, m_fFrametime( 0.0f )
, m_nCount( 0 )
{
	QueryPerformanceFrequency( &Frequency );
}

CFrequency::~CFrequency()
{
}

VOID CFrequency::Update()
{
	QueryPerformanceCounter( &EndCounter );
	m_fFrametime = static_cast<FLOAT>( EndCounter.QuadPart - StartCounter.QuadPart ) / static_cast<FLOAT>(Frequency.QuadPart);
	StartCounter = EndCounter;

	if ( m_nCount++ == MAX )
	{
		m_fFrequency = 1.0f / m_fFrametime;

		m_nCount = 0;
	}
}