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

// 問題の制約条件により、価値の最大値は以下の通り
constexpr int MAX_VALUE = 1000 * 100;

int main() {
  // set precision (10 digit)
  cout << setprecision(10);
  ll N(0), W(0);
  cin >> N >> W;

  for (int i = 1; i < N + 1; i++) {
    cin >> Weights[i] >> Values[i];
  }
  // i番目までの宝物を選択する/しないをした時に価値jを作れる時の最小の重さ
  // 初期値を非常に大きい値にしておくと、選べないパターンの場合分けをせずにすむ
  vector<vector<ll>> DP(N + 1, vector<ll>(MAX_VALUE + 1, 1000000000000000));

  DP[0][0] = 0;
  // Note:
  // 本問題のポイントは、制約条件からDPで何を管理するかを考察すること
  // →二次元DPだと、O(NW)なのでこのNとWに何を設定するかで計算が制約条件内に完了するか決まってくるので、
  //  それに応じて決める。A19の問題と「重量の最大値」と「価値の最大値」が異なるので、少ない方でループを回せる様に選定する
  for (int i = 1; i < N + 1; i++) {
    // ここの開始インデックスをミスって1スタートにしてハマっていた
    // for (int j = 1; j < W + 1; j++) {
    for (int j = 0; j < MAX_VALUE + 1; j++) {
      // i番目の宝物を選ばないパターン
      if (j < Values[i]) {
        DP[i][j] = DP[i - 1][j];
      } else {
        // 他の宝物と組み合わせて選ぶパターン
        DP[i][j] =
            std::min(DP[i - 1][j - Values[i]] + Weights[i], DP[i - 1][j]);
      }
    }
  }
  ll max = 0;
  for (ll i = 0; i <= MAX_VALUE; i++) {
    if (DP[N][i] <= W) max = std::max(max, i);
  }
  cout << max << endl;
}