#pragma once
#include <iostream>
using namespace std;

// Dynamic Array Class
template <class T>
class DynamicArray
{
private: /// Fields:
	T* _arr;
	int _logicalSize;
	int _physicalSize;

private: /// Private Methodes:
	// Increase the array size by 2
	void resize()
	{
		_physicalSize *= 2;
		T* temp = new T[_physicalSize];
		for (int i = 0; i < _logicalSize; i++)
			temp[i] = _arr[i];

		delete[] _arr;
		_arr = temp;
	}

public:/// Ctors:
	DynamicArray(int size = 2) : _logicalSize(0), _physicalSize(size), _arr(new T[size]) {}
	DynamicArray(const DynamicArray& other) : _arr(nullptr) { *this = other; }
	~DynamicArray()
	{
		delete[] _arr;
	}

public:	/// Operators:
	const DynamicArray& operator=(const DynamicArray& other) {
		if (this != &other) {
			_logicalSize = other._logicalSize;
			_physicalSize = other._physicalSize;
			delete[] _arr;
			_arr = new T[_physicalSize];
			for (int i = 0; i < _logicalSize; i++)
				_arr[i] = other._arr[i];
		}
		return *this;
	}
	const T& operator[](int i) const { return _arr[i]; }
	T& operator[](int i) { return _arr[i]; }

public: /// Methodes:
	// Insert on the end of the array
	void push_back(const T& value) {
		if (_logicalSize == _physicalSize)
			resize();
		_arr[_logicalSize++] = value;
	}
	// Getters:
	const T& front()    const { return _arr[0]; }
	int      size()     const { return _logicalSize; }
	int      capacity() const { return _physicalSize; }
	bool     empty()    const { return _logicalSize == 0; }
	void     clear() { _logicalSize = 0; }

	/// Iterator class:
	class iterator
	{
	private: /// Fields:
		DynamicArray* _da;
		int				 _i;
		bool       _reverse;

	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using different_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		friend class const_iterator; // const_iterator

	public: /// Ctors:
		iterator(DynamicArray& arr, int i) : _da(&arr), _i(i), _reverse(false) {}
		iterator(DynamicArray& arr, int i, bool b) : _da(&arr), _i(i), _reverse(b) {} // Reverse iterator builder
		iterator(const iterator& other) : _da(other._da), _i(other._i), _reverse(other._reverse) {}

	public: /// Operators:
		const iterator& operator=(const iterator& other) {
			_da = other._da;
			_i = other._i;
			return *this;
		}
		// comparison with another iterator:
		bool operator==(const iterator& other) const {
			return (_da == other._da) && (_i == other._i);
		}
		bool operator!=(const iterator& other) const {
			return !(*this == other);
		}
		// smart-pointer iterator methods:
		T& operator*() {
			return _da->_arr[_i];
		}
		T* operator->() {
			return &_da->_arr[_i];
		}
		// increment / decrement iterator methods:
		iterator& operator++()
		{
			if (this->_reverse == false)
			{
				++_i;
			}
			else
			{
				--_i;
			}
			return *this;
		}
		iterator operator++(int)
		{
			iterator temp(*this);
			if (this->_reverse == false)
			{
				++_i;
			}
			else
			{
				--_i;
			}
			return temp;
		}
		iterator& operator--()
		{
			if (this->_reverse == false)
			{
				--_i;
			}
			else
			{
				++_i;
			}
			return *this;
		}
		iterator operator--(int)
		{
			iterator temp(*this);
			if (this->_reverse == false)
			{
				--_i;
			}
			else
			{
				++_i;
			}
			return temp;
		}
		iterator operator-(int x)
		{
			iterator temp(*this);
			if (this->_reverse == false)
			{
				temp._i = (*this)._i - x;
			}
			else
			{
				temp._i = (*this)._i + x;
			}
			return temp;
		}
		iterator operator+(int x)
		{
			iterator temp(*this);
			if (this->_reverse == false)
			{
				temp._i = (*this)._i + x;
			}
			else
			{
				temp._i = (*this)._i - x;
			}
			return temp;
		}
	};

	/// Const-Iterator class: 
	class const_iterator
	{
	private:
		const DynamicArray* _da;
		const int            _i;

	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using different_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		friend class const_iterator; // const_iterator

	public: /// Ctors:
		const_iterator(DynamicArray& arr, int i) : _da(&arr), _i(i) {}
		const_iterator(const const_iterator& other) : _da(other._da), _i(other._i) {}
		const_iterator(const iterator& other) : _da(other._da), _i(other._i) {}

	public: /// Operators:
		const const_iterator operator=(const iterator& other)
		{
			_da = other._da;
			_i = other._i;
			return *this;
		}
		const const_iterator operator=(const const_iterator& other)
		{
			_da = other._da;
			_i = other._i;
			return *this;
		}
		bool operator==(const const_iterator& other) const {
			return (_da == other._da) && (_i == other._i);
		}
		bool operator!=(const const_iterator& other) const {
			return !(*this == other);
		}
		// smart-pointer iterator methods:
		T& operator*() const {
			return _da->_arr[_i];
		}
		T* operator->() const {
			return &_da->_arr[_i];
		}
		// increment / decrement iterator methods:
		const_iterator& operator++() {
			++_i;
			return *this;
		}
		const_iterator operator++(int) {
			iterator temp(*this);
			++_i;
			return temp;
		}
		const_iterator& operator--() {
			--_i;
			return *this;
		}
		const_iterator operator--(int) {
			iterator temp(*this);
			--_i;
			return temp;
		}
		const_iterator operator-(int x) {
			iterator temp(*this);
			temp._i = (*this)._i - x;
			return temp;
		}
		const_iterator operator+(int x) {
			iterator temp(*this);
			temp._i = (*this)._i + x;
			return temp;
		}
	};

	/// Iteraror Methodes:
	// Insert before iterator
	iterator insert(const iterator& pos, const T& val)
	{
		if (_logicalSize == _physicalSize)
		{
			resize();
		}
		iterator itrEnd = end();
		iterator itrCurrent = itrEnd, itrPrev = --itrEnd;

		while (itrCurrent != pos)
		{
			*itrCurrent = *itrPrev;
			itrCurrent = itrPrev--;
		}

		iterator p = pos;
		*p = val;
		++_logicalSize;
		return p;
	}

	// Erase a single cell, return the cell befoe iter
	iterator& erase(const iterator& iter)
	{
		iterator itrEnd = end();
		iterator itrCurrent = begin();
		iterator itrNext = begin() + 1;
		iterator temp = iter;
		while (itrCurrent != iter && itrCurrent != itrEnd)
		{
			itrCurrent = itrCurrent + 1;
			itrNext = itrNext + 1;
		}
		if (itrCurrent == iter)
		{
			while (itrCurrent != end())
			{
				*itrCurrent = *itrNext;
				itrCurrent = itrNext;
				itrNext = itrNext + 1;
			}
		}
		else // iter not exists
		{
			return begin();
		}
		_logicalSize--;
		return (temp - 1);
	}

	// Erase all cells from First to ont before Last, return the cell befoe first
	iterator& erase(const iterator& first, const iterator& last)
	{
		iterator itrEnd = end();
		iterator itrCurrent = begin();
		iterator itrNext = begin() + 1;
		iterator temp = first;

		// reach to "first":
		while (itrCurrent != first && itrCurrent != itrEnd)
		{
			itrCurrent++;
			itrNext++;
		}
		// reach to "last":
		while (itrEnd != last && itrEnd != itrCurrent)
		{
			itrEnd--;
		}
		itrEnd++; // to be one afer last
		if (itrCurrent == first)
		{
			while (itrNext != itrEnd)
			{
				*itrCurrent = *itrNext;
				++itrNext;
				_logicalSize--;
			}
		}
		else // "first" does not exists
		{
			return begin();
		}
		return (temp - 1);
	}

	// Begin / end "Getters":
	iterator begin() {
		return iterator(*this, 0);
	}
	iterator end() {
		return iterator(*this, _logicalSize);
	}
	iterator cbegin() {
		return const_iterator(*this, 0);
	}
	iterator cend() {
		return const_iterator(*this, _logicalSize);
	}
	iterator rend() {
		iterator itr = iterator(*this, 0, true);
		return itr;
	}
	iterator rbegin() {
		iterator itr = iterator(*this, _logicalSize, true);
		return itr;
	}
	const_iterator begin() const {
		return const_iterator(*this, 0);
	}
	const_iterator end() const {
		return const_iterator(*this, _logicalSize);
	}

	// Find Max index - assuming have " > " opperator !
	int findMax()
	{
		int indexMax = 0;
		T max = _arr[0];
		for (int i = 0; i < _logicalSize; i++)
		{
			if (_arr[i] > max)
			{
				max = _arr[i];
				indexMax = i;
			}
		}
		return indexMax;
	}

	// Print array:
	void print() const {
		for (int i = 0; i < _logicalSize; i++)
			cout << _arr[i] << " ";
		cout << endl;
	}
};
