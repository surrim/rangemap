#include "rangemap.h"

RangeMap::RangeMap(size_t size, unsigned defaultWidth):
		values(size) {
	for (auto i = 0u; i < values.size(); i++) {
		increment(i, defaultWidth);
	}
}

size_t RangeMap::push(unsigned width) {
    auto id = values.size();
    for (auto bit = 1u; id & bit; bit <<= 1) {
        width += values[id ^ bit];
    }
    values.push_back(width);
    return id;
}

void RangeMap::increment(size_t id, unsigned width) {
    for (auto bit = 1u; id < values.size(); id ^= bit) {
        values[id] += width;
        while (id & bit) {
            bit <<= 1;
        }
    }
}

unsigned RangeMap::width(size_t id) const {
    auto width = values[id];
    for (auto bit = 1u; id & bit; bit <<= 1) {
        width -= values[id ^ bit];
    }
    return width;
}

unsigned RangeMap::sum() const {
    return left(values.size());
}

unsigned RangeMap::left(size_t id) const {
    auto left = 0u;
    for (auto bit = 1u; id; bit <<= 1) {
        if (id & bit) {
            id ^= bit;
            left += values[id | (bit - 1)];
        }
    }
    return left;
}

static auto msb(auto value) {
    auto bit = 1u;
    while (bit < value) {
        bit <<= 1;
    }
    return bit;
}

size_t RangeMap::find(unsigned offset, unsigned& left) const {
    auto foundId = size_t(0);
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
