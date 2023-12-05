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

  ll X(0), Y(0);
  cin >> X >> Y;

  vector<pair<ll, ll>> K;
  // Note:
  // 最初迷走してしまったが[5,7]や[13,17]などの単純なケースを考える事によって正解に漕ぎ着けた。
  //       ポイントは、X, Yから逆に X-Y or Y-Xしていって[1,
  //       1]に戻す方法を考えること。
  while (X != Y) {
    K.push_back({X, Y});
    if (X > Y) {
      X = X - Y;
    } else {
      Y = Y - X;
    }
  }

  cout << K.size() << endl;
  for (int i = K.size() - 1; i >= 0; i--) {
    cout << K[i].first << " " << K[i].second << endl;
  }
}
