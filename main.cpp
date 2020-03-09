#include <iostream>
#include <fstream>
#include "CSV_handler.h"



int main(int argc, char* argv[]){
	std::string filename;
	if (argc > 1) {
		filename=argv[1];
	}
	else {
		filename="input.csv";
	}
    
	CSVHandler handler;
	handler.readDataFromCSVFile(filename);
	handler.processData();
	handler.writeProcessedData();

	return 0;
}