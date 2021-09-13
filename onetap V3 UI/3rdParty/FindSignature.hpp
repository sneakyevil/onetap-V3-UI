#pragma once

#define INRANGE(x,a,b)		(x >= a && x <= b) 
#define getBits( x )		(INRANGE(x,'0','9') ? (x - '0') : ((x&(~0x20)) - 'A' + 0xa))
#define getByte( x )		(getBits(x[0]) << 4 | getBits(x[1]))

static DWORD FindSignature(DWORD m_dStart, DWORD m_dEnd, const char* m_pSignature)
{
	const unsigned char* m_pSig = reinterpret_cast<const unsigned char*>(m_pSignature);
	DWORD m_dFirstMatch = 0x0;
	for (DWORD m_dCur = m_dStart; m_dEnd > m_dCur; ++m_dCur) 
	{
		if (*(PBYTE)m_pSig == (BYTE)'\?' || *(BYTE*)(m_dCur) == getByte(m_pSig)) 
		{
			if (!m_dFirstMatch) m_dFirstMatch = m_dCur;

			m_pSig += (*(PWORD)m_pSig == (WORD)'\?\?' || *(PBYTE)m_pSig != (BYTE)'\?') ? 2 : 1;
			if (!*m_pSig) return m_dFirstMatch;

			m_pSig++;
			if (!*m_pSig) return m_dFirstMatch;
		}
		else if (m_dFirstMatch)
		{
			m_dCur = m_dFirstMatch;
			m_pSig = reinterpret_cast<const unsigned char*>(m_pSignature);
			m_dFirstMatch = 0x0;
		}
	}
	return 0x0;
}