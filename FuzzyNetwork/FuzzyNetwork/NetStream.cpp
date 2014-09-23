#include "NetStream.h"


NetStream::NetStream()
{
}


NetStream::~NetStream()
{
}

void NetStream::Initialize(char* p_Buffer, int p_Length)
{
	m_Message = p_Buffer;
	m_MaxLength = p_Length;
	m_WrittenBits = 0;
	m_CurrentSize = 0;
	int m_ReadBits;
	int m_ReadCount;
}


int NetStream::Read(int p_BytesToRead, void* p_Buffer)
{
	int o_Value = 0;
	int t_ValueBits = 0;
	int t_Get = 0;
	int t_Fraction = 0;

	while (t_ValueBits < p_BytesToRead)
	{
		if (m_ReadBits == 0)
		{
			m_ReadCount++;
		}

		t_Get = 8 - m_ReadBits;
		if (t_Get > p_BytesToRead - t_ValueBits)
		{
			t_Get = p_BytesToRead - t_ValueBits;
		}
		t_Fraction = m_Message[m_ReadCount - 1];
		t_Fraction >>= m_ReadBits;
		t_Fraction &= ((1 << t_Get) - 1);
		o_Value |= t_Fraction << t_ValueBits;

		t_ValueBits += t_Get;
		m_ReadBits = (m_ReadBits + t_Get) & 7;
	}
}

int NetStream::Write(int p_BytesToWrite, const void* p_Buffer)
{
	int t_Put = 0;
	int t_Fraction = 0;

	while (p_BytesToWrite)
	{
		if (m_WrittenBits == 0)
		{
			m_Message[m_CurrentSize] = 0;
			m_CurrentSize++;
		}

		t_Put = 8 - m_WrittenBits;
		if (t_Put > p_BytesToWrite)
		{
			t_Put = p_BytesToWrite;
		}

		t_Fraction = (int)p_Buffer & ((1 << t_Put) - 1);
		m_Message[m_CurrentSize - 1] |= t_Fraction << m_WrittenBits;
		p_BytesToWrite -= t_Put;
		m_WrittenBits = (m_WrittenBits + t_Put) & 7;
	}
}

bool SetCurPos(int p_Pos)
{

}

int GetCurPos()
{

}
