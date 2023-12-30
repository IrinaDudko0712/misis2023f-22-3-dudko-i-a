#include <iostream>
#include <string>
int main() {
	int t;
	std::string s;
	std::cin >> t;
	while (t--) {
		std::cin >> s;
		bool stoppoint = 1;
		int n = s.length();
		int a = n - 1;
		int b = 0;
		for (int i = 0; i < n; i++) {
			if (s[i] == '0') {
				a = i;
				break;
			}
		}
		for (int m = n - 1; m >= 0; m--) {
			if (s[m] == '1') {
				b = m;
				break;
			}
		}
		int answers = a - b + 1;
		std::cout << answers << std::endl;
	}
}