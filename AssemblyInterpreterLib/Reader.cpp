#include "stdafx.h"
#include <fstream>

#include "Reader.h"
#include "AssemblyInterpreter.h"


Reader::Reader(AssemblyInterpreter* holder)
{
	this->holder = holder;
}

Reader::~Reader()
{
}

std::string Reader::read(std::string filePath)
{
	std::string fileContent;
	std::string line;
	std::ifstream fileToRead(filePath);
	if (fileToRead.is_open())
	{
		while (getline(fileToRead, line))
		{
			fileContent += line + '\n';
		}
		fileToRead.close();
	}
	else
	{
		this->holder->log("!!! ERROR: Read Error: Can't open the file - Check if file exists and if youre permitted to access.");
		this->holder->setError();
	}
	return fileContent;
}
