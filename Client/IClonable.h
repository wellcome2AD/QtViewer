#pragma once

class IClonable
{
public:
	virtual ~IClonable() = default;
	virtual IClonable* Clone() const = 0;
};
