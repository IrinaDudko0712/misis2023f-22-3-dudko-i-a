#include <bits/stdc++.h>
 
using ll = long long;
using namespace std;
 
// Functions
bool is_prime(int n){
	if (n <= 2) return n == 2;
	if (n % 2 == 0) return false;
	for (int i = 3; i * i <= n; i += 2){
		if (n % i == 0) return false;
	}
	return true;
}
 
void solve(){
	int n; cin >> n;	
	vector<int> a(n);
	vector<int> b;
	int res = 0;
	for (int &x : a){
		cin >> x;
	}
	for (auto x: a){
		if (x % 2 == 0) b.push_back(x);
	}
	for (auto x: a){
		if (x % 2 != 0) b.push_back(x);
	}
	for (int i = 0; i < n - 1; i++){
		if (b[i] % 2 == 0) res += n - 1 - i;
		else{
			for (int j = i + 1; j < n; j++){
				if (gcd(b[i], 2 * b[j]) > 1) res++;
			}
		}
	}
 
	cout << res << '\n';
}
 
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int t; cin >> t;
	while(t--){
		solve();
	}
	return 0;
}
