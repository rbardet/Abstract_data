#include <iostream>
#include "vector.hpp"
#include <vector>

int main() {
	ft::vector<int> my_vector(5, 4);
	std::vector<int> std_vector(5, 4);

	std::cout << "=== Test des valeurs dans les vecteurs ===\n";
	for (size_t i = 0; i < my_vector.size(); ++i) {
		std::cout << "Index " << i << " -> ft::vector: " << my_vector[i]
				  << " | std::vector: " << std_vector[i] << std::endl;
	}

	std::cout << "\n=== Test de la capacity() ===\n";
	std::cout << "ft::vector capacity(): " << my_vector.capacity() << std::endl;
	std::cout << "std::vector capacity(): " << std_vector.capacity() << std::endl;

	std::cout << "\n=== Test de empty() ===\n";
	std::cout << "ft::vector empty(): " << my_vector.empty() << std::endl;
	std::cout << "std::vector empty(): " << std_vector.empty() << std::endl;

	std::cout << "\n=== Test de front() ===\n";
	std::cout << "ft::vector front(): " << my_vector.front() << std::endl;
	std::cout << "std::vector front(): " << std_vector.front() << std::endl;

	std::cout << "\n=== Test de back() ===\n";
	std::cout << "ft::vector back(): " << my_vector.back() << std::endl;
	std::cout << "std::vector back(): " << std_vector.back() << std::endl;

	return 0;
}
