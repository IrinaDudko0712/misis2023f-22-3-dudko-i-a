#include <iostream>
#include<math.h>
int main() {
	int t = 0;
	std::cin >> t;
	for (int r = 0; r < t; r+=1 ) {
		int n = 0;
		std::cin >> n;
		int k = 0;
		std::cin >> k;
		std::string s;
		std::cin >> s;
		int Blackstring = 0;//черные клетки в строке
		int Whitestring = 0;//белые клетки в строке
		for (int i = 0; i < k; i+=1) {
			if (s[i] == 'W') {
				Whitestring+=1;
			}
			else {
				Blackstring+=1;
			}
		}
		int answers = Whitestring;//минимальное количество белых клеток которые нужно перекрасить в черный
			for (int a = k; a < n; a+=1) {//это и есть ответ на задачу//k-черные клетки
				if (s[a] == 'W') {
					Whitestring+=1;
				}
				else {
					Blackstring+=1;
				}
				if (s[a - k] == 'W') {
					Whitestring-=1;
				}
				else {
					Blackstring-=1;
				}
				answers =std::min(answers, Whitestring);
			}		                   
		std::cout << answers << std::endl;
	}
 }