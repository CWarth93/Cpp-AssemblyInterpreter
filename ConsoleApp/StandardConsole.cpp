#include "pch.h"
#include <iostream>

#include "StandardConsole.h"

StandardConsole::StandardConsole()
{
}

StandardConsole::~StandardConsole()
{
}

void StandardConsole::output(std::string msg)
{
	std::cout << msg;
}