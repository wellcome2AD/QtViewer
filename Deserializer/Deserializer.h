#pragma once

class Deserializer
{
public:
	virtual ~Deserializer() = default;
	virtual void Recv() = 0;
	virtual char GetChar() = 0;
};
