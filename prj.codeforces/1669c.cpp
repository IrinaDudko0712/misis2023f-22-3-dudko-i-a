#include <iostream>
#include <string>
#include <map>
int main() {
	int t = 1;
	std::cin >> t;
	while (t--) {
		int n;
		std::cin >> n;
		std::string a;
		std::cin >> a;
		int Redline = 0, Blueline = 0;
		int answer = 0;
		for (int i = 0; i < n; i++) {
			if (a[i] == 'R') {
				Redline = 1;
			}
			if (a[i] == 'B') {
				Blueline = 1;
			}
			if (a[i] == 'W') {
				if (Redline + Blueline == 1) {
					answer = 1;
					break;
				}
				Redline = 0;
				Blueline = 0;
			}
		}
		if (answer == 1 || Redline + Blueline == 1)
			std::cout << "NO" << std::endl;
		else
			std::cout << "YES" << std::endl;

	}
}