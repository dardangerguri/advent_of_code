#include <iostream>
# include <fstream>

int main() {
	std::ifstream input;
	std::string line;
	std::vector<std::string> grid;

	int splitCount = 0;

	input.open("./input.txt");
	if (!input) {
		std::cerr << "Failed to open file.\n";
		return (1);
	}

	while (std::getline(input, line))
		grid.push_back(line);

	for (size_t i = 0; i < grid.size(); i++) {
		for (size_t j = 0; j < grid[i].size(); j++) {
			if (i > 0 && grid[i][j] == 'S')
				continue;
			if (grid[i - 1][j] == 'S' || grid[i - 1][j] == '|') {
				if (grid[i][j] == '.' && grid[i - 1][j] == 'S')
					grid[i][j] = '|';
				else if (grid[i][j] == '.' && grid[i - 1][j] == '|')
					grid[i][j] = '|';
				else if (grid[i][j] == '^' && grid[i - 1][j] == '|') {
					if (j > 0 && grid[i][j - 1] != '^') {
						grid[i][j - 1] = '|';
					}
					if (j + 1 < grid[i].size() && grid[i][j + 1] != '^') {
						grid[i][j + 1] = '|';
					}
					splitCount++;
				}

			}
		}
	}

	std::cout << "The beam can be split " << splitCount << " times" << std::endl;

	input.close();
	return (0);
}
