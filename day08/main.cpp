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

public:
	UnionFind(int n) {
		parent.resize(n);
		size.resize(n, 1);
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
		return true;
	}

	int getSize(int x) {
		return size[find(x)];
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

	int edgesToProcess;
	int edgesProcessed;
	int connectionsMade;

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

	edgesToProcess = 1000;
	edgesProcessed = 0;
	connectionsMade = 0;

	for (size_t i = 0; i < edges.size() && edgesProcessed < edgesToProcess; i++) {
		edgesProcessed++;
		if (uf.unite(edges[i].a, edges[i].b)) {
			connectionsMade++;
		}
	}

	for (int i = 0; i < points.size(); i++) {
		if (uf.find(i) == i) {
			componentSizes.push_back(uf.getSize(i));
		}
	}

	std::sort(componentSizes.begin(), componentSizes.end(), [](int a, int b) {
		return a > b;
	});

	for (int i = 0; i < 3 && i < componentSizes.size(); i++) {
		result *= componentSizes[i];
	}

	std::cout << "Result of the three largest circuits is " << result << "\n";

	input.close();
	return (0);
}
