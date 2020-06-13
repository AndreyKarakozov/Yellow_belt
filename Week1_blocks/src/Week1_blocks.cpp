#include <iostream>
#include <cinttypes>

int main() {
	int number_of_blocks, dencity;
	std::cin >> number_of_blocks >> dencity;

	uint64_t mass = 0;
	for (int i = 0; i < number_of_blocks; ++i) {
		int width, heigth, depth;
		std::cin >> width >> heigth >> depth;
		mass += static_cast<uint64_t>(width) * heigth * depth;
	}
	mass *= dencity;
	std::cout << mass;

	return 0;
}
 /*
  1 10000000
  10000 10000 10000


  */
