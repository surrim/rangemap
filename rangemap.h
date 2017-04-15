#pragma once

#include <cstddef>
#include <vector>

class RangeMap {
	std::vector<unsigned> values;
public:
	RangeMap(size_t size = 0, unsigned defaultWidth = 1);

	size_t push(unsigned width = 1);
	void increment(size_t id, unsigned width = 1);

	size_t size() const;
	unsigned width(size_t id) const;
	unsigned sum() const;
	unsigned left(size_t id) const;
	size_t find(unsigned offset, unsigned& left) const;
};
