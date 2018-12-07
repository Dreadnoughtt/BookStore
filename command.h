#ifndef Command_H
#define Command_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

#include "dataSystem.h"
#include "account.h"
#include "database.h"
#include "finance.h"

enum ResultType { Executed, Exit };

class CommandSystem
{
public:
	static const int maxCommandLen = 200;

private:
	std::fstream dataIO;
	std::vector<DataType> curSelected;

private:
	AccountSystem *Account;
	FinanceSystem *Finance;
	Database *ISBNDatabase;
	Database *nameDatabase;
	Database *authorDatabase;
	Database *keywordDatabase;

public:
	CommandSystem(const std::string &file);
	~CommandSystem();

private:
	std::vector<std::string> parse(std::string str);
	void erase(DataType data);
	void modify(DataType old, DataType data);

private:
	ResultType userCommand(std::vector<std::string> token);
	ResultType dataCommand(std::vector<std::string> token);
	void printSelected();

public:
	ResultType runCommand(const std::string &str);
	ResultType runLoadCommand(const std::string &file);
};

#endif Command_H