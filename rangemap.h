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
