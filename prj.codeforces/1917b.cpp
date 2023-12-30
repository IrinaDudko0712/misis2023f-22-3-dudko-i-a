#include<bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        set<char>st;
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            if (st.find(s[i]) == st.end()) {
                st.insert(s[i]);
                ans += (n - i);
            }
        }
        cout << ans << endl;
    }
}