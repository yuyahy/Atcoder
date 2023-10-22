// デバッグ用関数の設定
#ifdef DEFINED_ONLY_IN_LOCAL
#include </workspaces/atcoder/cpp-dump/dump.hpp>
#define dump(...) CPP_DUMP(__VA_ARGS__)
#else
#define dump(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT(...)
#endif

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

  int N(0);
  cin >> N;
  vector<int> W(N, 0), X(N, 0);
  for (int i = 0; i < N; i++) {
    cin >> W[i] >> X[i];
  }
  ll max = 0;
  for (int i = 0; i < 24; i++) {
    ll attendence = 0;
    for (int j = 0; j < N; j++) {
      int local_time = 0;
      if (X[j] + i <= 23) {
        local_time = X[j] + i;
      } else {
        local_time = X[j] + i - 24;
      }
      if (local_time >= 9 && local_time + 1 <= 18) {
        attendence += W[j];
        // dump(local_time);
        // dump(i);
        // dump(X[j]);
      }
    }
    max = std::max(max, attendence);
  }
  cout << max << endl;
}
