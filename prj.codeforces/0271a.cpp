#include <iostream>
int main() {
	int year, a, b, c, d;
	std::cin >> year;
	while (true) {
		year += 1;
		a = year / 1000;
		b = (year / 100) % 10;
		c = (year / 10) % 10;
		d = year % 10;
		if (a != b && b != c && c != d && a != c && a != d && b != d)
			break;
	}
	std::cout << year << std::endl;
}
