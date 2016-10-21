#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <algorithm>
#include <initializer_list>
#include <type_traits>

namespace sdplib {
	template <typename T>
	class vector {
	public:
		using iterator = T*;
		using const_iterator = const T*;
		using size_type = unsigned int;
	    vector(size_type cap = 8, const T& init = T{});
		vector(const vector<T>& other);
		vector(vector<T>&& other);
		vector(std::initializer_list<T> init);
		vector<T>& operator=(vector<T> other);
		~vector();
		size_type size() const;
		size_type capacity() const;
		void push_back(const T& data);
		void pop_back();
		iterator insert(iterator pos, const T& data);
		iterator erase(iterator pos);
		void reserve(size_type newCap);
		void resize(size_type newSize, const T& init = T{});
		T& at(size_type index);
		const T& at(size_type index) const;
		T& operator[](size_type index);
		const T& operator[](size_type index) const;
		bool empty() const;
		T& front();
		const T& front() const;
		T& back();
		const T& back() const;
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		void clear();
	private:
		T *arr;
		size_type cap;
		size_type sz;
		template<typename T>
		friend void swap(vector<T>& left, vector<T>& right);
	};
	template<typename T>
	vector<T>::vector(size_type cap, const T& init) : arr{ cap ? new T[cap] : nullptr },
												      sz{cap}, cap{ cap } {
		std::fill(arr, arr + cap, init);
	}

	template<typename T>
	vector<T>::vector(const vector<T>& other) : arr{ other.cap ? new T[other.cap] : nullptr },
											    sz{ other.sz }, cap{ other.cap } {
		///std::uninitialized_copy(other.arr, other.arr+capacity, arr);
		for (int i = 0; i < sz; i++) {
			new (arr + i) T{ other[i] };
		}
	}
	template<typename T>
	vector<T>& vector<T>::operator=(vector<T> other) {
		swap(*this, other);
		return *this;
	}
	template<typename T>
	vector<T>::vector(vector<T>&& other) : vector{}{
		swap(*this, other);
	}
	template<typename T>
	vector<T>::vector(std::initializer_list<T> init) : arr{ new T[init.size()] }, sz{init.size()},
													   cap{ init.size() } {
		if (init.size() <= size()) {
			std::copy(init.begin(), init.end(), arr);
		}
	}
	template<typename T>
	vector<T>::~vector() {
		clear();
		delete[] arr;
	}
	template<typename T>
	typename vector<T>::size_type vector<T>::size() const {
		return sz;
	}
	template<typename T>
	typename vector<T>::size_type vector<T>::capacity() const {
		return cap;
	}
	template<typename T>
	void vector<T>::push_back(const T& data) {
		if (sz == cap) {
			reserve(cap<<1);
		}
		new (arr + sz) T{ data };
		++sz;
	}
	template<typename T>
	void vector<T>::pop_back() {
		if (!empty()) {
			arr[--sz].~T();
		}
	}
	template<typename T>
	typename vector<T>::iterator vector<T>::insert(iterator pos, const T& data) {
		if (pos >= begin() && pos <= end()) {
			if (sz == cap) {
				int diff = pos - begin();
				reserve(cap<<1);
				pos = begin() + diff;
			}
			for (iterator i = end(); i > pos; i--) {
				*i = *(i - 1);
			}
			new (pos) T{ data };
			sz++;
		}
		else {
			throw std::out_of_range("vector<T>::insert(): position is out of range");
		}
		return pos;
	}

	template<typename T>
	typename vector<T>::iterator vector<T>::erase(iterator pos) {
		if (pos >= begin() && pos <= end()) {
			if (!empty()) {
				for (iterator i = pos; i < end()-1; i++) {
					*i = *(i + 1);
				}
				arr[sz - 1].~T();
				sz--;
			}
		}
		else {
			throw std::out_of_range("vector<T>::erase(): position is out of range");
		}
		return pos;
	}
	template<typename T>
	void vector<T>::reserve(size_type newCap) {
		if (newCap > cap) {
			T *newArr{ new T[newCap] };
			for (int i = 0; i < sz; i++) {
				new (newArr + i) T{ arr[i] };
				arr[i].~T();
			}
			cap = newCap;
			delete[] arr;
			arr = newArr;
		}
	}
	template<typename T>
	void vector<T>::resize(size_type newSize, const T& init) {
		if (newSize < sz) {
			for (int i = newSize; i < sz; i++) {
				arr[i].~T();
			}
			sz = newSize;
		}
		else if (newSize > sz) {
			if (newSize > cap) {
				reserve(newSize);
			}
			std::fill(arr+sz, arr + cap, init);
			sz = newSize;
		}
	}
	template<typename T>
	T& vector<T>::at(size_type index) {
		if (index >= sz) {
			throw std::out_of_range("vector<T>::at(): index is out of range");
		}
		return arr[index];
	}
	template<typename T>
	const T& vector<T>::at(size_type index) const {
		if (index >= sz) {
			throw std::out_of_range("vector<T>::at(): index is out of range");
		}
		return arr[index];
	}
	template<typename T>
	T& vector<T>::operator[](size_type index) {
		return arr[index];
	}
	template<typename T>
	const T& vector<T>::operator[](size_type index) const {
		return arr[index];
	}
	template<typename T>
	bool vector<T>::empty() const {
		return sz==0;
	}
	template<typename T>
	T& vector<T>::front() {
		return *arr;
	}
	template<typename T>
	const T& vector<T>::front() const {
		return *arr;
	}
	template<typename T>
	T& vector<T>::back() {
		return arr[sz - 1];
	}
	template<typename T>
	const T& vector<T>::back() const {
		return arr[sz - 1];
	}
	template<typename T>
	typename vector<T>::iterator vector<T>::begin() {
		return arr;
	}
	template<typename T>
	typename vector<T>::const_iterator vector<T>::begin() const {
		return arr;
	}
	template<typename T>
	typename vector<T>::iterator vector<T>::end() {
		return arr + sz;
	}
	template<typename T>
	typename vector<T>::const_iterator vector<T>::end() const {
		return arr + sz;
	}
	template<typename T>
	void vector<T>::clear() {
		for (int i = 0; i < sz; i++) {
			arr[i].~T();
		}
		sz = 0;
	}
	template<typename T>
	void swap(vector<T>& left, vector<T>& right) {
		using std::swap;
		swap(left.arr, right.arr);
		swap(left.sz, right.sz);
		swap(left.cap, right.cap);
	}
	template <typename T>
	void printVector(const vector<T>& vec) {
		std::cout << "size: " << vec.size() << " capacity: " << vec.capacity() << std::endl;
		for (const T& x : vec) {
			std::cout << x << " ";
		}
		std::cout << std::endl;
	}
}

#endif
