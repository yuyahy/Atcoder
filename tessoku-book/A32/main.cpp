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
  int N(0), A(0), B(0);
  cin >> N >> A >> B;
  // Note: 残りの個数が少ないものから、勝ちの手が作れるかを考えていき、
  //       遡った結果がtrueであれば先手必勝である
  // N個目で勝ちの状態を作れるか
  vector<bool> DP(N + 1, false);

  for (int i = 0; i <= N; i++) {
    // A or Bの操作で相手が負けの状態を作れれば勝利
    if ((i - std::min(A, B) >= 0 && !DP[i - std::min(A, B)]) ||
        (i - std::max(A, B) >= 0 && !DP[i - std::max(A, B)])) {
      DP[N] = true;
    } else {
      // それ以外は負け
      DP[N] = false;
    }
  }
  auto result = DP[N] ? "First" : "Second";
  cout << result << endl;
}
