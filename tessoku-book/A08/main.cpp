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
  // Note:
  // 行と列、多次元配列の対応関係に注意すること(そのミスの修正に結構時間を使った)
  vector<vector<int>> grids(H + 1, vector<int>(W + 1, 0));

  int tmp(0);
  for (int i = 1; i < H + 1; i++) {
    for (int j = 1; j < W + 1; j++) {
      cin >> tmp;
      grids[i][j] = tmp;
    }
  }

  auto accum_row = grids;
  // 以下の方向ごとの累積和の計算の順番は入れ替えてもOKそう
  // 行方向に累積和を求める
  for (int i = 1; i < H + 1; i++) {
    for (int j = 1; j < W + 1; j++) {
      accum_row[i][j] += accum_row[i][j - 1];
    }
  }
  // 列方向に累積和を求める
  for (int j = 1; j < W + 1; j++) {
    for (int i = 1; i < H + 1; i++) {
      accum_row[i][j] += accum_row[i - 1][j];
    }
  }

  // 質問に答える
  int Q(0), A(0), B(0), C(0), D(0);
  cin >> Q;
  for (int i = 0; i < Q; i++) {
    cin >> A >> B >> C >> D;
    cout << (accum_row[C][D] + accum_row[A - 1][B - 1]) -
                (accum_row[A - 1][D] + accum_row[C][B - 1])
         << endl;
  }
}
