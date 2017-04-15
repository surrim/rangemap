#include <iostream>

#include "rangemap.h"

int main(int argc, char *argv[]) {
	auto rangeMap = RangeMap();
	for (auto i = 1; i < argc; i++) {
		auto width = std::stoi(argv[i]);
		rangeMap.push(width);
	}
	auto size = rangeMap.size();
	for (auto id = 0ul; id < size; id++) {
		auto left = rangeMap.left(id);
		auto width = rangeMap.width(id);
		std::cout << "left(" << id << ") = " << left << ", width(" << id << ") = " << width << std::endl;
	}
	std::cout << "size() = " << size << std::endl;
	auto sum = rangeMap.sum();
	for (auto i = 0u; i < sum; i++) {
		auto left = 0u;
		auto id = rangeMap.find(i, left);
		std::cout << "find(" << i << ") = " << id << ", " << left << std::endl;
	}
	std::cout << "sum() = " << sum << std::endl;
	return 0;
}
