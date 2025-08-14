#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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

	int result = 0;
	for (auto l_int : left_side) {
		size_t i = 0;
		for (auto r_int : right_side) {
			if (l_int == r_int) i++;
		}
		result += l_int * i;
	}

	std::cout << result << std::endl;
	return 0;

}