#include <iostream>
# include <fstream>

bool isInvalid(long long number) {
	std::string nmbr = std::to_string(number);
	size_t length = nmbr.size();
	size_t half = 0;
	std::string first;
	std::string second;

	if (length % 2 != 0)
		return (0);

	half = length / 2;
	first = nmbr.substr(0, half);
	second = nmbr.substr(half);

	return (first == second);
}

int main() {
	std::ifstream input;
	std::string range;


	int dashPosition = 0;
	long long start = 0;
	long long end = 0;
	long long sumInvalid = 0;

	input.open("./input.txt");
	if (!input) {
		std::cerr << "Failed to open file.\n";
		return (1);
	}

	while (std::getline(input, range, ',')) {
		dashPosition = range.find('-');
		start = std::stoll(range.substr(0, dashPosition));
		end = std::stoll(range.substr(dashPosition + 1));

		for (long long number = start; number <= end; number++) {
			if (isInvalid(number)) {
				sumInvalid += number;
			}
		}
	}

	std::cout << "The sum of invalid ids is " << sumInvalid << std::endl;

	input.close();
	return (0);
}
