#pragma once

class Serializer
{
public:
	virtual ~Serializer() = default;
	virtual void PutChar(char c) = 0;
	virtual void Flush() = 0;
};
