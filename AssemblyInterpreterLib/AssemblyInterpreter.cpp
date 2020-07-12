#include "stdafx.h"
#include <vector>
#include <string>

#include "AssemblyInterpreter.h"


AssemblyInterpreter::AssemblyInterpreter(Console* console) : reader(this), parser(this), executor(this)
{
	this->console = console;
	this->log("- welcome to the assembler interpreter");
}

AssemblyInterpreter::~AssemblyInterpreter()
{
	delete this->console;
}

void AssemblyInterpreter::interprete(std::string filePath)
{
	this->error = false;
	this->log("- start");
	std::string fileContent = this->read(filePath);	
	std::vector<Command> commands = this->parse(fileContent);
	this->execute(commands);
	this->log("- end");
	this->output();
}

void AssemblyInterpreter::log(std::string newLogMsg)
{
	this->logMsg += newLogMsg + "\n";
}

void AssemblyInterpreter::setError()
{
	this->error = true;
}

std::string AssemblyInterpreter::read(std::string filePath)
{
	return this->reader.read(filePath);
}

std::vector<Command> AssemblyInterpreter::parse(std::string fileContent)
{
	return this->parser.parse(fileContent);	
}

void AssemblyInterpreter::execute(std::vector<Command> commands)
{
	this->executor.execute(commands);
}


void AssemblyInterpreter::output()
{	
	this->console->output(this->logMsg);
}

