#include <iostream>
# include <fstream>
# include <sstream>

int main() {
	std::ifstream input;
	std::string line;

	std::vector<std::string> lines;
	std::string operators;
	size_t maxLength = 0;

	std::string number;
	char op;
	bool problemFlag = false;
	long long nmbr = 0;
	long long result = 0;
	long long total = 0;

	input.open("./input.txt");
	if (!input) {
		std::cerr << "Failed to open file.\n";
		return (1);
	}

	while (std::getline(input, line)) {
		lines.push_back(line);

		if (line.length() > maxLength)
			maxLength = line.length();
	}

	operators = lines.back();
	lines.pop_back();

	for (int col = 0; col <= maxLength - 1; col++) {
		if (operators[col] != std::string::npos && (operators[col] == '+' || operators[col] == '*'))
			op = operators[col];
		number.clear();

		for (size_t row = 0; row < lines.size(); row++) {
			if (col < lines[row].size() && isdigit(lines[row][col]))
				number += lines[row][col];
		}
		if (!number.empty()) {
			nmbr = std::stoll(number);
			if (!problemFlag) {
				result = nmbr;
				problemFlag = true;
			} else {
				if (op == '+')
					result += nmbr;
				else
					result *= nmbr;
			}
		} else {
			if (problemFlag) {
				total += result;
				result = 0;
				problemFlag = false;
			}
		}
	}
	if (problemFlag)
		total += result;

	std::cout << "The grand total is " << total << std::endl;

	input.close();
	return (0);
}
