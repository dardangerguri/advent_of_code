#include <iostream>
# include <fstream>

int main() {
	std::ifstream input;
	std::string line;

	int position = 50;
	int zeroCount = 0;
	char direction;
	int distance;

	input.open("./input.txt");
	if (!input) {
		std::cerr << "Failed to open file.\n";
		return (1);
	}

	while (std::getline(input, line)) {
		direction = line[0];
		distance = std::stoi(line.substr(1));

		if (direction == 'R')
			position += distance;
		else
			position -= distance;

		position = (position + 100) % 100;

		if (position == 0)
			zeroCount++;

	}

	std::cout << "The password is " << zeroCount << std::endl;

	input.close();
	return (0);
}
