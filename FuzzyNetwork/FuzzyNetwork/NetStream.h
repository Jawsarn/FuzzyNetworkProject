#pragma once
#include "Stream.h"

#define MAX_SIZE_OF_BUFFER 1024


typedef unsigned char NET_MESSAGE;

class NetStream:public Stream
{


public:
	NetStream();
	~NetStream();

	void Initialize(NET_MESSAGE* p_Buffer, int p_Length);

	int Read(int p_BytesToRead, void* p_Buffer);
	int Write(int p_BytesToWrite, const void* p_Buffer);

	bool SetCurPos(int p_Pos);
	int GetCurPos();

private:
	NET_MESSAGE* m_Message;
	int m_MaxLength;
	int m_WrittenBits;
	int m_CurrentSize;

	int m_ReadBits;
	int m_ReadCount;

	bool m_isWriting;
	bool m_isReading;
};

