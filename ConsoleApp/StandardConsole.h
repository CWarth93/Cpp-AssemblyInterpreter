#pragma once

#include "../AssemblyInterpreterLib/Console.h"

class StandardConsole : public Console
{

public:
	StandardConsole();
	~StandardConsole();
	void output(std::string msg);

};

