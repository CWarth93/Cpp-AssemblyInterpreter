#pragma once

#include <vector>

#include "Command.h"

class AssemblyInterpreter;


class Executor
{

public:

	Executor(AssemblyInterpreter* holder);
	~Executor();
	void execute(std::vector<Command> commands);

private:

	AssemblyInterpreter* holder;

	std::string ax;
	std::string bx;
	std::string cx;
	std::vector<std::string> stack;

	bool doCommand(Command cmd);

	bool mov(std::string arg1, std::string arg2, uint64_t lineNumber);
	bool push(std::string arg1, uint64_t lineNumber);
	bool pop(std::string arg1, uint64_t lineNumber);
	bool add(std::string arg1, std::string arg2, uint64_t lineNumber);
	bool sub(std::string arg1, std::string arg2, uint64_t lineNumber);
	bool div(std::string arg1, std::string arg2, uint64_t lineNumber);
	bool mul(std::string arg1, std::string arg2, uint64_t lineNumber);
	bool print(std::string arg1);

	std::string doAdd(std::string arg1, std::string arg2);
	std::string doSub(std::string arg1, std::string arg2);
	std::string doDiv(std::string arg1, std::string arg2);
	std::string doMul(std::string arg1, std::string arg2);

	bool checkIfNumber(std::string txt);
	
};

