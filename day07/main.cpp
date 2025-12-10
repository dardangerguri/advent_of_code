#include <iostream>
# include <fstream>

int main() {
	std::ifstream input;
	std::string line;
	std::vector<std::string> grid;

	long long totalTimelines = 0;
	int rows;
	int cols;
	int sRow = 0;
	int sCol = 0;
	char c;
	long long currentValue;

	input.open("./input.txt");
	if (!input) {
		std::cerr << "Failed to open file.\n";
		return (1);
	}

	while (std::getline(input, line))
		grid.push_back(line);

	rows = grid.size();
	cols = grid[0].size();

	std::vector<std::vector<long long>> timelineCount(rows, std::vector<long long>(cols, 0));

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (grid[i][j] == 'S') {
				sRow = i;
				sCol = j;
				timelineCount[i][j] = 1;
				break;
			}
		}
	}

	for (int i = sRow; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			currentValue = timelineCount[i][j];
			if (currentValue == 0) {
				continue;
			}

			c = grid[i][j];

			if (c == 'S' || c == '.' || c == '|') {
				if (i + 1 < rows) {
					timelineCount[i + 1][j] += currentValue;
				}
			}

			else if (c == '^') {
				if (j > 0 && i + 1 < rows) {
					timelineCount[i + 1][j - 1] += currentValue;
				}
				if (j + 1 < cols && i + 1 < rows) {
					timelineCount[i + 1][j + 1] += currentValue;
				}
			}
		}
	}

	for (int j = 0; j < cols; j++)
		totalTimelines += timelineCount[rows - 1][j];

	std::cout << "The total timelines are " << totalTimelines << std::endl;

	input.close();
	return (0);
}
