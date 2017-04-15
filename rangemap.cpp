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

#include "rangemap.h"

#include <algorithm>
#include <cassert>

static_assert(sizeof(0ul) == sizeof(size_t));

RangeMap::RangeMap(size_t size, unsigned defaultWidth):
		values(size) {
	assert(defaultWidth > 0);
	if (size) {
		values[0] = defaultWidth;
		auto frameSize = 1ul;
		while (true) {
			auto doubleFrameSize = 2 * frameSize;
			if (doubleFrameSize > size) {
				std::copy_n(values.begin(), size - frameSize, values.begin() + frameSize);
				break;
			}
			std::copy_n(values.begin(), frameSize, values.begin() + frameSize);
			values[doubleFrameSize - 1] *= 2;
			frameSize = doubleFrameSize;
		}
	}
}

size_t RangeMap::push(unsigned width) {
	assert(width > 0);
	auto id = values.size();
	for (auto bit = 1ul; id & bit; bit <<= 1) {
		width += values[id ^ bit];
	}
	values.push_back(width);
	return id;
}

void RangeMap::increment(size_t id, unsigned width) {
	assert(width > 0);
	for (auto bit = 1ul; id < values.size(); id ^= bit) {
		values[id] += width;
		while (id & bit) {
			bit <<= 1;
		}
	}
}

size_t RangeMap::size() const {
	return values.size();
}

unsigned RangeMap::width(size_t id) const {
	auto width = values[id];
	for (auto bit = 1ul; id & bit; bit <<= 1) {
		width -= values[id ^ bit];
	}
	return width;
}

static unsigned left(const std::vector<unsigned>& values, size_t id) {
	auto left = 0u;
	for (auto bit = 1u; id; bit <<= 1) {
		if (id & bit) {
			id ^= bit;
			left += values[id | (bit - 1)];
		}
	}
	return left;
}

unsigned RangeMap::sum() const {
	return ::left(values, values.size());
}

unsigned RangeMap::left(size_t id) const {
	assert(id < size());
	return ::left(values, id);
}

static size_t msb(size_t value) {
	auto bit = 1ul;
	while (bit < value) {
		bit <<= 1;
	}
	return bit;
}

size_t RangeMap::find(unsigned offset, unsigned& left) const {
	assert(offset < sum());
	auto foundId = 0ul;
	auto foundLeft = 0u;
	for (auto height = msb(values.size()); height > 1; height >>= 1) {
		auto middleId = foundId + (height >> 1);
		auto middleLeft = foundLeft + values[middleId - 1];
		if (offset >= middleLeft && middleId < values.size()) {
			foundId = middleId;
			foundLeft = middleLeft;
		}
	}
	left = foundLeft;
	return foundId;
}
