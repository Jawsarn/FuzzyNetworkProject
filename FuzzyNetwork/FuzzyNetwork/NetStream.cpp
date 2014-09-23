#include "NetStream.h"


NetStream::NetStream()
{
}


NetStream::~NetStream()
{
}

void NetStream::Initialize(NET_MESSAGE* p_Buffer, int p_Length)
{
	m_isReading = false;
	m_isWriting = false;
	m_Message = p_Buffer;
	m_MaxLength = p_Length;
	m_WrittenBits = 0;
	m_CurrentSize = 0;
	m_ReadBits = 0;
	m_ReadCount = 0;
}


int NetStream::Read(int p_BytesToRead, void* p_Buffer)
{
	p_BytesToRead *= 8; //32 bits ints noob!
	if (m_isWriting)
		return 0;
	
	else
		m_isReading = true;


	//int o_Value = 0;
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
		*(int*)p_Buffer |= t_Fraction << t_ValueBits;

		t_ValueBits += t_Get;
		m_ReadBits = (m_ReadBits + t_Get) & 7;
	}
	
	return 0;

}

int NetStream::Write(int p_BytesToWrite, const void* p_Buffer)
{
	int o_something = p_BytesToWrite;
	p_BytesToWrite *= 8;
	if (m_isReading)
		return 0;

	else
		m_isWriting = true;


	
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

		t_Fraction = *(int*)p_Buffer & ((1 << t_Put) - 1);
		m_Message[m_CurrentSize - 1] |= t_Fraction << m_WrittenBits;
		p_BytesToWrite -= t_Put;
		*(int*)p_Buffer >>= t_Put;
		m_WrittenBits = (m_WrittenBits + t_Put) & 7;
	}
	return o_something;
}

bool NetStream::SetCurPos(int p_Pos)
{
	return true;
}

int NetStream::GetCurPos()
{
	return 0;
}
