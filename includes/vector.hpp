#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <stdexcept>
#include <iterator>

// i refer to cpp.com
// https://cplusplus.com/reference/vector/vector/


template<bool Cond, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };

template <typename T> struct is_integral { static const bool value = false; };
template <> struct is_integral<int> { static const bool value = true; };
template <> struct is_integral<long> { static const bool value = true; };
template <> struct is_integral<unsigned int> { static const bool value = true; };
template <> struct is_integral<unsigned long> { static const bool value = true; };
template <> struct is_integral<char> { static const bool value = true; };
template <> struct is_integral<bool> { static const bool value = true; };

namespace ft {
	template< typename T, typename _alloc = std::allocator<T> >
	class vector {
		public:
			typedef T value_type;
			typedef _alloc allocator_type;
			typedef T& reference;
			typedef const T& const_reference;
			typedef T* pointer;
			typedef const T* const_pointer;
			typedef pointer iterator;
			typedef const_pointer const_iterator;
			typedef std::reverse_iterator<iterator> reverse_iterator;
			typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef ptrdiff_t difference_type;
			typedef size_t size_type;

		//constructor
		explicit vector(
			const allocator_type &alloc = allocator_type()
		) :
		_M_start(0), _M_finish(0), _M_end_of_storage(0), _Alloc(alloc) {}

		explicit vector(
			size_type n,
			const value_type &val = value_type(),
			const allocator_type &alloc = allocator_type()
		) :
		_M_start(0), _M_finish(0), _M_end_of_storage(0), _Alloc(alloc)
		{
			if (n > 0) {
				this->_M_start = this->_Alloc.allocate(n);
				this->_M_finish = this->_M_start;
				this->_M_end_of_storage = this->_M_start + n;
				pointer p = this->_M_start;
				for(; p != this->_M_end_of_storage; p++) {
					this->_Alloc.construct(p, val);
					this->_M_finish++;
				}
			}
		}

		template <class InputIterator>
		vector(
			InputIterator first,
			InputIterator last,
			const allocator_type& alloc = allocator_type()
		) :
		_Alloc(alloc)
		{
			pointer p = this->_Alloc.allocate(last - first);
			this->_M_start = p;
			this->_M_finish = p + (last - first);
			this->_M_finish = p + (last - first);
			while (first != last) {
				this->_Alloc.construct(p, *first);
				first++;
				p++;
			}
		}


		vector (const vector& x) :
		_M_start(0), _M_finish(0), _M_end_of_storage(0), _Alloc(x._Alloc)
		{
			*this = x;
		}

		vector& operator=(const vector &x) {
			if (*this != x) {
				while (this->_M_finish != this->_M_start) {
					this->_M_finish--;
					this->_Alloc.destroy(this->_M_finish);
				}

				if (this->_M_start) {
					this->_Alloc.deallocate(this->_M_start, this->capacity());
				}

				pointer p = this->_Alloc.allocate(x.capacity());
				pointer head = p;
				for (size_type i = 0; i < x.size(); i++) {
					this->_Alloc.construct(p, x[i]);
					p++;
				}

				this->_M_start = head;
				this->_M_finish = head + x.size();
				this->_M_end_of_storage = head + x.capacity();
			}
			return *this;
		}

		~vector() {
			if (this->size() <= 0) return ;

			while (this->_M_finish != this->_M_finish) {
				this->_M_finish--;
				this->_Alloc.destroy(this->_M_finish);
			}

			if (this->_M_start) {
				this->_Alloc.deallocate(this->_M_start, this->capacity());
			}

		}

		//iterators

		iterator begin() { return _M_start; }

		const_iterator begin() const { return _M_start; }
		
		iterator end() { return _M_finish; }
		
		const_iterator end() const { return _M_finish; }
		
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		
		reverse_iterator rend() { return reverse_iterator(begin()); }
		
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		//Capacity

		size_type size() const { return this->_M_finish - this->_M_start; }

		size_type max_size() const { return this->_M_end_of_storage - this->_M_start; }

		void resize(size_type n, value_type val = value_type()) {
			if (n < this->size()) {
				pointer p = this->_M_start + n;
				for (size_type i = n; i < this->size(); i++) {
					this->_Alloc.destroy(p);
					*p = 0;
					p++;
				}

				this->_M_finish = this->_M_start + n;
				return ;
			}

			if (n > this->size()) {
				if (n > this->capacity()) {
					size_type old_size = this->size();
					size_type new_size = old_size * 2;
					pointer new_start = this->_Alloc.allocate(new_size);
					pointer p = new_start;
					pointer old_p = this->_M_start;

					for (size_type i = 0; i < old_size; i++) {
						this->_Alloc.construct(p, *old_p);
						old_p++;
						p++;
					}

					old_p = this->_M_start;
					for (size_type i = 0; i < old_size; i++) {
						this->_Alloc.destroy(old_p);
						old_p++;
					}

					if (this->_M_start) {
						this->_Alloc.deallocate(this->_M_start, this->capacity());
					}

					this->_M_start = new_start;
					this->_M_finish = this->_M_start + old_size;
					this->_M_end_of_storage = this->_M_start + new_size;
				}

				for (; this->size() != n; this->_M_finish++) {
					*this->_M_finish = val;
				}
			}
		}

		size_type capacity() const { return this->_M_end_of_storage - this->_M_start; }

		bool empty() const { return this->size() <= 0; }

		void reserve(size_type n) {
			if (n > this->capacity()) {
				size_type old_size = this->size();
				pointer new_start = this->_Alloc.allocate(n);
				pointer new_p = new_start;
				pointer old_p = this->_M_start;

				for (size_type i = 0; i < old_size; i++) {
					this->_Alloc.construct(new_p, *old_p);
					old_p++;
					new_p++;
				}

				old_p = this->_M_start;
				for (size_type i = 0; i < old_size; i++) {
					this->_Alloc.destroy(old_p);
					old_p++;
				}

				if (this->_M_start) {
					this->_Alloc.deallocate(this->_M_start, this->capacity());
				}

				this->_M_start = new_start;
				this->_M_finish = new_start + old_size;
				this->_M_end_of_storage = new_start + n;
			}
		}

		//element access

		reference operator[](size_type n) { return this->_M_start[n]; }
		
		const_reference operator[](size_type n) const { return this->_M_start[n]; }

		reference at(size_type n) {
			if (n >= this->size()) {
				throw std::runtime_error("need to swap to a custom exception");
			}

			return this->_M_start[n];
		}
		
		const_reference at(size_type n) const {
			if (n >= this->size()) {
				throw std::runtime_error("need to swap to a custom exception");
			}

			return this->_M_start[n];
		}
		
		reference front() { return *this->_M_start; }

		const_reference front() const { return *this->_M_start; }

		reference back() { return *this->_M_finish; }
	
		const_reference back() const { return *this->_M_finish; }

		value_type* data() { return this->_M_start; }
		
		const value_type* data() const { return this->_M_start; }

		//modifiers

		void assign(size_type n, const value_type& val) {
			if (n > this->capacity()) {
				while (this->_M_finish != this->_M_start) {
					this->_M_finish--;
					this->_Alloc.destroy(this->_M_finish);
				}

				if (this->_M_start) {
					this->_Alloc.deallocate(this->_M_start, this->capacity());
				}
				this->_M_start = this->_Alloc.allocate(n);
				this->_M_end_of_storage = this->_M_start + n;
			}

			this->_M_finish = this->_M_start + n;
			pointer p = this->_M_start;
			while (p != this->_M_finish) {
				this->_Alloc.construct(p, val);
				p++;
			}
		}

		void push_back (const value_type& val) {
			if (this->_M_finish >= this->_M_end_of_storage) {
				size_type new_size = this->capacity() * 2;
				if (new_size == 0) {
					new_size = 1;
				}
				this->reserve(new_size);
			}

			this->_Alloc.construct(this->_M_finish, val);
			this->_M_finish++;
		}

		void pop_back () {
			this->_M_finish--;
			this->_Alloc.destroy(this->_M_finish);
		}

		iterator insert(iterator position, const value_type& val) {
			size_type pos_index = position - this->_M_start;

			if (this->size() == this->capacity()) {
				size_type new_cap = (this->capacity() * 2) + 1;
				pointer new_start = this->_Alloc.allocate(new_cap);
				pointer new_finish = new_start;

				for (size_type i = 0; i < pos_index; i++) {
					this->_Alloc.construct(new_start + i, this->_M_start[i]);
					new_finish++;
				}

				this->_Alloc.construct(new_start + pos_index, val);
				new_finish++;

				for (size_type i = pos_index; i < this->size(); i++) {
					this->_Alloc.construct(new_finish, this->_M_start[i]);
					new_finish++;
				}

				for (pointer p = this->_M_start; p != this->_M_finish; p++)
					this->_Alloc.destroy(p);
				if (this->_M_start)
					this->_Alloc.deallocate(this->_M_start, this->capacity());

				this->_M_start = new_start;
				this->_M_finish = new_finish;
				this->_M_end_of_storage = new_start + new_cap;

			} else {
				iterator it = this->_M_finish;
				while (it != this->_M_start + pos_index) {
					this->_Alloc.construct(it, *(it - 1));
					it++;
				}
				this->_Alloc.construct(this->_M_start + pos_index, val);
				this->_M_finish++;
			}

			return this->_M_start + pos_index;
		}


		void insert(iterator position, size_type n, const value_type& val) {
			if (n == 0)
				return;

			size_type pos_index = position - this->_M_start;

			if (this->size() + n > this->capacity()) {
				size_type new_cap = (this->capacity() * 2) + 1;
				pointer new_start = this->_Alloc.allocate(new_cap);
				pointer new_finish = new_start;

				for (size_type i = 0; i < pos_index; i++) {
					this->_Alloc.construct(new_start + i, this->_M_start[i]);
					new_finish++;
				}

				for (size_type i = 0; i < n; i++) {
					this->_Alloc.construct(new_start + pos_index + i, val);
					new_finish++;
				}

				for (size_type i = pos_index; i < this->size(); i++) {
					this->_Alloc.construct(new_finish, this->_M_start[i]);
					new_finish++;
				}

				for (pointer p = this->_M_start; p != this->_M_finish; p++)
					this->_Alloc.destroy(p);
				if (this->_M_start)
					this->_Alloc.deallocate(this->_M_start, this->capacity());

				this->_M_start = new_start;
				this->_M_finish = new_finish;
				this->_M_end_of_storage = new_start + new_cap;

			} else {
				for (iterator it = this->_M_finish - 1; it >= this->_M_start + pos_index; it--) {
					this->_Alloc.construct(it + n, *it);
					this->_Alloc.destroy(it);
				}
				for (size_type i = 0; i < n; i++) {
					this->_Alloc.construct(this->_M_start + pos_index + i, val);
				}
				this->_M_finish += n;
			}
		}

		template <class InputIterator>
		typename enable_if<!is_integral<InputIterator>::value, void>::type
		insert(iterator position, InputIterator first, InputIterator last) {
			size_type n = 0;
			for (InputIterator it = first; it != last; ++it)
				n++;

			if (n == 0)
				return;

			size_type pos_index = position - this->_M_start;

			if (this->size() + n > this->capacity()) {
				size_type new_cap = (this->capacity() * 2) + 1;
				pointer new_start = this->_Alloc.allocate(new_cap);
				pointer new_finish = new_start;

				for (size_type i = 0; i < pos_index; ++i) {
					this->_Alloc.construct(new_start + i, this->_M_start[i]);
					new_finish++;
				}

				for (InputIterator it = first; it != last; ++it) {
					this->_Alloc.construct(new_finish, *it);
					new_finish++;
				}

				for (size_type i = pos_index; i < this->size(); ++i) {
					this->_Alloc.construct(new_finish, this->_M_start[i]);
					new_finish++;
				}

				for (pointer p = this->_M_start; p != this->_M_finish; ++p)
					this->_Alloc.destroy(p);
				if (this->_M_start)
					this->_Alloc.deallocate(this->_M_start, this->capacity());

				this->_M_start = new_start;
				this->_M_finish = new_finish;
				this->_M_end_of_storage = new_start + new_cap;

			} else {
				for (iterator it = this->_M_finish - 1; it >= this->_M_start + pos_index; --it) {
					this->_Alloc.construct(it + n, *it);
					this->_Alloc.destroy(it);
				}

				iterator it_pos = this->_M_start + pos_index;
				for (InputIterator it = first; it != last; ++it) {
					this->_Alloc.construct(it_pos, *it);
					it_pos++;
				}

				this->_M_finish += n;
			}
		}


		iterator erase(iterator position) {
			iterator it = position;
			iterator next = position + 1;
			
			while (next != this->_M_finish) {
				*it = *next;
				next++;
				it++;
			}

			this->_M_finish--;
			this->_Alloc.destroy(this->_M_finish);

			return position;
		}
		
		iterator erase(iterator first, iterator last) {
			if (first == last)
				return first;

			iterator it = first;
			iterator move = last;

			while (it != last) {
				this->_Alloc.destroy(it);
				it++;
			}

			it = first;
			while (move != this->_M_finish) {
				this->_Alloc.construct(it, *move);
				this->_Alloc.destroy(move);
				it++;
				move++;
			}

			this->_M_finish = it;
			return first;
		}

		void swap(vector& x) {
			pointer p = this->_M_start;
			this->_M_start = x._M_start;
			x._M_start = p;

			p = this->_M_finish;
			this->_M_finish = x._M_finish;
			x._M_finish = p;

			p = this->_M_end_of_storage;
			this->_M_end_of_storage = x._M_end_of_storage;
			x._M_end_of_storage = p;

			allocator_type _A = this->_Alloc;
			this->_Alloc = x._Alloc;
			x._Alloc = _A;
		}

		void clear() {
			pointer head = this->_M_start;
			while (head != this->_M_finish) {
				this->_Alloc.destroy(head);
				head = 0;
				head++;
			}
			this->_M_finish = this->_M_start;
		}

		//allocator

		allocator_type get_allocator() const { return this->_Alloc; }

		protected:
			pointer _M_start;
			pointer _M_finish;
			pointer _M_end_of_storage;
			allocator_type _Alloc;
	};

	//operator overload

	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		if (lhs.size() == rhs.size()) {
			for (typename  ft::vector<T, Alloc>::size_type i = 0; i < lhs.size(); i++) {
				if (lhs[i] != rhs[i]) {
					return false;
				}
			}
			return true;
		}
		return false;
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		if (lhs == rhs)
			return false;
		return true;
	}

	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		typename  ft::vector<T, Alloc>::size_type lim;
		if (lhs.size() > rhs.size()) 
			lim = rhs.size();
		else
			lim = lhs.size();
		
		for (typename ft::vector<T, Alloc>::size_type i = 0; i < lim; i++) {
			if (lhs[i] < rhs[i])
				return true;
			if (lhs[i] > rhs[i])
				return false;
		}

		if (lhs.size() < rhs.size())
			return true;
		return false;
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		if (lhs < rhs || lhs == rhs)
			return true;
		return false;
	}

	template <class T, class Alloc>
	bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		if (lhs < rhs || lhs == rhs)
			return false;
		return true;
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		if (lhs > rhs || lhs == rhs)
			return true;
		return false;
	}

	template <class T, class Alloc>
	void swap(vector<T,Alloc>& x, vector<T,Alloc>& y) { x.swap(y); }

}

#endif
