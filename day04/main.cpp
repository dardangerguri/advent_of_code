#include <iostream>
# include <fstream>

int main() {
	std::ifstream input;
	std::string line;
	std::vector<std::string> grid;

	int rollpapersAccesible = 0;
	int rollpaperCount = 0;
	int ni;
	int nj;
	int rowOffset[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
	int colOffset[8] = {-1, 0, 1, -1, 1, -1, 0, 1};


	input.open("./input.txt");
	if (!input) {
		std::cerr << "Failed to open file.\n";
		return (1);
	}

	while (std::getline(input, line))
		grid.push_back(line);

	for (size_t i = 0; i < grid.size(); i++) {
		for (size_t j = 0; j < grid[i].size(); j++) {
			if (grid[i][j] != '@')
				continue;

			rollpaperCount = 0;
			for (int k = 0; k < 8; k++) {
				ni = i + rowOffset[k];
				nj = j + colOffset[k];

				if (ni >= 0 && ni < grid.size() && nj >= 0 && nj < grid[i].size())
					if (grid[ni][nj] == '@')
						rollpaperCount++;
			}

			if (rollpaperCount < 4)
				rollpapersAccesible++;
		}
	}

	std::cout << "The number of rollpapers that can be accessed by a forklift is " << rollpapersAccesible << std::endl;

	input.close();
	return (0);
}
