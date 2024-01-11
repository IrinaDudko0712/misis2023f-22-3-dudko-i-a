#include <iostream>
using namespace std;
 
int main() {
    int n; cin >> n;
    string str; cin >> str;
    int arr[n], got = false, point = -1, temp;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        if (i < 1) continue;
        if (str[i] == 'L' && str[i - 1] == 'R') {
            temp = (arr[i] + arr[i - 1]) / 2;
            temp -= arr[i - 1];
            
            if (!got) {
                point = temp; got = true;
            } else if (temp < point) point = temp;
            else continue;
        }
    } cout << point << endl;
}
 
