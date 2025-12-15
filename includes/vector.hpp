#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <stdexcept>

// i refer to cpp.com
// https://cplusplus.com/reference/vector/vector/

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
				this->_M_start = _Alloc.allocate(n);
				this->_M_finish = this->_M_start;
				this->_M_end_of_storage = this->_M_start + n;
				pointer p = this->_M_start;
				for(; p != this->_M_end_of_storage; p++) {
					this->_Alloc.construct(p, val);
					this->_M_finish++;
				}
			}
		}

		vector& operator=(const vector &x) {
			if (*this != &x) {

			}
			return *this;
		}

		~vector() {
			if (this->size() <= 0) return ;

			pointer p = this->_M_start;
			while (p != this->_M_finish) {
				this->_Alloc.destroy(p);
				p++;
			}

			if (this->_M_start) {
				this->_Alloc.deallocate(this->_M_start, this->capacity());
			}
		}

		//Capacity

		size_type size() const {
			return this->_M_finish - this->_M_start;
		}

		size_type max_size() const {
			return this->_M_end_of_storage - this->_M_start;
		}

		void resize(size_type n, value_type val = value_type()) {
			(void)n, val;
		}

		size_type capacity() const {
			return this->_M_end_of_storage - this->_M_start;
		}

		bool empty() const {
			return this->size() <= 0;
		}

		void reserve(size_type n) {
			if (n > this->capacity()) {
				size_type old_size = this->size();
				pointer new_start = _Alloc.allocate(n);
				pointer new_p = new_start;
				pointer old_p = _M_start;

				for (size_type i = 0; i < old_size; i++) {
					_Alloc.construct(new_p, *old_p);
					old_p++;
					new_p++;
				}

				old_p = _M_start;
				for (size_type i = 0; i < old_size; i++) {
					_Alloc.destroy(old_p);
					old_p++;
				}

				if (_M_start) {
					_Alloc.deallocate(_M_start, _M_end_of_storage - _M_start);
				}

				_M_start = new_start;
				_M_finish = new_start + old_size;
				_M_end_of_storage = new_start + n;
			}
		}

		//element access

		reference operator[](size_type n) {
			return this->_M_start[n];
		}
		
		const_reference operator[](size_type n) const {
			return this->_M_start[n];
		}

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
		
		reference front() {
			return *this->_M_start;
		}

		const_reference front() const {
			return *this->_M_start;
		}

		reference back() {
			return *(this->_M_finish - 1);
		}
	
		const_reference back() const {
			return *(this->_M_finish - 1);
		}

		value_type* data() {
			return this->_M_start;
		}
		
		const value_type* data() const {
			return this->_M_start;
		}

		//modifiers

		void push_back (const value_type& val) {
			if (this->_M_finish >= this->_M_end_of_storage) {
				size_type new_size = this->capacity() * 2;
				if (new_size == 0) {
					new_size = 2; 
				}
				this->reserve(new_size);
			}

			std::cout << this->_M_finish << std::endl;
			std::cout << this->_M_end_of_storage << std::endl;
			*this->_M_finish = val;
			this->_M_finish++;
		}

		//allocator

		allocator_type get_allocator() const {
			return this->_Alloc;
		}

		protected:
			pointer _M_start;
			pointer _M_finish;
			pointer _M_end_of_storage;
			allocator_type _Alloc;
	};
}

#endif
