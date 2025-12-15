#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>

// i refer to cpp.com
// https://cplusplus.com/reference/vector/vector/

namespace ft {
	template<typename T>
	class vector {
		private:
			T *start;
			T *end;
			T *storage_end;
		public:
		typedef T value_type;
		typedef &T reference;
		typedef const &T const_reference;
		typedef size_t size_type;


			vector() {};

			vector& operator=(const vector &src) {
				if (*this != &src) {

				}
				return *this;
			}
			~vector() {}

			//Capacity
			size_type size() const {
				return this.end - this.start;
			}

			size_type max_size() const {
				return this.storage_end - this.start;
			}



			//element access
			reference operator[] (size_type n) {
				return this.start[n];
			}
			
			const_reference operator[] (size_type n) const {
				return this.start[n];
			}

	};
}

#endif
