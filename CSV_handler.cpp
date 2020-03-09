#include "CSV_handler.h"

//#include "CSV_Reader.h"


void CSVHandler::readDataFromCSVFile(std::string filename) {

	CSVReader reader(filename);//Initialize Class reader from CSV

	CSV_Data = reader.getData();
}

void CSVHandler::writeProcessedData() {//Just simple output to console
	for (long i = 0; i < height; ++i) {
		for (long j = 0; j < CSV_Data[i].size(); ++j) {
			std::cout << CSV_Data[i][j];
			if (j != width - 1) {
				std::cout << ",";
			}
		}
		std::cout << std::endl;
	}
}

void CSVHandler::processData() {
	height = CSV_Data.size();//Calculate heiht and width of CSV Table
	if (height > 0) {
		width = CSV_Data[0].size();
	}

	for (long i = 1; i < width; ++i) {//Getting infomation about Column names 
		Column_names.insert(std::pair<std::string, int>(CSV_Data[0][i],i));
	}

	for (long i = 1; i < height; ++i) {//Getting infomation about Row names
		Row_names.insert(std::pair<std::string, int>(CSV_Data[i][0], i));
	}
	for (long i = 0; i < height; ++i) {//Getting information in which cells are formulas
		std::vector <bool> is_formula_row;
		for (int j = 0; j < CSV_Data[i].size(); ++j) {
			if (CSV_Data[i][j][0] == '=') {
				is_formula_row.push_back(true);
			}
			else {
				is_formula_row.push_back(false);
			}
		}
		Is_formula.push_back(is_formula_row);
	}
	
	for (long i = 1; i < height; ++i) {//Calculate all the formulas
		for (long j = 1; j < CSV_Data[i].size(); ++j) {
			if (Is_formula[i][j]) {
				calculateFormula(i, j, 0);
			}
		}
	}
}

void CSVHandler::calculateFormula(long _i, long _j, long depth) {
	depth++;
	if (depth >= ((height - 1)*(width - 1 ))) {//This is to prevent loop link
		std::cout << "There is loop link in this CSV file!" << std::endl;
		exit(0);
	}

	long result = 0;
	
	std::string formula = CSV_Data[_i][_j];
	
	std::string left_operand;//Left operand of formula
	std::string right_operand;//Right operand of formula
	char operation;//Orepation

	int pos = formula.find('+');
	if (pos == -1) {
		pos = formula.find('-');
		if (pos == -1) {
			pos = formula.find('*');
			if (pos == -1) {
				pos = formula.find('/');
			}
		}
	}
	formula.erase(0, 1);
	left_operand = formula.substr(0,pos-1);
	operation = formula[pos-1];
	formula.erase(0,pos);
	right_operand = formula;
	

	long leftColumn = getColumnNumber(left_operand);
	long leftRow = getRowNumber(left_operand);

	long rightColumn = getColumnNumber(right_operand);
	long rightRow = getRowNumber(right_operand);

	if (leftColumn == -1 || leftRow == -1 || rightColumn == -1 || rightRow == -1) {//This is to prevent calculating formulas, that are wrong
		std::cout << "There is something wrong with formulas in this CSV file!" << std::endl;
		exit(0);
	}

	if (Is_formula[leftRow][leftColumn]) {//First left operand of formula is calculated 
		calculateFormula(leftRow, leftColumn,depth);
	}
	if (Is_formula[rightRow][rightColumn]) {//Then right operand of formula is calculated 
		calculateFormula(rightRow, rightColumn, depth);
	}

	switch (operation) {//Then the whole formula is calculated
	case '+':
		result = std::stoi(CSV_Data[leftRow][leftColumn]) + std::stoi(CSV_Data[rightRow][rightColumn]);
		break;
	case '-':
		result = std::stoi(CSV_Data[leftRow][leftColumn]) - std::stoi(CSV_Data[rightRow][rightColumn]);
		break;
	case '*':
		result = std::stoi(CSV_Data[leftRow][leftColumn]) * std::stoi(CSV_Data[rightRow][rightColumn]);
		break;
	case '/':
		result = std::stoi(CSV_Data[leftRow][leftColumn]) / std::stoi(CSV_Data[rightRow][rightColumn]);
		break;
	}
	
	Is_formula[_i][_j] = false;//Now there is a number in this cell
	CSV_Data[_i][_j] = std::to_string(result);

	
}


long CSVHandler::getColumnNumber(std::string _formula) {
	std::string columnid="";
	long pos = 0;
	while (!(_formula[pos] >= '0' && _formula[pos] <= '9')) {
		++pos;
	}

	columnid = _formula.substr(0,pos);//Find column information in formula
	std::map<std::string, long>::iterator it;

	it = Column_names.find(columnid);
	if (it != Column_names.end()) {
		return it->second;
	}

	return -1;
}

long CSVHandler::getRowNumber(std::string _formula) {
	std::string rowid = "";
	long pos = _formula.size()-1;
	while ((_formula[pos] >= '0' && _formula[pos] <= '9')) {
		--pos;
	}

	rowid = _formula.substr(pos+1, _formula.size()-pos-1);//Find row information in formula
	std::map<std::string, long>::iterator it;

	it = Row_names.find(rowid);
	if (it != Row_names.end()) {
		return it->second;
	}

	return -1;

}