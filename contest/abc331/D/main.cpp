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

// f(A,B,C,D)= (A≤h<C,B≤w<D を満たす範囲にあるマス (h,w)
// のうち黒マスであるマスの個数)
//  C、Dが開区間になっている事に注意
ll CountBlackPoints(const ll C, const ll D, const ll N,
                    const vector<vector<int>>& grids) {
  // 一般に、マス目全体を特定の領域で切り出した形状は以下の4種類
  // ・A→与えられたグリッドと同じ形状(N×N)
  // ・B→幅: 与えられたグリッドと同じ、高さ: D % N (N×[D % N])
  // ・C→幅: C % N、高さ: 与えられたグリッドと同じ ([C % N]×N)
  // ・D→幅: C % N、高さ: D % N ([C % N]×[D % N])
  //
  //  --------------------------
  // |         |         |      |
  // |   (A)   |   (A)   |  (C) |
  // |         |         |      |
  // |--------------------------
  // |         |         |      |
  // |   (A)   |   (A)   |  (C) |
  // |         |         |      |
  // |--------------------------
  // |         |         |      |
  // |   (B)   |   (B)   |  (D) |
  // |--------------------------(C, D)

  // どのインデックスもN×N以下のため、全体の領域から小さい領域を引くなどは不要なのだと考えられる
  // 領域D
  ll res = grids[C % N][D % N];
  // 領域A
  res += grids[N][N] * (C / N) * (D / N);
  // 領域B
  res += grids[N][D % N] * (C / N);
  // 領域C
  res += grids[C % N][N] * (D / N);

  return res;
}

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
        grids[i + 1][j + 1] = 1;
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

  ll A(0), B(0), C(0), D(0);

  // ポイント1. 愚直にやると、f(A,B,C,D)= (A≤h<C,B≤w<D を満たす範囲にあるマス
  // (h,w)のうち黒マスであるマスの個数)を直接求める事になるが、これはパラメータが4つあり、中々大変である。
  // そこで、以下の様に目的の領域(d)に含まれる黒点の個数を求める事で、パラメータを4→2に減らす事ができる
  // →左上の頂点を(0,0)とし、右下の頂点のみパラメータとした領域の足し引きで考える
  //
  //  ・{目的の領域(d)に含まれる黒点の個数} =
  // {(0,0)から(C,D)までに含まれる黒点の個数}+{(0,0)から(A,B)までに含まれる黒点の個数}
  // -{(0,0)から(C,B)までに含まれる黒点の個数}-{(0,0)から(A,D)までに含まれる黒点の個数}
  // ※(0,0)から(A,B)の領域が2回引かれるので、辻褄合わせに足す必要がある
  //
  // (0,0)   (A, 0)      (C, 0)
  //  --------------------
  // |        |          |
  // |   (a)  |    (b)   |
  // |        | (A, B)   | (C, B)
  // |--------------------
  // |   (c)  |    (d)   |
  // |        |          |
  // |--------------------
  //         (A, D)      (C, D)

  for (int i = 0; i < Q; i++) {
    cin >> A >> B >> C >> D;
    // ポイント2. f()の定義より、右下の座標は+1してやる必要がある
    C++;
    D++;
    // ポイント3. 愚直に全マス(10^9×10^9)を計算すると間に合わないので、
    //           周期性を利用する。
    //           CountBlackPoints()を読むと分かる様に、左上(0,0)、右下(C,D)となる領域を
    //           分割すると高々4種類の長方形しかできない(幅の選び方と高さの選び方がそれぞれ2種類しかないため)。
    //           また、各長方形の個数は、領域のサイズとグリッドのサイズの剰余から求める事ができる
    cout << CountBlackPoints(C, D, N, grids) +
                CountBlackPoints(A, B, N, grids) -
                CountBlackPoints(A, D, N, grids) -
                CountBlackPoints(C, B, N, grids)
         << endl;
  }
}
