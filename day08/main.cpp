#include <iostream>
# include <fstream>
# include <sstream>

struct Point {
	int x, y, z;
	int id;
};

struct Edge {
	int a, b;
	long long dist2;
};

class UnionFind {
private:
	std::vector<int> parent;
	std::vector<int> size;
	int components;

public:
	UnionFind(int n) {
		parent.resize(n);
		size.resize(n, 1);
		components = n;
		for (int i = 0; i < n; i++) {
			parent[i] = i;
		}
	}

	int find(int x) {
		if (parent[x] != x) {
			parent[x] = find(parent[x]);
		}
		return parent[x];
	}

	bool unite(int x, int y) {
		int rootX = find(x);
		int rootY = find(y);

		if (rootX == rootY) {
			return false;
		}

		if (size[rootX] < size[rootY]) {
			int temp = rootX;
			rootX = rootY;
			rootY = temp;
		}

		parent[rootY] = rootX;
		size[rootX] += size[rootY];
		components--;
		return true;
	}

	int getComponents() {
		return components;
	}
};

int main() {
	std::ifstream input;
	std::string line;
	std::vector<Point> points;
	std::vector<Edge> edges;
	std::vector<int> componentSizes;

	std::string token;
	int id = 0;

	long long dx;
	long long dy;
	long long dz;
	long long d2;

	int lastA = -1;
	int lastB = -1;
	int edgesProcessed = 0;
	int connectionsMade = 0;

	long long result = 1;

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

		std::getline(ss, token, ',');
		p.y = std::stoi(token);

		std::getline(ss, token, ',');
		p.z = std::stoi(token);

		p.id = id++;
		points.push_back(p);
	}

	for (size_t i = 0; i < points.size(); i++) {
		for (size_t j = i + 1; j < points.size(); j++) {
			dx = points[i].x - points[j].x;
			dy = points[i].y - points[j].y;
			dz = points[i].z - points[j].z;
			d2 = dx*dx + dy*dy + dz*dz;

			edges.push_back({ (int)i, (int)j, d2 });
		}
	}

	std::sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
		return (a.dist2 < b.dist2);
	});

	UnionFind uf(points.size());

	edgesProcessed = 0;
	connectionsMade = 0;

	for (size_t i = 0; i < edges.size(); i++) {
		edgesProcessed++;
		if (uf.unite(edges[i].a, edges[i].b)) {
			connectionsMade++;

			lastA = edges[i].a;
			lastB = edges[i].b;

			if (uf.getComponents() == 1) {
				break;
			}
		}
	}

	result = (long long)points[lastA].x * points[lastB].x;

	std::cout << "Result of the two X cordinates of the last two junction boxes is " << result << "\n";

	input.close();
	return (0);
}
