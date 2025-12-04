#include <iostream>
# include <fstream>
# include <string>

int main() {
	std::ifstream input;
	std::string line;

	long long totalJoltage = 0;
	std::string selectedDigits;
	size_t pos = 0;
	char c;

	input.open("./input.txt");
	if (!input) {
		std::cerr << "Failed to open file.\n";
		return (1);
	}

	while (std::getline(input, line)) {
		selectedDigits.clear();

		for (pos = 0; pos < line.size(); pos++) {
			c = line[pos];

			while (!selectedDigits.empty() && selectedDigits.back() < c && selectedDigits.size() + (line.size() - pos - 1) >= 12)
				selectedDigits.pop_back();
			if (selectedDigits.size() < 12)
				selectedDigits.push_back(c);
		}
		totalJoltage += std::stoll(selectedDigits);
	}

	std::cout << "The total output joltage is " << totalJoltage << std::endl;

	input.close();
	return (0);
}
