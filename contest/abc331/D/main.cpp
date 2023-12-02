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

  ll N(0), Q(0);
  cin >> N >> Q;
  string tmp;
  vector<vector<int>> grids(N + 1, vector<int>(N + 1, 0));
  for (int i = 0; i < N; i++) {
    cin >> tmp;
    for (int j = 0; j < int(tmp.length()); j++) {
      if (tmp[j] == 'B') {
        grids[i][j] = 1;
      }
    }
  }
  dump(grids);

  // 繰り返しのマス目なので、いもす法で累積和を取ればいける？
  // X方向の累積和
  for (int i = 1; i < N + 1; i++) {
    for (int j = 1; j < N + 1; j++) {
      grids[i][j] += grids[i][j - 1];
    }
  }
  dump(grids);
  // Y方向の累積和
  for (int j = 1; j < N + 1; j++) {
    for (int i = 1; i < N + 1; i++) {
      grids[i][j] += grids[i - 1][j];
    }
  }
  dump(grids);

  //   cout << exist_points[c][d] + exist_points[a - 1][b - 1] -
  //               (exist_points[a - 1][d] + exist_points[c][b - 1])
  //        << endl;

  ll A(0), B(0), C(0), D(0);

  for (int i = 0; i < Q; i++) {
    cin >> A >> B >> C >> D;
    // 1. ABCDの範囲がNより大きい場合
    //    →(A, B), (C, D), (A, D), (C, B)で累積和を計算する
    //     Nマスごとの累積和は計算済みなので、商×N

    cout << grids[C - 1][D - 1] + grids[A - 2][B - 2] -
                (grids[A - 2][D - 1] + grids[C - 1][B - 2])
         << endl;
  }
}
