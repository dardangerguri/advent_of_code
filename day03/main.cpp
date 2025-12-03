#include <iostream>
# include <fstream>

int main() {
	std::ifstream input;
	std::string line;

	int totalJoltage = 0;
	size_t position;
	size_t secondPos;
	int joltage;

	input.open("./input.txt");
	if (!input) {
		std::cerr << "Failed to open file.\n";
		return (1);
	}

	while (std::getline(input, line)) {

		joltage = 0;
		for (char first = '9'; first >= '0'; first--) {
			position = line.find(first);
			if (position == std::string::npos || position + 1 >= line.size())
				continue;
			joltage = (first - '0') * 10;

			for (char second = '9'; second >= '0'; second--) {
				secondPos = line.find(second, position + 1);
				if (secondPos == std::string::npos)
					continue;
				joltage += (second - '0');
				break;
			}
			break;
		}
		totalJoltage += joltage;
	}

	std::cout << "The total output joltage is " << totalJoltage << std::endl;

	input.close();
	return (0);
}
