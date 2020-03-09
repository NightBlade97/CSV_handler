#include "CSV_Reader.h"
#include <iostream>


std::vector<std::vector<std::string> > CSVReader::getData() {
		 
	std::vector<std::vector<std::string>> Data;
	Data.clear();

	std::ifstream fin(fileName);

	if (!fin.is_open()) {
		std::cout << "Can't open this CSV file!"<<std::endl;
		exit(0);
	}

	std::string line;
	
	while (std::getline(fin, line)){//First read the whole line
		if (line != "") {
			std::stringstream ss(line);//Thansform it in stringstream
			std::vector<std::string> data_line;
			data_line.clear();
			std::string csv_data;

			while (std::getline(ss, csv_data, delimeter)) {//Then read infromatino about all cells
				data_line.push_back(csv_data);
				
			}
			Data.push_back(data_line);
		}
		
		
	}

	fin.close();

	return Data;
}