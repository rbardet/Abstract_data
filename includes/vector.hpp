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

	};
}

#endif
