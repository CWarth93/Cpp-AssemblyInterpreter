#pragma once

#include "Command.h"

class AssemblyInterpreter;

class Parser
{

public:

	Parser(AssemblyInterpreter* holder);
	~Parser();
	std::vector<Command> parse(std::string fileContent);

private:

	AssemblyInterpreter* holder;

	std::vector<std::vector<std::string>> splitIntoLinesWithWords(std::string fileContent);
	bool syntaxCheck(std::vector<std::vector<std::string>> lines);
	std::vector<Command> createCommands(std::vector<std::vector<std::string>> lines);

	bool checkIfLineIsEmpty(std::vector<std::string> line);
	bool checkIfLineHasCorrectAmountOfWords(std::vector<std::string> line);
	bool checkIfExpressionIsSplitter(std::string expression);
	bool checkIfExpressionIsSpace(std::string expression);
	bool checkIfExpressionIsComma(std::string expression);
	bool checkIfLineHasOnlyOneArgument(std::vector<std::string> line);

	bool checkIfCommandIsCorrect(Command* command);


};

