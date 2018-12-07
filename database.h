#ifndef Database_H
#define Database_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <exception>
#include <iomanip>

#include "dataSystem.h"

std::string formatSubstr(const std::string &str, int start, int len);

class DataType
{
public:
	static const int ISBNLen = 20;
	static const int StringLen = 40;
	static const int DataTypeLen = ISBNLen + StringLen * 3 + sizeof(int) + sizeof(double);

public:
	std::string ISBN; //aligned to 20 characters
	std::string name, author, keyword; //aligned to 40 characters(20 chinese characters)
	double price; //current price
	int quantity;

public:
	DataType() = default;
	DataType(std::string str);
	DataType(std::string _ISBN, std::string _name, std::string _author,
		std::string _keyword, double _price, int _quantity);

public:
	std::string printToString();
};

class Database
{
public:
	static const int BlockSize = 1;
	static const int BlockLen = sizeof(int) * 2 + BlockSize * DataType::DataTypeLen;

private:
	std::fstream dataIO;
	int offset, readLen; //offset used when reading a DataType
	int startAddress;

public:
	Database(const std::string &file, int _offset, int len);
	~Database();

private:
	std::string readBlock(int offset, int len = BlockLen);
	std::string readWholeBlock(int address);
	void writeWholeBlock(int address, const std::string &str);
	bool inCurBlock(std::string key, std::string uniqueKey, int curSize);

	std::vector<DataType> readInsideBlock(std::string key, int address, int size, std::string uniqueKey = "");
	void eraseInsideBlock(std::string &key, int address, int size, std::string uniqueKey);
	void writeInsideBlock(std::string &key, int address, int size, std::string uniqueKey, std::string value = "");
	int split(int start, int beginEle, int size);
	int createNewBlock(int size = 0, int next = -1); //create a new block without filling the elements
	void cleanup();

public:
	DataType read(std::string key, std::string uniqueKey);
	std::vector<DataType> readAll(std::string key);
	void write(std::string key, DataType &data, std::string uniqueKey);
	void erase(std::string key, std::string uniqueKey);
};

#endif Database_H