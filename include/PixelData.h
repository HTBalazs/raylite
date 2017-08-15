/*
    Copyright 2016-2017 Balazs Toth
    This file is part of Raylite.

    Raylite is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Raylite is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Raylite.  If not, see <http://www.gnu.org/licenses/>.

    For more information please visit: https://bitbucket.org/Rayliteproject/
*/

#pragma once

#include <memory>

template <typename T>
class PixelData final {
public:
	T* data;
	int size;
	PixelData() = delete;
	explicit PixelData(int s) {
		size = s;
		data = new T[size];
	}
	~PixelData() {
		delete [] data;
	}
	T& operator[](int i) const {
		return data[i];
	}
	PixelData(PixelData const& other) {
		size = other.size;
		data = ::operator new(sizeof(T)*size);

		for(int i=0; i<size; i++) 
			new (&data[i]) T{other[i]};
	}
	PixelData& operator=(PixelData const& other) {
		delete [] data;
		size = other.size;
		this->PixelData(other);
	}
	PixelData(PixelData&& other) {
		data = other.data;
		size = other.size;
		other.data = nullptr;
		other.size = 0;
	}
	PixelData& operator=(PixelData&& other) {
		if(this==&other) return *this;
		delete [] data;
		size = other.size;
		data = other.data;
		other.size = 0;
		other.data = nullptr;
	}
};

template <typename T> using PixelDataPtr = std::shared_ptr<PixelData<T>>;