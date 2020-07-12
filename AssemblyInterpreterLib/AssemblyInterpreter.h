#pragma once

#include <vector>

#include "Console.h"
#include "Reader.h"
#include "Parser.h"
#include "Executor.h"

class AssemblyInterpreter
{

public:

	AssemblyInterpreter(Console* console);
	~AssemblyInterpreter();

	void interprete(std::string filePath);
	void log(std::string newLogMsg);
	void setError();

private:

	Console* console;

	Reader reader;
	Parser parser;
	Executor executor;
	
	std::string logMsg;	
	bool error;

	std::string read(std::string filePath);
	std::vector<Command> parse(std::string fileContent);
	void execute(std::vector<Command> commands);
	void output();	

};