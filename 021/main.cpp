#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <locale> // isspace...
#include <algorithm> // sort...
#include <functional> //greater...
#include <cstdint> // shorter types

int main() {
	std::ifstream infile("infile.txt");
	std::string line = {};
	uint16_t safe = 0;

	while (std::getline(infile, line)) {
		// put the numbers into the num_line vector
		std::vector<uint16_t> num_line = {};
		size_t space = 0, old_space = 0;
		while (true) {
			old_space = space;
			space = line.find(' ', space);
			if (!line.substr(old_space, space - old_space).empty()) {num_line.push_back(std::stoi(line.substr(old_space, space - old_space)));}
			if (space == std::string::npos) {break;}
			space++;
		}
		// code from here should process each line.
		bool break_flag = false;
		if (num_line.at(0) < num_line.at(1)) { // numbers are rising
			for (size_t i = 0; i < num_line.size() - 1; i++) {
				break_flag = (num_line.at(i+1) - num_line.at(i) <= 3 && num_line.at(i+1) - num_line.at(i) > 0) ? false : true;
				if (break_flag) {break;}
			}
			auto sorted = num_line;
			std::sort(sorted.begin(), sorted.end());
			if (!break_flag && sorted == num_line) safe++;
		} else
		if (num_line.at(0) > num_line.at(1)) { // numbers are falling
			for (size_t i = 0; i < num_line.size() - 1; i++) {
				break_flag = (num_line.at(i) - num_line.at(i+1) <= 3 && num_line.at(i) - num_line.at(i+1) > 0) ? false : true;
				if (break_flag) {break;}
			}
			auto sorted = num_line;
			std::sort(sorted.begin(), sorted.end(), std::greater<int>());
			if (!break_flag && sorted == num_line) safe++;
		}
	}

	std::cout << safe << std::endl;
	return 0;
}
