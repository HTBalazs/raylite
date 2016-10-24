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