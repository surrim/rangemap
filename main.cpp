#include <iostream>

#include "rangemap.h"

int main(int argc, char *argv[]) {
	auto rangeMap = RangeMap();
	for (auto i = 1; i < argc; i++) {
		auto width = std::stoi(argv[i]);
		rangeMap.push(width);
	}
	for (auto i = 0u; i < rangeMap.sum(); i++) {
		auto left = 0u;
		auto id = rangeMap.find(i, left);
		if (left == i) {
			std::cout << i << '\t' << id << '\t' << left << std::endl;
		}
	}
    return 0;
}
