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

// ll DP[109][100009];
vector<ll> Weights(109, 0), Values(109, 0);

int main() {
  // set precision (10 digit)
  cout << setprecision(10);
  ll N(0), W(0);
  cin >> N >> W;

  for (int i = 1; i < N + 1; i++) {
    cin >> Weights[i] >> Values[i];
  }
  // i番目までの宝物を選択する/しないをした時の最大の価値
  // 初期値を非常に小さい値にしておくと、選べないパターンの場合分けをせずにすむ
  vector<vector<ll>> DP(N + 1, vector<ll>(W + 1, -1000000000000000));

  DP[0][0] = 0;
  for (int i = 1; i < N + 1; i++) {
    // ここの開始インデックスをミスって1スタートにしてハマっていた
    // for (int j = 1; j < W + 1; j++) {
    for (int j = 0; j < W + 1; j++) {
      // i番目の宝物を選ばないパターン
      if (j < Weights[i]) {
        DP[i][j] = DP[i - 1][j];
      } else {
        // 他の宝物と組み合わせて選ぶパターン
        DP[i][j] =
            std::max(DP[i - 1][j - Weights[i]] + Values[i], DP[i - 1][j]);
      }
    }
  }
  ll max = 0;
  for (int i = 0; i <= W; i++) {
    max = std::max(max, DP[N][i]);
  }
  cout << max << endl;
}