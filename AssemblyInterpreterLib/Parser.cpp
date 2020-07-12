#include "stdafx.h"
#include <string>
#include <vector>

#include "Parser.h"
#include "AssemblyInterpreter.h"


Parser::Parser(AssemblyInterpreter* holder)
{
	this->holder = holder;
}

Parser::~Parser()
{
}

std::vector<Command> Parser::parse(std::string fileContent)
{	
	std::vector<std::vector<std::string>> lines = this->splitIntoLinesWithWords(fileContent);	
	if (this->syntaxCheck(lines))
	{
		return  this->createCommands(lines);		
	}	
	else
	{ 
		return std::vector<Command>();
	}
}

std::vector<std::vector<std::string>> Parser::splitIntoLinesWithWords(std::string fileContent)
{
	std::vector<std::vector<std::string>> allLines;
	std::vector<std::string> oneLine;
	std::string currentWord;
	bool stringMode = false;
	for (char& character : fileContent)
	{
		if (character == '\n')										 
		{
			if (currentWord.size() != 0)
			{
				oneLine.push_back(currentWord);
			}
			currentWord = "";
			allLines.push_back(oneLine);
			oneLine.clear();
		}
		else if (character == '"')
		{
			stringMode = !stringMode;
			currentWord += character;
		}
		else
		{
			if ((character == ' ' || character == ',') && !stringMode)					
			{
				if (currentWord.size() != 0)
				{
					oneLine.push_back(currentWord);
				}
				currentWord = character;
				if (currentWord.size() != 0)
				{
					oneLine.push_back(currentWord);
				}
				currentWord = "";
			}
			else														
			{
				currentWord += character;
			}
		}
	}
	allLines.push_back(oneLine);
	return allLines;
}

bool Parser::syntaxCheck(std::vector<std::vector<std::string>> lines)
{
	uint64_t lineCounter = 0;
	uint64_t syntaxError = -1;
	std::string errorMsg;
	for (std::vector<std::string> line : lines)
	{
		lineCounter++;
		if (!this->checkIfLineIsEmpty(line))
		{
			if (this->checkIfLineHasCorrectAmountOfWords(line))
			{
				if (!this->checkIfExpressionIsSplitter(line.at(0)))
				{
					if (this->checkIfExpressionIsSpace(line.at(1)))
					{
						if (!this->checkIfExpressionIsSplitter(line.at(2)))
						{
							if (!this->checkIfLineHasOnlyOneArgument(line))
							{
								if (this->checkIfExpressionIsComma(line.at(3)))
								{
									if (this->checkIfExpressionIsSpace(line.at(4)))
									{
										if (this->checkIfExpressionIsSplitter(line.at(5)))										
										{
											syntaxError = lineCounter;
											errorMsg = "There is no second argument after argument splitter. Use a second argument.";
											break;
										}
									}
									else
									{
										syntaxError = lineCounter;
										errorMsg = "There is no ' ' after the argument separator. Use ' ' after ','.";
										break;
									}
								}
								else
								{
									syntaxError = lineCounter;
									errorMsg = "There is ' ' after the first argument. Use ','.";
									break;
								}
							}
							else
							{
								break;
							}
						}
						else
						{
							syntaxError = lineCounter;
							errorMsg = "The second expression is either ' ' or ','. Use an argument.";
							break;
						}
					}
					else
					{
						syntaxError = lineCounter;
						errorMsg = "There is ',' after the first expression. Use ' '.";
						break;
					}
				}
				else
				{
					syntaxError = lineCounter;
					errorMsg = "The first expression is either ' ' or ','. Use a command.";
					break;
				}
			}
			else
			{
				syntaxError = lineCounter;
				errorMsg = "The line has either too much or too less expressions. Use two or three expressions.";
				break;
			}
		}
	}
	if (syntaxError != -1)
	{
		this->holder->log("!!! ERROR: Parser Error: Wrong syntax in line " + std::to_string(lineCounter)
			+ " - " + errorMsg);
		this->holder->setError();
		return false;
	}
	else
	{
		return true;
	}
}

std::vector<Command> Parser::createCommands(std::vector<std::vector<std::string>> lines)
{
	std::vector<Command> commands;
	uint64_t lineCounter = 0;
	for (std::vector<std::string> line : lines)
	{
		lineCounter++;
		Command newCommand(line, lineCounter);
		if (this->checkIfCommandIsCorrect(&newCommand))
		{
			commands.push_back(newCommand);
		}
		else
		{			
			commands.clear();
			return commands;
		}
	}
	return commands;
}

bool Parser::checkIfLineIsEmpty(std::vector<std::string> line)
{
	if (line.size() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Parser::checkIfLineHasCorrectAmountOfWords(std::vector<std::string> line)
{
	if (line.size() == 3 || line.size() == 6)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Parser::checkIfExpressionIsSplitter(std::string expression)
{
	if (this->checkIfExpressionIsSpace(expression) || this->checkIfExpressionIsComma(expression))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Parser::checkIfExpressionIsSpace(std::string expression)
{
	if (expression == " ")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Parser::checkIfExpressionIsComma(std::string expression)
{
	if (expression == ",")
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool Parser::checkIfLineHasOnlyOneArgument(std::vector<std::string> line)
{
	if (line.size() == 3)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Parser::checkIfCommandIsCorrect(Command* command)
{
	if(command->getType() == "mov") 
	{
		if (command->hasTwoArguments())
		{
			return true;
		}
		else
		{
			this->holder->log("!!! ERROR: Parser Error: Wrong usage of command 'mov' in line " + std::to_string(command->getLineNumber())
				+ " - Provide two arguments.");
			this->holder->setError();
			return false;
		}
	}
	else if(command->getType() == "push")
	{
		if (command->hasOneArgument() && !command->hasTwoArguments())
		{
			return true;
		}
		else
		{
			this->holder->log("!!! ERROR: Parser Error: Wrong usage of command 'push' in line " + std::to_string(command->getLineNumber())
				+ " - Provide one argument.");
			this->holder->setError();
			return false;
		}
	}
	else if (command->getType() == "pop")
	{
		if (command->hasOneArgument() && !command->hasTwoArguments())
		{
			return true;
		}
		else
		{
			this->holder->log("!!! ERROR: Parser Error: Wrong usage of command 'pop' in line " + std::to_string(command->getLineNumber())
				+ " - Provide one argument.");
			this->holder->setError();
			return false;
		}
	}
	else if (command->getType() == "add")
	{
		if (command->hasTwoArguments())
		{
			return true;
		}
		else
		{
			this->holder->log("!!! ERROR: Parser Error: Wrong usage of command 'add' in line " + std::to_string(command->getLineNumber())
				+ " - Provide two arguments.");
			this->holder->setError();
			return false;
		}
	}
	else if (command->getType() == "sub")
	{
		if (command->hasTwoArguments())
		{
			return true;
		}
		else
		{
			this->holder->log("!!! ERROR: Parser Error: Wrong usage of command 'sub' in line " + std::to_string(command->getLineNumber())
				+ " - Provide two arguments.");
			this->holder->setError();
			return false;
		}
	}
	else if (command->getType() == "div")
	{
		if (command->hasTwoArguments())
		{
			return true;
		}
		else
		{
			this->holder->log("!!! ERROR: Parser Error: Wrong usage of command 'div' in line " + std::to_string(command->getLineNumber())
				+ " - Provide two arguments.");
			this->holder->setError();
			return false;
		}
	}
	else if (command->getType() == "mul")
	{
		if (command->hasTwoArguments())
		{
			return true;
		}
		else
		{
			this->holder->log("!!! ERROR: Parser Error: Wrong usage of command 'mul' in line " + std::to_string(command->getLineNumber())
				+ " - Provide two arguments.");
			this->holder->setError();
			return false;
		}
	}
	else if (command->getType() == "print")
	{
		if (command->hasOneArgument() && !command->hasTwoArguments())
		{
			return true;
		}
		else
		{
			this->holder->log("!!! ERROR: Parser Error: Wrong usage of command 'print' in line " + std::to_string(command->getLineNumber())
				+ " - Provide one argument.");
			this->holder->setError();
			return false;
		}
	}
	else if (command->getType() == "")
	{
		return true;
	}
	else
	{
		this->holder->log("!!! ERROR: Parser Error: Unknown command in line " + std::to_string(command->getLineNumber())
			+ " - Command doesnt belong to assembler subset.");
		this->holder->setError();
		return false;
	}
}