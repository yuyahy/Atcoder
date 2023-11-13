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
  int H(0), W(0);
  cin >> H >> W;
  dump(H);
  dump(W);
  vector<vector<char>> grids(H, vector<char>(W, 0));
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      cin >> grids[i][j];
    }
  }
  dump(grids);

  // (1, 1)から(i, j)までに辿りつくまでの経路の数
  vector<vector<ll>> DP(H, vector<ll>(W, 0));
  // 初期状態
  DP[0][0] = 1;
  dump(DP);
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      // 遷移
      // 貰う式で考える
      // (i ,j)にたどり着くのは以下の2パターン
      // 1. (i-1, j)から下に1マス移動する
      // 2. (i, j-1)から右に1マス移動する
      // ※ただし、「#」のマスからは移動できない
      if (i > 0 && grids[i - 1][j] != '#') {
        DP[i][j] += DP[i - 1][j];
      }
      if (j > 0 && grids[i][j - 1] != '#') {
        DP[i][j] += DP[i][j - 1];
      }
    }
  }
  dump(DP);
  cout << DP[H - 1][W - 1] << endl;
}
