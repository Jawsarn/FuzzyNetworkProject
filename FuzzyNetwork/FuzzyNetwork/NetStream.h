#pragma once
#include "Stream.h"

class NetStream:Stream
{
public:
	NetStream();
	~NetStream();

	void Initialize(char* p_Buffer, int p_Length);

	int Read(int p_BytesToRead, void* p_Buffer);
	int Write(int p_BytesToWrite, const void* p_Buffer);

	bool SetCurPos(int p_Pos);
	int GetCurPos();

private:
	char * m_Message;
	int m_MaxLength;
	int m_WrittenBits;
	int m_CurrentSize;

	int m_ReadBits;
	int m_ReadCount;
};

