#include <bits/stdc++.h>
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<vector<int>> adj(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  double ans = 0.0;
  auto dfs = [&](int node, int p, int d, auto&& dfs) -> void {
    ans += 1.0 / d;
    for (int next : adj[node]) {
      if (next != p) {
        dfs(next, node, d + 1, dfs);
      }
    }
  };
  dfs(0, -1, 1, dfs);
  cout << fixed << setprecision(10) << ans << '\n';
  return 0;
}
