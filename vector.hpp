// #ifndef VECTOR_HPP
// # define VECTOR_HPP

// # include <iostream>
// # include <vector>
// # include "vectorIterator.hpp"

// // empty — определяет, пуста ли коллекция;
// // size — возвращает размер коллекции;
// // begin — возвращает прямой итератор, указывающий на начало коллекции;
// // end — возвращает прямой итератор, указывающий на конец коллекции,
// // 	т.е. на несуществующий элемент, идущий после последнего;
// // rbegin — возвращает обратный итератор на начало коллекции;
// // rend — возвращает обратный итератор на конец коллекции;
// // clear — очищает коллекцию, т.е. удаляет все ее элементы;
// // erase — удаляет определенные элементы из коллекции;
// // capacity — возвращает вместимость коллекции, т.е. количество элементов,
// // 	которое может вместить эта коллекция (фактически, сколько памяти под коллекцию выделено);
// namespace ft
// {
// 	template <class T, class A = std::allocator<T> >
// 	class vector
// 	{
// 	public:
	
// 		//member_types
// 		typedef A										allocator_type;
// 		typedef typename A::value_type					value_type;
// 		typedef typename A::pointer						pointer;
// 		typedef typename A::const_pointer				const_pointer;
// 		typedef typename A::reference					reference;
// 		typedef typename A::const_reference				const_reference;
// 		typedef typename A::size_type					size_type;
// 		typedef typename A::difference_type				difference_type;
// 		typedef vectorIterator<pointer>					iterator;
// 		typedef vectorIterator<const_pointer>			const_iterator;
// 		typedef ft::reverse_iterator<iterator>			reverse_iterator;
// 		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

// 	private:
// 		// Fields
// 		pointer			_arr;
// 		size_type		_size;
// 		size_type		_capacity;
// 		allocator_type	_alloc;

// 	public:

// 		//1) Конструктор по умолчанию. Создает пустой контейнер.
// 		explicit vector(const allocator_type& alloc = allocator_type()) :
// 						_arr(0), _size(0), _capacity(0), _alloc(alloc) {}
// 		// 2) Создает контейнер с count копиями элемента со значением value.
// 		explicit vector(size_type n, const value_type& val = value_type(),
// 						const allocator_type& alloc = allocator_type()) :
// 						_size(n), _capacity(n), _alloc(alloc)
// 		{
// 			_arr = _alloc.allocate(n);
// 			for (size_type i = 0; i < _size; i++)
// 				_alloc.construct(_arr + i, val);
// 		}
// 		// Создает контейнер с содержимым диапазона (first, last).
// 		template <class InputIterator>
// 		vector(InputIterator first, InputIterator last,
// 				const allocator_type& alloc = allocator_type(),
// 				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) :
// 				_size(0), _alloc(alloc)
// 		{
// 			_size = static_cast<size_type>(last - first);
// 			_arr = _alloc.allocate(_size);
// 			for (size_type i = 0; first != last; first++, i++)
// 				_alloc.construct(_arr + i, *first);
// 			_capacity = _size;
// 		}

// 		vector(const vector& x) : _size(x._size), _capacity(x._capacity), _alloc(x._alloc)
// 		{
// 			_arr = _alloc.allocate(_size);
// 			for (size_type i = 0; i < _size; i++)
// 				_alloc.construct(_arr + i, x._arr[i]);
// 		}

// 		~vector()
// 		{
// 			for (size_type i = 0; i < _size; i++)
// 				_alloc.destroy(_arr + i);
// 			_alloc.deallocate(_arr, _capacity);
// 		}

// 		vector& operator= (const vector& x)
// 		{
// 			if (this != &x)
// 			{
// 				for (size_type i = 0; i < _size; i++)
// 					_alloc.destroy(_arr + i);
// 				_alloc.deallocate(_arr, _size);
// 				_size = x._size;
// 				_capacity = x._capacity;
// 				_arr = _alloc.allocate(_size);
// 				for (size_type i = 0; i < _size; i++)
// 					_alloc.construct(_arr + i, x._arr[i]);
// 			}
// 			return *this;
// 		}

// 		//iterators
// 		iterator begin()
// 		{
// 			return iterator(_arr);
// 		}
// 		const_iterator begin() const
// 		{
// 			return const_iterator(_arr);
// 		}
// 		iterator end()
// 		{
// 			return iterator(_arr + _size);
// 		}
// 		const_iterator end() const
// 		{
// 			return const_iterator(_arr + _size);
// 		}
// 		reverse_iterator rbegin()
// 		{
// 			return reverse_iterator(end());
// 		}
// 		const_reverse_iterator rbegin() const
// 		{
// 			return const_reverse_iterator(end());
// 		}
// 		reverse_iterator rend()
// 		{
// 			return reverse_iterator(begin());
// 		}
// 		const_reverse_iterator rend() const
// 		{
// 			return const_reverse_iterator(begin());
// 		}

// 		size_type size() const
// 		{
// 			return _size;
// 		}
// 		size_type max_size() const
// 		{
// 			return _alloc.max_size();
// 		}
// 		void resize(size_type n, value_type val = value_type())
// 		{
// 			if (n > max_size())
// 				throw std::length_error("vector");
// 			if (_size < n)
// 				insert(end(), n - _size, val);
// 			else if (_size > n)
// 			{
// 				for (size_type i = n; i < _size; i++)
// 					_alloc.destroy(&_arr[i]);
// 				_size = n;
// 			}
// 		}
// 		size_type capacity() const
// 		{
// 			return _capacity;
// 		}
// 		bool empty() const
// 		{
// 			return _size == 0;
// 		}
// 		void reserve(size_type n)
// 		{
// 			if (n > max_size())
// 				throw std::length_error("vector");
// 			if (n > _capacity)
// 			{
// 				try
// 				{
// 					pointer tmp = _alloc.allocate(n);
// 					for (size_type i = 0; i < _size; i++)
// 						_alloc.construct(&tmp[i], _arr[i]);
// 					_alloc.deallocate(_arr, _capacity);
// 					_capacity = n;
// 					_arr = tmp;
// 				}
// 				catch(...)
// 				{
// 					_alloc.deallocate(_arr, _capacity);
// 					throw;
// 				}
// 			}
// 		}

// 		//element access
// 		reference operator[](size_type n)
// 		{
// 			return *(begin() + n);
// 		}
// 		const_reference operator[](size_type n) const
// 		{
// 			return *(begin() + n);
// 		}
// 		reference at(size_type n)
// 		{
// 			if (n < 0 || n > _size)
// 				throw std::out_of_range("vector");
// 			return *(begin() + n);
// 		}
// 		const_reference at(size_type n) const
// 		{
// 			if (n < 0 || n > _size)
// 				throw std::out_of_range("vector");
// 			return *(begin() + n);
// 		}
// 		reference front()
// 		{
// 			return *_arr;
// 		}
// 		const_reference front() const
// 		{
// 			return *_arr;
// 		}
// 		reference back()
// 		{
// 			return _arr[_size - 1];
// 		}
// 		const_reference back() const
// 		{
// 			return _arr[_size - 1];
// 		}

// 		//modifiers
// 		template <class InputIterator>
// 		void assign(InputIterator first, InputIterator last,
// 					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
// 		{
// 			if (first > last)
// 				std::logic_error("vector");
// 			clear();
// 			size_type	dif = static_cast<size_type>(last - first);
// 			size_type	m;
// 			if (_capacity < dif)
// 			{
// 				m = (_capacity * 2 > dif) ? _capacity * 2 : dif;
// 				_alloc.deallocate(_arr, _capacity);
// 				_arr = _alloc.allocate(m);
// 				_capacity = m;
// 			}
// 			for (iterator pos = begin(); first != last; pos++, first++)
// 				_alloc.construct(pos.base(), *first);
// 			_size = dif;
// 		}
// 		void assign(size_type n, const value_type& val)
// 		{
// 			size_type	m;
// 			clear();
// 			if (_capacity < n)
// 			{
// 				m = (_capacity * 2 > n) ? _capacity * 2 : n;
// 				_alloc.deallocate(_arr, _capacity);
// 				_arr = _alloc.allocate(m);
// 				_capacity = m;
// 			}
// 			for (size_type i = 0; i < n; i++)
// 				_alloc.construct(&_arr[i], val);
// 			_size = n;
// 		}
// 		void push_back(const value_type& val)
// 		{
// 			insert(end(), val);
// 		}
// 		void pop_back()
// 		{
// 			if (_size)
// 				_alloc.destroy(&_arr[--_size]);
// 		}
// 		iterator insert(iterator position, const value_type& val)
// 		{
// 			if (position < begin() || position > end())
// 				throw std::logic_error("vector");
// 			size_type	idx = static_cast<size_type>(position - begin());
// 			insert(position, 1, val);
// 			return iterator(&_arr[idx]);
// 		}
// 		void insert(iterator position, size_type n, const value_type& val)
// 		{
// 			if (n == 0)
// 				return ;
// 			else if (max_size() - size() < n)
// 				throw std::length_error("vector");
// 			else
// 			{
// 				size_type	dif = static_cast<size_type>(position - begin());
// 				if (_size + n > _capacity)
// 				{
// 					size_type	newCapacity;
// 					if (_size + n <= _capacity * 2)
// 						newCapacity = _capacity * 2;
// 					else
// 						newCapacity = _size + n;
// 					pointer tmp = _alloc.allocate(newCapacity);
// 					std::uninitialized_copy(begin(), position, iterator(tmp));
// 					try
// 					{
// 						for (size_type i = 0; i < n; i++)
// 							_alloc.construct(&tmp[dif + i], val);
// 					}
// 					catch (...)
// 					{
// 						for (size_type i = 0; i < dif + n; i++)
// 							_alloc.destroy(&tmp[i]);
// 						_alloc.deallocate(tmp, newCapacity);
// 						throw;
// 					}
// 					std::uninitialized_copy(position, end(), iterator(&tmp[dif + n]));
// 					_alloc.deallocate(_arr, _capacity);
// 					_capacity = newCapacity;
// 					_arr = tmp;
// 				}
// 				else
// 				{
// 					for (size_type i = _size; i > dif; i--)
// 					{
// 						_alloc.destroy(&_arr[i + n - 1]);
// 						_alloc.construct(&_arr[i + n - 1], _arr[i - 1]);
// 					}
// 					for (size_type i = 0; i < n; i++)
// 					{
// 						_alloc.destroy(&_arr[dif + i]);
// 						_alloc.construct(&_arr[dif + i], val);
// 					}
// 				}
// 				_size += n;
// 			}
// 		}
// 		template <class InputIterator>
// 		void insert(iterator position, InputIterator first, InputIterator last,
// 					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
// 		{
// 			if (position < begin() || position > end() || first > last)
// 				throw std::logic_error("vector");
// 			size_type	dif = static_cast<size_type>(position - begin());
// 			size_type	n = static_cast<size_type>(last - first);
// 			if (_size + n > _capacity)
// 			{
// 				size_type	newCapacity;
// 				if (_size + n <= _capacity * 2)
// 					newCapacity = _capacity * 2;
// 				else
// 					newCapacity = _size + n;
// 				pointer tmp = _alloc.allocate(newCapacity);
// 				std::uninitialized_copy(begin(), position, iterator(tmp));
// 				try
// 				{
// 					for (size_type i = 0; i < n; i++, first++)
// 						_alloc.construct(&tmp[dif + i], *first);
// 				}
// 				catch (...)
// 				{
// 					for (size_type i = 0; i < dif + n; i++)
// 						_alloc.destroy(&tmp[i]);
// 					_alloc.deallocate(tmp, newCapacity);
// 					throw;
// 				}
// 				std::uninitialized_copy(position, end(), iterator(&tmp[dif + n]));
// 				_alloc.deallocate(_arr, _capacity);
// 				_capacity = newCapacity;
// 				_arr = tmp;
// 			}
// 			else
// 			{
// 				for (size_type i = _size; i > dif; i--)
// 				{
// 					_alloc.destroy(&_arr[i + n - 1]);
// 					_alloc.construct(&_arr[i + n - 1], *(first + i - 1));
// 				}
// 				for (size_type i = 0; i < n; i++)
// 				{
// 					_alloc.destroy(&_arr[dif + i]);
// 					_alloc.construct(&_arr[dif + i], *first);
// 				}
// 			}
// 			_size += n;
// 		}
// 		iterator erase(iterator position)
// 		{
// 			if (position < begin() || position >= end())
// 				throw std::logic_error("vector");
// 			size_type	dif = static_cast<size_type>(position - begin());
// 			for (size_type i = dif; i < _size - 1; i++)
// 			{
// 				_alloc.destroy(&_arr[i]);
// 				_alloc.construct(&_arr[i], _arr[i + 1]);
// 			}
// 			_alloc.destroy(&_arr[_size - 1]);
// 			_size--;
// 			return position;
// 		}
// 		iterator erase(iterator first, iterator last)
// 		{
// 			if (first > last || first < begin() || last > end())
// 				throw std::logic_error("vector");
// 			size_type	dif = static_cast<size_type>(first - begin());
// 			size_type	n = static_cast<size_type>(last - first);
// 			size_type	dif2 = static_cast<size_type>(end() - last);
// 			for (size_type i = 0; i < n; i++)
// 				_alloc.destroy(&_arr[dif + i]);
// 			size_type i = dif;
// 			for (; last != end(); i++, last++)
// 			{
// 				if (_arr[i])
// 					_alloc.destroy(&_arr[i]);
// 				_alloc.construct(&_arr[i], *last);
// 			}
// 			for (; i < _size; i++)
// 				_alloc.destroy(&_arr[i]);
// 			_size -= n;
// 			return first;
// 		}
// 		void swap(vector& x)
// 		{
// 			ft::swap(_alloc, x._alloc);
// 			ft::swap(_capacity, x._capacity);
// 			ft::swap(_size, x._size);
// 			ft::swap(_arr, x._arr);
// 		}
// 		void clear()
// 		{
// 			for (iterator it = begin(); it != end(); it++)
// 				_alloc.destroy(it.base());
// 			_size = 0;
// 		}

// 		//allocator
// 		allocator_type get_allocator() const
// 		{
// 			return _alloc;
// 		}
// 	};


// 	//relational operations
// 	template <class T, class Alloc>
// 	bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
// 	{
// 		return lhs.size() == rhs.size()
// 				&& ft::equal(lhs.begin(), lhs.end(), rhs.begin());
// 	}
// 	template <class T, class Alloc>
// 	bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
// 	{
// 		return !(lhs == rhs);
// 	}
// 	template <class T, class Alloc>
// 	bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
// 	{
// 		return ft::lexicographical_compare(lhs.begin(), lhs.end(),
// 											rhs.begin(), rhs.end());
// 	}
// 	template <class T, class Alloc>
// 	bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
// 	{
// 		return rhs < lhs;
// 	}
// 	template <class T, class Alloc>
// 	bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
// 	{
// 		return !(rhs < lhs);
// 	}
// 	template <class T, class Alloc>
// 	bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
// 	{
// 		return !(lhs < rhs);
// 	}

// 	//swap
// 	template <class T, class Alloc>
// 	void swap(vector<T, Alloc>& x, vector<T, Alloc>& y)
// 	{
// 		x.swap(y);
// 	}
// } // namespace ft

// #endif

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "iterator.hpp"
# include "algorithm.hpp"
# include "vectorIterator.hpp"
# include <string>
# include <iostream>
# include <algorithm>
# include <limits>

namespace ft
{
	template < class T, class Allocator = std::allocator<T> >
	class vector // generic template
	{
		public:
			typedef T									value_type;
			typedef Allocator							allocator_type;
			typedef typename allocator_type::size_type	size_type;
			typedef typename allocator_type::difference_type	difference_type;
			typedef typename allocator_type::reference	reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer	pointer;
			typedef typename allocator_type::const_pointer	const_pointer;
			typedef vectorIterator<pointer>					iterator;
			typedef vectorIterator<const_pointer>				const_iterator;
			typedef ft::reverse_iterator<pointer>		reverse_iterator;
			typedef ft::reverse_iterator<const_pointer>	const_reverse_iterator;

		private:
			allocator_type		_alloc;
			value_type*			_vec;
			size_type			_size;
			size_type			_capacity;

		public: //construct
			explicit vector (const allocator_type& alloc = allocator_type()):
				_alloc(alloc), _vec(nullptr), _size(0), _capacity(0) {};
			vector (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type())
			{
				if (n < 0)
					throw std::out_of_range("vector");
				_alloc = alloc;
				_capacity = _size = n;
				_vec = _alloc.allocate(_capacity);
				for (size_t i = 0; i < n; ++i)
					_vec[i] = val;
			};
			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
                 const allocator_type& alloc = allocator_type(), typename ft::enable_if<!is_integral<InputIterator>::value, bool>::type = true):
				 _alloc(alloc), _vec(nullptr), _size(0), _capacity(0)
			{ this->assign(first, last); };
			vector (const vector& x): _vec(nullptr), _size(0), _capacity(0) { *this = x; };

		public: //destruct
			~vector()
			{
				if (this->_vec != nullptr)
					clear();
				this->_alloc.deallocate(this->_vec, this->_capacity);
			};

		public: //operator=
			vector& operator= (const vector& x)
			{
				if (this != &x)
				{
					if (this->_capacity != 0)
						this->_alloc.deallocate(this->_vec, this->_capacity);
					this->_alloc = x._alloc;
					this->_size = x._size;
					this->_capacity = x._size;
					this->_vec = this->_alloc.allocate(this->_capacity);
					for (size_t i = 0; i < this->_size; i++)
						this->_alloc.construct(this->_vec + i, x._vec[i]);
				}
				return (*this);
			}

		public: //itgerators
			iterator begin() { return(iterator(this->_vec)); };
			const_iterator begin() const	{ return (const_iterator(this->_vec)); };
			iterator end()	{ return(iterator(begin() + size())); };
			const_iterator end() const	{ return (const_iterator(begin() + size())); };
			reverse_iterator rbegin() { return(reverse_iterator((end()).base())); };
			const_reverse_iterator rbegin() const { return(const_reverse_iterator((end()).base())); };
			reverse_iterator rend() { return(reverse_iterator((begin()).base())); };
			const_reverse_iterator rend() const { return(const_reverse_iterator((begin()).base())); };

		public: //capacity
			size_type	size()		const	{ return (this->_size); };
			size_type max_size() const { return (std::min<size_type>(std::numeric_limits<size_type>::max()
				/ sizeof(value_type), std::numeric_limits<difference_type>::max())); };
			size_type capacity() const { return (this->_capacity); };
			bool empty() const { return (!this->_size); };
			void reserve (size_type n)
			{
				if (n > capacity()) {
					value_type* temp = this->_alloc.allocate(n);
					if (this->_vec != NULL) {
						for(size_t i = 0; i < size(); i++) {
							this->_alloc.construct(temp + i, this->_vec[i]);
							this->_alloc.destroy(this->_vec + i);
						}
						this->_alloc.deallocate(this->_vec, capacity());
					}
					this->_capacity = n;
					this->_vec = temp;
				}
			};
			void		resize (size_type n, value_type val = value_type()) {
				if (n < _size) {
					while (_size != n)
						pop_back();
				} else {
					if (_capacity * 2 < n)
						reserve(n);
					while (_size != n)
						push_back(val);
				}
			}

		public: //element access
			reference operator[] (size_type n) { return (this->_vec[n]); };
			const_reference operator[] (size_type n) const { return (this->_vec[n]); };
			reference at (size_type n) {
				if (n >= size())
					throw std::out_of_range("vector");
				return (this->_vec[n]);
			};
			const_reference at (size_type n) const {
				if (n >= size())
					throw std::out_of_range("vector");
				return (this->_vec[n]);
			};
			reference front() { return (this->_vec[0]); };
			const_reference front() const { return (this->_vec[0]); };
			reference back() { return (this->_vec[this->_size - 1]); };
			const_reference back() const { return (this->_vec[this->_size - 1]); };

		public: //Modifiers
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last, typename ft::enable_if<!is_integral<InputIterator>::value, bool>::type = true)
			{
				size_type	len	= last - first;
				clear();
				if (len > capacity())
				{
					this->_alloc.deallocate(this->_vec, capacity());
					this->_vec = this->_alloc.allocate(len);
					this->_capacity = len;
				}
				for (size_type i = 0; i < len; i++)
					this->_alloc.construct(this->_vec + i, *(first + i));
				this->_size = len;
			}
			void assign (size_type n, const value_type& val) {
				clear();
				if (n > capacity()) {
					this->_alloc.deallocate(this->_vec, capacity());
					this->_vec = this->_alloc.allocate(n);
					this->_capacity = n;
				}
				for (size_t i = 0; i < n; i++)
					this->_alloc.construct(this->_vec + i, val);
				this->_size = n;				
			};

			void push_back (const value_type& val) {
				if (_size == _capacity)
					(!_capacity) ? this->reserve(1) : this->reserve(_capacity * 2);
				this->_alloc.construct(this->_vec + this->_size, val);
				++this->_size;
			};
			void pop_back() {
				this->_alloc.destroy(this->_vec + this->_size);
				--this->_size;
			};

			iterator insert (iterator position, const value_type& val) {
				difference_type diff = end() - position;
				if (this->_size == this->_capacity)
					reserve(capacity() + 1);
				iterator it = end();
				while (diff != 0) {
					*(it) = *(it - 1);
					it--;
					diff--;
				}
				*(it) = val;
				++this->_size;
				return (it);
			};
    		void insert (iterator position, size_type n, const value_type& val) {
				difference_type diff = end() - position;
				difference_type posIndex = position - begin();
				if (size() + n > capacity()) {
					if (size() + n > capacity() * 2)
						reserve(size() + n);
					else
						reserve(capacity() * 2);
				}
				iterator it = end() - 1;
				for (difference_type i = 0; i < diff; i++) {
					*(it + n) = *(it);
					it--;
				}
				it = begin() + posIndex;
				for (size_t i = 0; i < n; i++)
					*(it + i) = val;
				this->_size += n;		
			};
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!is_integral<InputIterator>::value, bool>::type = true)
			{
				difference_type	diff = end() - position;
				difference_type	len	= last - first;
				difference_type posIndex = position - begin();
				if (size() + len > capacity()) {
					if (size() + len > capacity() * 2)
						reserve(size() + len);
					else
						reserve(capacity() * 2);
				}
				iterator it = end() - 1;
				for (difference_type i = 0; i < diff; i++) {
					*(it + len) = *(it);
					it--;
				}
				it = begin() + posIndex;
				for (difference_type i = 0; i < len; i++)
					*(it + i) = *(first++);
				this->_size += len;
			}

			iterator erase (iterator position) {
				iterator it = position;
				this->_alloc.destroy(it.base());
				while (it != end() - 1) {
					*(it) = *(it + 1);
					it++;
				}
				this->_size--;
				return (position);
			};
			iterator erase (iterator first, iterator last) {
				iterator it = first;
				size_type len = last - first;
				this->_size -= len;
				for (size_type i = 0; i < _size; i++)
					this->_alloc.destroy((first + i).base());
				while (it != end()) {
					*(it) = *(it + len);
					it++;
				}
				return (first);
			};

			void swap (vector& x) {
				std::swap(_size, x._size);
				std::swap(_capacity, x._capacity);
				std::swap(_alloc, x._alloc);
				std::swap(_vec, x._vec);
			};
			void clear() {
				for (size_t i = 0; i < this->_size; i++)
					this->_alloc.destroy(&this->_vec[i]);
				this->_size = 0;
			};

		public: //allocator
			allocator_type get_allocator() const { return (this->_alloc); };
	};
	template <class T, class Alloc>
  	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		  return ((lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));};
	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (!(lhs == rhs));
	};
	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	};
	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (!(lhs > rhs));
	};
	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	};
	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (!(lhs < rhs));
	};

	template <class T, class Alloc>
  	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) { x.swap(y); };
};

#endif