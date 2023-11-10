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
  int N(0), M(0);
  cin >> N >> M;
  vector<vector<int>> coupon(M + 1, vector<int>(N + 1, 0));
  for (int i = 1; i <= M; i++) {
    for (int j = 1; j <= N; j++) {
      cin >> coupon[i][j];
    }
  }
  dump(coupon);
  // i番目までのクーポンの中から何枚か使ってj番目までの品物を買うときのクーポンの最小枚数
  vector<vector<int>> DP(M + 1, vector<int>((1 << N), 100000000));
  DP[0][0] = 0;
  for (int i = 1; i <= M; i++) {
    for (int j = 0; j < (1 << N); j++) {
      // j番目までの商品の選び方の集合を10進数→2進数で桁が0 or 1かを判定する
      // 品物kが既に無料の場合は、already[k] = 1
      int already[19];
      for (int k = 1; k <= N; k++) {
        if ((j / (1 << (k - 1))) % 2 == 0) {
          already[k] = 0;
        } else {
          already[k] = 1;
        }
      }
      // クーポンiを選んだ場合の集合の整数表現vを計算
      // →先頭から、下位の桁として10進数表現にする
      auto v(0);
      for (int k = 1; k <= N; k++) {
        if (already[k] == 1 || coupon[i][k] == 1) {
          v += (1 << (k - 1));
        }
      }

      // 配る式DPを考えると、状態DP[i-1][S]から遷移する状態は以下の2通り
      // ・クーポンiを使う場合
      //   → DP[i][S+Tiの和集合] = min(DP[i-1][S] +1,DP[i][S+Tiの和集合])
      // ・クーポンiを使わない場合
      //   → DP[i][S] =min(DP[i-1][S], DP[i][S])
      DP[i][v] = std::min(DP[i - 1][j] + 1, DP[i][v]);
      DP[i][j] = std::min(DP[i - 1][j], DP[i][j]);
    }
  }
  auto result(0);
  if (DP[M][(1 << N) - 1] == 100000000) {
    result = -1;
  } else {
    result = DP[M][(1 << N) - 1];
  }
  dump(DP);
  cout << result << endl;
}
