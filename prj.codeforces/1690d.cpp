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
		int Blackstring = 0;//������ ������ � ������
		int Whitestring = 0;//����� ������ � ������
		for (int i = 0; i < k; i+=1) {
			if (s[i] == 'W') {
				Whitestring+=1;
			}
			else {
				Blackstring+=1;
			}
		}
		int answers = Whitestring;//����������� ���������� ����� ������ ������� ����� ����������� � ������
			for (int a = k; a < n; a+=1) {//��� � ���� ����� �� ������//k-������ ������
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