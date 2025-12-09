#include <iostream>
# include <fstream>

int main() {
	std::ifstream input;
	std::string line;

	std::vector<std::pair<long long, long long>> ranges;
	std::vector<std::pair<long long, long long>> mergedRanges;
	std::vector<long long> ids;

	size_t dash;
	long rangeStart;
	long rangeEnd;
	long long freshCount = 0;
	long long totalFresh = 0;

	input.open("./input.txt");
	if (!input) {
		std::cerr << "Failed to open file.\n";
		return (1);
	}

	while (std::getline(input, line) && !line.empty()) {
		if (line.find('-') != std::string::npos) {
			dash = line.find('-');
			rangeStart = std::stoll(line.substr(0, dash));
			rangeEnd = std::stoll(line.substr(dash + 1));
			ranges.push_back({rangeStart, rangeEnd});
		}
	}

	while (std::getline(input, line)) {
		if (!(line.empty()))
			ids.push_back(std::stoll(line));
	}

	std::sort(ranges.begin(), ranges.end());

	for (auto &r : ranges) {
		if (mergedRanges.empty() || r.first > mergedRanges.back().second + 1)
			mergedRanges.push_back(r);
		else
			mergedRanges.back().second = std::max(mergedRanges.back().second, r.second);
	}

	for (auto &r : mergedRanges) {
		totalFresh += r.second - r.first + 1;
	}

	std::cout << "The total number of fresh ids " << totalFresh << std::endl;

	for (long long id : ids) {
		auto rangeIter = std::lower_bound(mergedRanges.begin(), mergedRanges.end(), std::make_pair(id, id));

		if (rangeIter != mergedRanges.begin()) {
			--rangeIter;
			if (id <=rangeIter->second) {
				freshCount++;
				continue;
			}
			++rangeIter;
		}

		if (rangeIter != mergedRanges.end() && id >= rangeIter->first && id <= rangeIter->second)
			freshCount++;
	}

	std::cout << "The number of fresh ingridients is " << freshCount << std::endl;

	input.close();
	return (0);
}
