#include <iostream>
# include <fstream>
# include <sstream>

struct Point {
	int x;
	int y;
};

int main() {
	std::ifstream input;
	std::string line;
	std::vector<Point> points;

	std::string token;

	long long maxArea = 0;
	long long width = 0;
	long long height = 0;
	long long area = 0;


	input.open("./input.txt");
	if (!input) {
		std::cerr << "Failed to open file.\n";
		return (1);
	}

	while (std::getline(input, line)) {
		Point p;
		std::stringstream ss(line);

		std::getline(ss, token, ',');
		p.x = std::stoi(token);

		std::getline(ss, token);
		p.y = std::stoi(token);

		points.push_back(p);
	}

	for (size_t i = 0; i < points.size(); i++) {
		for (size_t j = i + 1; j < points.size(); j++) {
			width = std::llabs(points[i].x - points[j].x) + 1;
			height = std::llabs(points[i].y - points[j].y) + 1;

			area = width * height;

			if (area > maxArea)
				maxArea = area;
		}
	}

	std::cout << "Largest rectangle area is " << maxArea << std::endl;

	input.close();
	return (0);
}
