#include <iostream>
# include <fstream>
# include <sstream>

int main() {
	std::ifstream input;
	std::string line;

	std::vector<std::vector<int>> numbersGrid;
	std::vector<char> operators;
	int number;

	size_t firstChar = 0;
	size_t rows;
	size_t columns;
	char op;
	long long result = 0;

	long long total = 0;

	input.open("./input.txt");
	if (!input) {
		std::cerr << "Failed to open file.\n";
		return (1);
	}

	while (std::getline(input, line)) {
		firstChar = line.find_first_not_of(' ');
		if (firstChar != std::string::npos && std::isdigit(line[firstChar])) {
			std::vector<int> row;
			std::stringstream ss(line);
			number = 0;
			while (ss >> number) {
				row.push_back(number);
			}
			numbersGrid.push_back(row);
		} else {
			for (char c : line) {
				if (c == '+' || c == '*')
					operators.push_back(c);
			}
		}
	}

	rows = numbersGrid.size();
	columns = numbersGrid[0].size();

	for (size_t col = 0; col < columns; ++col) {
		result = numbersGrid[0][col];
		op = operators[col];
		for (size_t row = 1; row < rows; ++row) {
			if (op == '+')
				result += numbersGrid[row][col];
			else
				result *= numbersGrid[row][col];
		}
		total += result;
	}

	std::cout << "The grand total of all the answers is " << total << std::endl;


	input.close();
	return (0);
}
