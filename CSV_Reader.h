
#include <fstream>
#include <sstream>
#include <vector>
#include <string>


class CSVReader //A class to read data from CSV
{
	std::string fileName;
	char delimeter;
public:
	CSVReader(std::string filename, char delm = ',') :
		fileName(filename), delimeter(delm)
	{ }

	//Function to actually get data from CSV file
	std::vector<std::vector<std::string> > getData();
};