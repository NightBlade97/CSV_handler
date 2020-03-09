#pragma once
#include <iostream>
#include <map>
#include "CSV_Reader.h"

class CSVHandler{ //Class to process data from CSV

private:
	std::vector<std::vector<std::string>> CSV_Data;//Matrix, where CSV Data is stored
	std::map<std::string,long> Column_names;//Map, where information about column names stored
	std::map<std::string,long> Row_names;//Map, where information about row names stored
	std::vector<std::vector<bool>> Is_formula;//Matrix where information is stored, whether this cell stores a formula or a numerical value 

	long width;
	long height;

	long getColumnNumber(std::string);//Function to get number of column from string, containing the formula 
	long getRowNumber(std::string);//Function to get number of row from string, containing the formula

	void calculateFormula(long,long,long);//Function to calculate formula

public:
	void readDataFromCSVFile(std::string);//function to read data from CSV File
	void processData();//Function to process all data
	void writeProcessedData();//Function to write processed data to console
};