#include <iostream>
#include<cmath>
int main() {
	int t;
	std::cin >> t;
	while (t--) {
		int n;
		std::cin >> n;
		char c;
		std::cin >> c;
		std::string s;
		std::cin >> s;
		s = s + s;
		if (c == 'g') {
			std::cout << 0 << std::endl;
		}
		else {
			int sim = 2 * n;
			int results = 0;
			for (int i = 2 * n - 1; i >= 0; --i) {
				if (s[i] == c) {
					results = fmax(results, sim - i);
				}
				if (s[i] == 'g') {
					sim = i;
				}
			}
			std::cout << results << std::endl;
		}
	}
}