#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
	std::vector<int> left_side = {};
	std::vector<int> right_side = {};
	std::ifstream infile("infile.txt");
	std::string line = {};
	
	// Read the file into the vectors
	while (std::getline(infile, line)) {
		left_side.push_back(std::stoi(line.substr(0, line.find(' '))));
		right_side.push_back(std::stoi(line.substr(line.find_last_of(' '), line.size())));
	}

	std::sort(left_side.begin(), left_side.end());
	std::sort(right_side.begin(), right_side.end());

	unsigned long diff = 0;
	for (size_t i = 0; i < left_side.size(); i++) {
		diff += std::abs(left_side.at(i) - right_side.at(i));
	}

	std::cout << diff << std::endl;

	return 0;

}