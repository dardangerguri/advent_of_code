#include <iostream>
# include <fstream>

int main() {
	std::ifstream input;
	std::string line;

	int position = 50;
	int zeroCount = 0;
	char direction;
	int distance;
	int loops = 0;
	int remainder = 0;

	input.open("./input.txt");
	if (!input) {
		std::cerr << "Failed to open file.\n";
		return (1);
	}

	while (std::getline(input, line)) {
		direction = line[0];
		distance = std::stoi(line.substr(1));
		loops = distance / 100;
		remainder = distance % 100;

		if (direction == 'R') {
			zeroCount += loops;
			if (position + remainder >= 100)
				zeroCount++;
			position = (position + distance) % 100;
		}
		else {
			zeroCount += loops;
			if (position > 0 && remainder >= position)
				zeroCount++;
			position = (position - (distance % 100) + 100) % 100;
		}
	}

	std::cout << "The password is " << zeroCount << std::endl;

	input.close();
	return (0);
}
