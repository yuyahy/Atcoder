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
  int N(0), A(0), B(0), C(0), D(0);
  cin >> N;
  constexpr int GRID_SIZE = 1501;
  vector<vector<int>> grids(GRID_SIZE + 1, vector<int>(GRID_SIZE + 1, 0));
  for (int i = 0; i < N; i++) {
    cin >> A >> B >> C >> D;
    // 紙が置かれている内部のみが+1される様なインデックスを+1し、累積和をとった時にその外部を打ち消す様なインデックスを-1する
    grids[C + 1][D + 1] += 1;
    grids[A + 1][B + 1] += 1;
    grids[C + 1][B + 1] += -1;
    grids[A + 1][D + 1] += -1;
  }

  // 行方向の累積和を求める
  for (int i = 1; i < GRID_SIZE + 1; i++) {
    for (int j = 1; j < GRID_SIZE + 1; j++) {
      grids[i][j] += grids[i][j - 1];
    }
  }
  // 列方向の累積和を求める
  for (int j = 1; j < GRID_SIZE + 1; j++) {
    for (int i = 1; i < GRID_SIZE + 1; i++) {
      grids[i][j] += grids[i - 1][j];
    }
  }
  // 紙が少なくとも1枚置かれているセルをカウントし、面積とする
  // →サンプルケースが紙が重なっているケースだったが、重なっている物は1としてカウントしていたため
  int cnt = 0;
  for (int i = 1; i < GRID_SIZE + 1; i++) {
    for (int j = 1; j < GRID_SIZE + 1; j++) {
      if (grids[i][j] != 0) cnt++;
    }
  }
  cout << cnt << endl;
}
