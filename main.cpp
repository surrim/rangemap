/* Copyright 2017 surrim
 *
 * This file is part of RangeMap.
 *
 * RangeMap is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RangeMap is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with RangeMap.  If not, see <http://www.gnu.org/licenses/>.
 */

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
