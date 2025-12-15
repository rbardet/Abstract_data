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
				while(p != this->_M_end_of_storage) {
					this->_Alloc.construct(p, val);
					p++;
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

		protected:
			pointer _M_start;
			pointer _M_finish;
			pointer _M_end_of_storage;
			allocator_type _Alloc;
	};
}

#endif
