#pragma once

#include <string>
#include <vector>

class Command 
{

public:

	Command(std::vector<std::string> line, uint64_t lineNumber);
	~Command();

	uint64_t getLineNumber();
	std::string getType();
	std::string getArg1();
	std::string getArg2();

	bool hasOneArgument();
	bool hasTwoArguments();

private:

	uint64_t lineNumber;
	std::string type;
	std::string arg1;
	std::string arg2;

	void setType(std::vector<std::string> line);
	void setFirstArgument(std::vector<std::string> line);
	void setSecondArgument(std::vector<std::string> line);


};

