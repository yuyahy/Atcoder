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

  vector<ll> P(N + 2, 0), A(N + 2, 0);
  for (int i = 1; i < N + 1; i++) {
    cin >> P[i] >> A[i];
  }
  dump(P);
  dump(A);

  vector<vector<ll>> DP(N + 1, vector<ll>(N + 1, 0));
  // l番目からr番目までのブロックが残っている状態を考え、この状態になるまでに
  // 稼げる最大点を動的計画法で求めていく
  for (int length = N - 2; length >= 0; length--) {
    for (int left = 1; left <= N - length; left++) {
      auto right = left + length;
      dump(right);
      dump(left);
      // 状態(l, r)に遷移する直前は以下の2パターン
      // ・左のl-1番目のブロックを削除する
      // ・左のr+1番目のブロックを削除する
      auto left_score =
          (P[left - 1] >= left && P[left - 1] <= right) ? A[left - 1] : 0;
      auto right_score =
          (P[right + 1] >= left && P[right + 1] <= right) ? A[right + 1] : 0;
      if (left == 1) {
        DP[left][right] = DP[left][right + 1] + right_score;
      } else if (right == N) {
        DP[left][right] = DP[left - 1][right] + left_score;
      } else {
        DP[left][right] = std::max(DP[left - 1][right] + left_score,
                                   DP[left][right + 1] + right_score);
      }
      dump(DP[left][right]);
    }
  }
  dump(DP);
  ll result(0);
  for (int i = 0; i < N + 1; i++) {
    result = std::max(result, DP[i][i]);
  }
  cout << result << endl;
}
