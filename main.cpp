#include <iostream>

int makex() {
	return 1;
}

int usex(const int& x) {
	return x;
}

int main() {
	std::cout << "usex(x) = " << usex(makex()) << std::endl;
	return 0;
}