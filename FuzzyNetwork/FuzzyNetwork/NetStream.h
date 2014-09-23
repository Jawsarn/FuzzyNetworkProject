#pragma once
#include "Stream.h"

class NetStream:Stream
{
public:
	NetStream();
	~NetStream();

	

	virtual int Read(int p_BytesToRead, void* p_Buffer);
	virtual int Write(int p_BytesToWrite, const void* p_Buffer);

	virtual bool SetCurPos(int p_Pos);
	virtual int GetCurPos();
};

