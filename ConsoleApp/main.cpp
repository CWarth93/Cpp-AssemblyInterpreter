#include "pch.h"
#include <iostream>

#include "../AssemblyInterpreterLib/AssemblyInterpreter.h"
#include "StandardConsole.h"

int main()
{
	AssemblyInterpreter interpreter(new StandardConsole());
	interpreter.interprete("../input.txt");
}
