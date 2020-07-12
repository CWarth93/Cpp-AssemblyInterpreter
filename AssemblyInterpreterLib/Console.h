#pragma once

#include <string>

class Console
{

public:
	Console() = default;
	~Console() = default;
	virtual void output(std::string msg) = 0;

};

