#include "stdafx.h"

#include "Executor.h"
#include "AssemblyInterpreter.h"

Executor::Executor(AssemblyInterpreter* holder)
{
	this->holder = holder;
}

Executor::~Executor()
{
}

void Executor::execute(std::vector<Command> commands)
{
	for(Command cmd : commands)
	{
		if (!this->doCommand(cmd))
		{
			break;
		}
	}
}

bool Executor::doCommand(Command cmd)
{
	if (cmd.getType() == "mov")
	{
		return this->mov(cmd.getArg1(), cmd.getArg2(), cmd.getLineNumber());
	}
	else if (cmd.getType() == "push")
	{
		return this->push(cmd.getArg1(), cmd.getLineNumber());
	}
	else if (cmd.getType() == "pop")
	{
		return this->pop(cmd.getArg1(), cmd.getLineNumber());
	}
	else if (cmd.getType() == "add")
	{
		return this->add(cmd.getArg1(), cmd.getArg2(), cmd.getLineNumber());
	}
	else if (cmd.getType() == "sub")
	{
		return this->sub(cmd.getArg1(), cmd.getArg2(), cmd.getLineNumber());
	}
	else if (cmd.getType() == "div")
	{
		return this->div(cmd.getArg1(), cmd.getArg2(), cmd.getLineNumber());
	}
	else if (cmd.getType() == "mul")
	{
		return this->mul(cmd.getArg1(), cmd.getArg2(), cmd.getLineNumber());
	}
	else if (cmd.getType() == "print")
	{
		return this->print(cmd.getArg1());
	}
	else
	{
		return true;
	}
}

bool Executor::mov(std::string arg1, std::string arg2, uint64_t lineNumber)
{
	if (arg1 == "ax")
	{
		if (arg2 == "bx")
		{
			this->ax = bx;
		}
		else if (arg2 == "cx")
		{
			this->ax = cx;
		}
		else if (arg2 != "ax")
		{
			this->ax = arg2;
		}
		return true;
	}
	else if (arg1 == "bx")
	{
		if (arg2 == "ax")
		{
			this->bx = ax;
		}
		else if (arg2 == "cx")
		{
			this->bx = cx;
		}
		else if (arg2 != "bx")
		{
			this->bx = arg2;
		}
		return true;
	}
	else if (arg1 == "cx")
	{
		if (arg2 == "ax")
		{
			this->cx = ax;
		}
		else if (arg2 == "bx")
		{
			this->cx = bx;
		}
		else if (arg2 != "cx")
		{
			this->cx = arg2;
		}
		return true;
	}
	else
	{
		this->holder->log("!!! ERROR: Executor Error: Wrong usage of 'mov' command in line " + std::to_string(lineNumber)
		+ " - Provide register 'ax', 'bx' or 'cx' as first argument.");
		this->holder->setError();
		return false;
	}	
}

bool Executor::push(std::string arg1, uint64_t lineNumber)
{
	if (arg1 == "ax")
	{
		this->stack.push_back(ax);
		return true;
	}
	else if (arg1 == "bx")
	{
		this->stack.push_back(bx);
		return true;
	}
	else if (arg1 == "cx")
	{
		this->stack.push_back(cx);
		return true;
	}
	else
	{
		this->stack.push_back(arg1);
		return true;
	}
}

bool Executor::pop(std::string arg1, uint64_t lineNumber)
{
	if (arg1 == "ax")
	{
		ax = this->stack.at(this->stack.size() - 1);
		this->stack.pop_back();
		return true;
	}
	else if (arg1 == "bx")
	{
		bx = this->stack.at(this->stack.size() - 1);
		this->stack.pop_back();
		return true;
	}
	else if (arg1 == "cx")
	{
		cx = this->stack.at(this->stack.size() - 1);
		this->stack.pop_back();
		return true;
	}
	else
	{
		this->holder->log("!!! ERROR: Executor Error: Wrong usage of 'pop' command in line " + std::to_string(lineNumber)
			+ " - Provide register 'ax', 'bx' or 'cx' as first argument.");
		this->holder->setError();
		return false;
	}
}

bool Executor::add(std::string arg1, std::string arg2, uint64_t lineNumber)
{
	if (arg1 == "ax")
	{
		if (arg2 == "ax")
		{
			this->ax = this->doAdd(ax, ax);
		}
		else if (arg2 == "bx")
		{
			this->ax = this->doAdd(ax, bx);
		}
		else if (arg2 == "cx")
		{
			this->ax = this->doAdd(ax, cx);
		}
		else
		{
			this->ax = this->doAdd(ax, arg2);
		}
		if (this->ax != "////./ERROR/.////")
		{
			return true;
		}
		else
		{
			this->holder->log("!!! ERROR: Executor Error: Wrong usage of 'add' command in line " + std::to_string(lineNumber)
				+ " - Addition not possible with the given datatypes of arguments.");
			this->holder->setError();
			return false;
		}
	}
	else if (arg1 == "bx")
	{
		if (arg2 == "ax")
		{
			this->bx = this->doAdd(bx, ax);
		}
		else if (arg2 == "bx")
		{
			this->bx = this->doAdd(bx, bx);
		}
		else if (arg2 == "cx")
		{
			this->bx = this->doAdd(bx, cx);
		}
		else
		{
			this->bx = this->doAdd(bx, arg2);
		}
		if (this->bx != "////./ERROR/.////")
		{
			return true;
		}
		else
		{
			this->holder->log("!!! ERROR: Executor Error: Wrong usage of 'add' command in line " + std::to_string(lineNumber)
				+ " - Addition not possible with the given datatypes of arguments.");
			this->holder->setError();
			return false;
		}
	}
	else if (arg1 == "cx")
	{
		if (arg2 == "ax")
		{
			this->cx = this->doAdd(cx, ax);
		}
		else if (arg2 == "bx")
		{
			this->cx = this->doAdd(cx, bx);
		}
		else if (arg2 == "cx")
		{
			this->cx = this->doAdd(cx, cx);
		}
		else
		{
			this->cx = this->doAdd(cx, arg2);
		}
		if (this->cx != "////./ERROR/.////")
		{
			return true;
		}
		else
		{
			this->holder->log("!!! ERROR: Executor Error: Wrong usage of 'add' command in line " + std::to_string(lineNumber)
				+ " - Addition not possible with the given datatypes of arguments.");
			this->holder->setError();
			return false;
		}
	}
	else
	{
		this->holder->log("!!! ERROR: Executor Error: Wrong usage of 'add' command in line " + std::to_string(lineNumber)
			+ " - Provide 'ax', 'bx' or 'cx' as first argument.");
		this->holder->setError();
		return false;
	}	
}

bool Executor::sub(std::string arg1, std::string arg2, uint64_t lineNumber)
{
	if (arg1 == "ax")
	{
		if (arg2 == "ax")
		{
			this->ax = this->doSub(ax, ax);
		}
		else if (arg2 == "bx")
		{
			this->ax = this->doSub(ax, bx);
		}
		else if (arg2 == "cx")
		{
			this->ax = this->doSub(ax, cx);
		}
		else
		{
			this->ax = this->doSub(ax, arg2);
		}
		if (this->ax != "////./ERROR/.////")
		{
			return true;
		}
		else
		{
			this->holder->log("!!! ERROR: Executor Error: Wrong usage of 'sub' command in line " + std::to_string(lineNumber)
				+ " - Subtraction not possible with the given datatypes of arguments.");
			this->holder->setError();
			return false;
		}
	}
	else if (arg1 == "bx")
	{
		if (arg2 == "ax")
		{
			this->bx = this->doSub(bx, ax);
		}
		else if (arg2 == "bx")
		{
			this->bx = this->doSub(bx, bx);
		}
		else if (arg2 == "cx")
		{
			this->bx = this->doSub(bx, cx);
		}
		else
		{
			this->bx = this->doSub(bx, arg2);
		}
		if (this->bx != "////./ERROR/.////")
		{
			return true;
		}
		else
		{
			this->holder->log("!!! ERROR: Executor Error: Wrong usage of 'sub' command in line " + std::to_string(lineNumber)
				+ " - Subtraction not possible with the given datatypes of arguments.");
			this->holder->setError();
			return false;
		}
	}
	else if (arg1 == "cx")
	{
		if (arg2 == "ax")
		{
			this->cx = this->doSub(cx, ax);
		}
		else if (arg2 == "bx")
		{
			this->cx = this->doSub(cx, bx);
		}
		else if (arg2 == "cx")
		{
			this->cx = this->doSub(cx, cx);
		}
		else
		{
			this->cx = this->doSub(cx, arg2);
		}
		if (this->cx != "////./ERROR/.////")
		{
			return true;
		}
		else
		{
			this->holder->log("!!! ERROR: Executor Error: Wrong usage of 'sub' command in line " + std::to_string(lineNumber)
				+ " - Subtraction not possible with the given datatypes of arguments.");
			this->holder->setError();
			return false;
		}
	}
	else
	{
		this->holder->log("!!! ERROR: Executor Error: Wrong usage of 'sub' command in line " + std::to_string(lineNumber)
			+ " - Provide 'ax', 'bx' or 'cx' as first argument.");
		this->holder->setError();
		return false;
	}
}

bool Executor::div(std::string arg1, std::string arg2, uint64_t lineNumber)
{
	if (arg1 == "ax")
	{
		if (arg2 == "ax")
		{
			this->ax = this->doDiv(ax, ax);
		}
		else if (arg2 == "bx")
		{
			this->ax = this->doDiv(ax, bx);
		}
		else if (arg2 == "cx")
		{
			this->ax = this->doDiv(ax, cx);
		}
		else
		{
			this->ax = this->doDiv(ax, arg2);
		}
		if (this->ax != "////./ERROR/.////" && this->ax != "////./0ERROR0/.////")
		{
			return true;
		}
		else
		{
			if (this->ax == "////./0ERROR0/.////")
			{
				this->holder->log("!!! ERROR: Executor Error: Wrong usage of 'div' command in line " + std::to_string(lineNumber)
					+ " - Division through zero not possible.");
			}
			else
			{
				this->holder->log("!!! ERROR: Executor Error: Wrong usage of 'div' command in line " + std::to_string(lineNumber)
					+ " - Division not possible with the given datatypes of arguments.");				
			}
			this->holder->setError();
			return false;
		}
	}
	else if (arg1 == "bx")
	{
		if (arg2 == "ax")
		{
			this->bx = this->doDiv(bx, ax);
		}
		else if (arg2 == "bx")
		{
			this->bx = this->doDiv(bx, bx);
		}
		else if (arg2 == "cx")
		{
			this->bx = this->doDiv(bx, cx);
		}
		else
		{
			this->bx = this->doDiv(bx, arg2);
		}
		if (this->bx != "////./ERROR/.////" && this->bx != "////./0ERROR0/.////")
		{
			return true;
		}
		else
		{
			if (this->bx == "////./0ERROR0/.////")
			{
				this->holder->log("!!! ERROR: Executor Error: Wrong usage of 'div' command in line " + std::to_string(lineNumber)
					+ " - Division through zero not possible.");
			}
			else
			{
				this->holder->log("!!! ERROR: Executor Error: Wrong usage of 'div' command in line " + std::to_string(lineNumber)
					+ " - Division not possible with the given datatypes of arguments.");
			}
			this->holder->setError();
			return false;
		}
	}
	else if (arg1 == "cx")
	{
		if (arg2 == "ax")
		{
			this->cx = this->doDiv(cx, ax);
		}
		else if (arg2 == "bx")
		{
			this->cx = this->doDiv(cx, bx);
		}
		else if (arg2 == "cx")
		{
			this->cx = this->doDiv(cx, cx);
		}
		else
		{
			this->cx = this->doDiv(cx, arg2);
		}
		if (this->cx != "////./ERROR/.////" && this->cx != "////./0ERROR0/.////")
		{
			return true;
		}
		else
		{
			if (this->cx == "////./0ERROR0/.////")
			{
				this->holder->log("!!! ERROR: Executor Error: Wrong usage of 'div' command in line " + std::to_string(lineNumber)
					+ " - Division through zero not possible.");
			}
			else
			{
				this->holder->log("!!! ERROR: Executor Error: Wrong usage of 'div' command in line " + std::to_string(lineNumber)
					+ " - Division not possible with the given datatypes of arguments.");
			}
			this->holder->setError();
			return false;
		}
	}
	else
	{
		this->holder->log("!!! ERROR: Executor Error: Wrong usage of 'div' command in line " + std::to_string(lineNumber)
			+ " - Provide 'ax', 'bx' or 'cx' as first argument.");
		this->holder->setError();
		return false;
	}
}

bool Executor::mul(std::string arg1, std::string arg2, uint64_t lineNumber)
{
	if (arg1 == "ax")
	{
		if (arg2 == "ax")
		{
			this->ax = this->doMul(ax, ax);
		}
		else if (arg2 == "bx")
		{
			this->ax = this->doMul(ax, bx);
		}
		else if (arg2 == "cx")
		{
			this->ax = this->doMul(ax, cx);
		}
		else
		{
			this->ax = this->doMul(ax, arg2);
		}
		if (this->ax != "////./ERROR/.////")
		{
			return true;
		}
		else
		{
			this->holder->log("!!! ERROR: Executor Error: Wrong usage of 'mul' command in line " + std::to_string(lineNumber)
				+ " - Multiplication not possible with the given datatypes of arguments.");
			this->holder->setError();
			return false;
		}
	}
	else if (arg1 == "bx")
	{
		if (arg2 == "ax")
		{
			this->bx = this->doMul(bx, ax);
		}
		else if (arg2 == "bx")
		{
			this->bx = this->doMul(bx, bx);
		}
		else if (arg2 == "cx")
		{
			this->bx = this->doMul(bx, cx);
		}
		else
		{
			this->bx = this->doMul(bx, arg2);
		}
		if (this->bx != "////./ERROR/.////")
		{
			return true;
		}
		else
		{
			this->holder->log("!!! ERROR: Executor Error: Wrong usage of 'mul' command in line " + std::to_string(lineNumber)
				+ " - Multiplication not possible with the given datatypes of arguments.");
			this->holder->setError();
			return false;
		}
	}
	else if (arg1 == "cx")
	{
		if (arg2 == "ax")
		{
			this->cx = this->doMul(cx, ax);
		}
		else if (arg2 == "bx")
		{
			this->cx = this->doMul(cx, bx);
		}
		else if (arg2 == "cx")
		{
			this->cx = this->doMul(cx, cx);
		}
		else
		{
			this->cx = this->doMul(cx, arg2);
		}
		if (this->cx != "////./ERROR/.////")
		{
			return true;
		}
		else
		{
			this->holder->log("!!! ERROR: Executor Error: Wrong usage of 'mul' command in line " + std::to_string(lineNumber)
				+ " - Multiplication not possible with the given datatypes of arguments.");
			this->holder->setError();
			return false;
		}
	}
	else
	{
		this->holder->log("!!! ERROR: Executor Error: Wrong usage of 'mul' command in line " + std::to_string(lineNumber)
			+ " - Provide 'ax', 'bx' or 'cx' as first argument.");
		this->holder->setError();
		return false;
	}
}

bool Executor::print(std::string arg1)
{
	if (arg1 == "ax")
	{
		this->holder->log(this->ax);
		return true;
	}
	else if (arg1 == "bx")
	{
		this->holder->log(this->bx);
		return true;
	}
	else if (arg1 == "cx")
	{
		this->holder->log(this->cx);
		return true;
	}
	else
	{
		this->holder->log(arg1);
		return true;
	}
}

std::string Executor::doAdd(std::string arg1, std::string arg2)
{
	if (arg1[0] == '"' && arg2[0] == '"' && arg1[arg1.size()] == '"' && arg2[arg2.size()] == '"')
	{
		return (arg1 + arg2);
	}
	else if(this->checkIfNumber(arg1) && this->checkIfNumber(arg2))
	{
		if (arg1.find(".") != std::string::npos || arg2.find(".") != std::string::npos)
		{
			return std::to_string((std::stof(arg1) + std::stof(arg2)));
		}
		else
		{
			return std::to_string((std::stoi(arg1) + std::stoi(arg2)));
		}
	}
	else
	{
		return "////./ERROR/.////";
	}
}

std::string Executor::doSub(std::string arg1, std::string arg2)
{
	if (this->checkIfNumber(arg1) && this->checkIfNumber(arg2))
	{
		if (arg1.find(".") != std::string::npos || arg2.find(".") != std::string::npos)
		{
			return std::to_string((std::stof(arg1) - std::stof(arg2)));
		}
		else
		{
			return std::to_string((std::stoi(arg1) - std::stoi(arg2)));
		}
	}
	else
	{
		return "////./ERROR/.////";
	}
}

std::string Executor::doDiv(std::string arg1, std::string arg2)
{
	if (this->checkIfNumber(arg1) && this->checkIfNumber(arg2) && (arg2 != "0"))
	{
		if (arg1.find(".") != std::string::npos || arg2.find(".") != std::string::npos)
		{
			return std::to_string((std::stof(arg1) / std::stof(arg2)));
		}
		else
		{
			return std::to_string((std::stoi(arg1) / std::stoi(arg2)));
		}
	}
	else
	{
		if (arg2 == "0")
		{
			return "////./0ERROR0/.////";
		}
		else
		{
			return "////./ERROR/.////";
		}
	}
}

std::string Executor::doMul(std::string arg1, std::string arg2)
{
	if (this->checkIfNumber(arg1) && this->checkIfNumber(arg2))
	{
		if (arg1.find(".") != std::string::npos || arg2.find(".") != std::string::npos)
		{
			return std::to_string((std::stof(arg1) * std::stof(arg2)));
		}
		else
		{
			return std::to_string((std::stoi(arg1) * std::stoi(arg2)));
		}
	}
	else
	{
		return "////./ERROR/.////";
	}
}

bool Executor::checkIfNumber(std::string txt)
{
	uint16_t charCounter = 0;
	bool emode = false;
	for (char c : txt)
	{
		if (charCounter == 0)
		{
			if (!isdigit(c) && c != '-' && c != '.')
			{
				return false;
			}
		}
		else
		{
			if (!emode && c == 'e')
			{
				emode = true;
			}
			else if ((!(emode && (c == '+' || c == '-'))) && (!isdigit(c)))
			{
				return false;
			}
		}
		charCounter++;
	}
	return true;
}


