#include <bits/stdc++.h>

#include <atcoder/all>
using namespace atcoder;
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

// mint
using mint = static_modint<1000000007>;
// ll int
ll INF = numeric_limits<ll>::max() / 2;

int main() {
  // set precision (10 digit)
  cout << setprecision(10);
  int n(0), x(0);

  cin >> n >> x;
  auto tmp = 0;
  auto bFind = false;
  for (auto i = 0; i < n; i++) {
    cin >> tmp;
    if (tmp == x) {
      bFind = true;
      break;
    }
  }
  auto result_str = bFind ? "Yes" : "No";
  cout << result_str << endl;
}
