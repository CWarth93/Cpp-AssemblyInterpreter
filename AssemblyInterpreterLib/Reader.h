#pragma once

#include <string>

class AssemblyInterpreter;

class Reader
{

public:

	Reader(AssemblyInterpreter* holder);
	~Reader();

	std::string read(std::string filePath);

private:

	AssemblyInterpreter* holder;

};

