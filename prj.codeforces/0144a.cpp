#include <iostream>
using namespace std;
 
int main() {
    int t;
    cin >> t;
    int max = 0;
    int min = 101;
    int maxpos = 0;
    int minpos = 0;
 
    for (int i = 1; i <= t; i++) {
        int n;
        cin >> n;
 
        if (n > max) {
            max = n;
            maxpos = i;
        }
 
        if (n <= min) {
            min = n;
            minpos = i;
        }
    }
    if (maxpos > minpos) {
        cout << (maxpos)+(t - 2 -minpos) << endl;
    }
    else {
        cout << (maxpos)+(t - ++minpos) << endl;
    }
    
    return 0;
}
