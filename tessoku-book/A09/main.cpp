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

  int H(0), W(0), N(0);
  cin >> H >> W >> N;
  // Note:
  // 行と列、多次元配列の対応関係に注意すること(以前そのミスの修正に結構時間を使った)
  // 累積和の計算と、右下の与えられた座標の更に右下を使う関係で幅・高さを2つ大きめに取っている
  vector<vector<int>> grids(H + 2, vector<int>(W + 2, 0));

  int A(0), B(0), C(0), D(0);
  for (int k = 0; k < N; k++) {
    cin >> A >> B >> C >> D;
    // 縦方向と横方向で累積和を計算したときに、(A, B)と(C,D)
    // がなす矩形の内部のセルのみが+1で埋まる様に記録する
    // Note:
    // A08の様に、記録すべきインデックスが設問によって異なるが、そこの判断の方法が分かっていない。
    // ただ、原理を考えると、今回は左上の点は計算したい矩形の内部に入っていないと、
    // 矩形外のセルも加算されてしまうので、そこがインデックス選びのポイントかもしれない(簡単なケースで手で書いた方が良いかも)
    // ※同様にA08の場合は、矩形の右下が矩形の内部にないと、意図した累積和を算出できないと思う
    grids[C + 1][D + 1] += 1;
    grids[A][B] += 1;
    grids[C + 1][B] -= 1;
    grids[A][D + 1] -= 1;
    // 愚直にやるなら、ここで(A、B)〜(C、D)のマス目をインクリメント
    // for (int i = A; i < C + 1; i++) {
    //   for (int j = B; j < D + 1; j++) {
    //     grids[i][j] += 1;
    //   }
    // }
  }
  // X方向の累積和を求める
  for (int i = 1; i < H + 1; i++) {
    for (int j = 1; j < W + 1; j++) {
      grids[i][j] += grids[i][j - 1];
    }
  }
  // Y方向の累積和を求める
  for (int j = 1; j < W + 1; j++) {
    for (int i = 1; i < H + 1; i++) {
      grids[i][j] += grids[i - 1][j];
    }
  }
  // 各マスの積雪量を出力する
  for (int i = 1; i < H + 1; i++) {
    for (int j = 1; j < W + 1; j++) {
      auto suffix = j == W ? "" : " ";
      cout << grids[i][j] << suffix;
    }
    cout << endl;
  }
}