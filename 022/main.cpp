#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <locale> // isspace...
#include <algorithm> // sort...
#include <functional> //greater...
#include <cstdint> // shorter types

#define TESTING

namespace std{
	template <typename T>
	using vector_2d = std::vector<std::vector<T>>;
}

int main() {
#	ifndef TESTING
	std::ifstream infile("infile.txt");
#	else
	std::ifstream infile("test.txt");
#	endif
	std::string line = {};
	uint16_t safe = 0;

	while (std::getline(infile, line)) {
		// put the numbers into the num_line vector
		std::vector<int> num_line = {};
		size_t space = 0, old_space = 0;
		while (true) {
			old_space = space;
			space = line.find(' ', space);
			if (!line.substr(old_space, space - old_space).empty()) {num_line.push_back(std::stoi(line.substr(old_space, space - old_space)));}
			if (space == std::string::npos) {break;}
			space++;
		}
		// make a 2 dimensional vector, which holds num_line with each one value erased
		std::vector_2d<int> possible_lines = {};
		for (size_t i = 0; i < num_line.size(); i++) {
			possible_lines.push_back(num_line);
		}
		for (size_t i = 0; i < possible_lines.size(); i++) {
			possible_lines.at(i).erase(possible_lines.at(i).begin() + static_cast<long>(i));
		}
		for (auto vec : possible_lines) {
			bool break_flag = false;
			if (vec.at(0) < vec.at(1)) { // numbers are rising
				for (size_t i = 0; i < vec.size() - 1; i++) {
					break_flag = (vec.at(i+1) - vec.at(i) <= 3 && vec.at(i+1) - vec.at(i) > 0) ? false : true;
					if (break_flag) {break;}
				}
				auto sorted = vec;
				std::sort(sorted.begin(), sorted.end());
				if (!break_flag && sorted == vec) {
					safe++;
					break;
				}
			} else
			if (vec.at(0) > vec.at(1)) { // numbers are falling
				for (size_t i = 0; i < vec.size() - 1; i++) {
					break_flag = (vec.at(i) - vec.at(i+1) <= 3 && vec.at(i) - vec.at(i+1) > 0) ? false : true;
					if (break_flag) {break;}
				}
				auto sorted = vec;
				std::sort(sorted.begin(), sorted.end(), std::greater<int>());
				if (!break_flag && sorted == vec) {
					safe++;
					break;
				}
			}
		}
	}
#	ifndef TESTING
	std::cout << safe << std::endl;
#	else
	std::string test_state = (safe == 8)? "TRUE":"FALSE";
	std::cout << test_state << std::endl;
	if (test_state == "FALSE") {
		std::cout << safe << std::endl;
	}
#	endif
	return 0;
}
