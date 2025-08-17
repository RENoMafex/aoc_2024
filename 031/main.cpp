#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <regex>

std::ifstream infile("infile.txt");
std::regex regex("mul\\([0-9]{1,3},[0-9]{1,3}\\)", std::regex_constants::egrep);
std::regex single_num("[0-9]{1,3}", std::regex_constants::egrep);

int main() {
	int result = 0;
	std::string line = {};
	std::vector<std::string> matches = {};
	std::smatch match;
	while (std::getline(infile, line)) {
		auto search_start(line.cbegin());
		while (std::regex_search(search_start, line.cend(), match, regex)) {
			matches.push_back(match.str());
			search_start = match.suffix().first;
		}
	}

	std::array<std::string, 2> nums_str = {};
	std::array<int, 2> nums = {};
	for (const auto& str : matches) {
		auto search_start = str.cbegin();
		if (std::regex_search(search_start, str.cend(), match, single_num)) {
			nums_str.front() = match.str();
			search_start = match.suffix().first;
		}
		if (std::regex_search(search_start, str.cend(), match, single_num)) {
			nums_str.back() = match.str();
		}
		for (size_t i = 0; i < nums.size(); i++) {
			nums.at(i) = std::stoi(nums_str.at(i));
		}
		int mul = nums.front() * nums.back();
		result += mul;
	}

	std::cout << result << std::endl;

	return 0;
}
