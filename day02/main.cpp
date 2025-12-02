#include <iostream>
# include <fstream>

bool isInvalid(long long number) {
	std::string nmbr = std::to_string(number);
	size_t length = nmbr.size();
	bool pattern = true;

	for (size_t len = 1; len <= length / 2; len++) {

		std::string part = nmbr.substr(0, len);
		pattern = true;

		for (size_t i = len; i < length; i += len) {
			if (nmbr.substr(i, len) != part) {
				pattern = false;
				break;
			}
		}

		if (pattern)
			return (1);
	}
	return (0);
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
