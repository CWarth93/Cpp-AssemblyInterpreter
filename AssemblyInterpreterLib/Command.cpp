#include "stdafx.h"

#include "Command.h"


Command::Command(std::vector<std::string> line, uint64_t lineNumber)
{
	this->setType(line);
	this->setFirstArgument(line);
	this->setSecondArgument(line);
	this->lineNumber = lineNumber;
}

Command::~Command()
{
}

uint64_t Command::getLineNumber()
{
	return this->lineNumber;
}

std::string Command::getType()
{
	return this->type;
}

std::string Command::getArg1()
{
	return this->arg1;
}

std::string Command::getArg2()
{
	return this->arg2;
}

bool Command::hasOneArgument()
{	
	return (this->arg1 != "");
}

bool Command::hasTwoArguments()
{
	return (this->arg2 != "");
}

void Command::setType(std::vector<std::string> line)
{
	if (line.size() != 0)
	{
		this->type = line.at(0);
	}
	else
	{
		this->type = "";
	}
}

void Command::setFirstArgument(std::vector<std::string> line)
{
	if (line.size() != 0)
	{
		this->arg1 = line.at(2);								
	}
	else
	{
		this->arg1 = "";
	}
}

void Command::setSecondArgument(std::vector<std::string> line)
{
	if (line.size() > 3)
	{
		this->arg2 = line.at(5);							
	}
	else
	{
		this->arg2 = "";
	}
}
