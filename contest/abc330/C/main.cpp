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

  ll D(0);
  cin >> D;
  //   double tmp = D;
  //   ll r = tmp;
  //   dump(r);
  ll y(0);
  ll min(100000000000000);
  dump(std::round(sqrt(D)));

  // Note: x < sqrt(D)だと拾えきれないケースがあるので+1まで調べる
  // for (ll x = 0; x < sqrt(D) + 1; x++) {
  //   // y^2 + (x^2 - D) を最小化する
  //   if (x * x - D >= 0) {
  //     // (x^2 - D)が0以上であれば、y=0で最小にできる
  //     y = 0;
  //     min = std::min(min, abs(x * x + y * y - D));
  //   } else {
  //     // (x^2 - D)が0未満であれば、y^2 = abs(x^2 - D)が最小にできる
  //     auto y_tmp = sqrt(D - x * x);
  //     ll res1 = std::ceil(y_tmp) * std::ceil(y_tmp) + (x * x - D);
  //     ll res2 = std::floor(y_tmp) * std::floor(y_tmp) + (x * x - D);

  //     if (abs(res2) < abs(res1)) {
  //       min = std::min(min, abs(res2));
  //     } else {
  //       min = std::min(min, abs(res1));
  //     }each
  //   }
  // }
  // dump(y);

  // 方針2: 平方数のテーブルを作成しておき、この配列を利用して解く
  //        →この方針だとXを決める時のループで、Dの√の+1まで調べるなどの気づきは必要なくなる

  // Dの制約より、2乗してDの最大値を少し超えるくらいの値を設定しておく
  // constexpr ll max = 2e6;
  // // 平方数の配列を作っておく
  // vector<ll> square_vec;
  // for (ll i = 0; i <= max; i++) {
  //   square_vec.push_back(i * i);
  // }
  // dump(square_vec.size());
  // //
  // X^2、Y^2のありうる値はsquare_vecのいずれかの値なので、X^2を固定して探索する
  // // ※配列のサイズ的に2重ループで総当りだと間に合わない
  // for (const auto& x : square_vec) {
  //   // (X^2-D)+Y^2を最小化する様なY^2の値を探す
  //   if (x - D >= 0) {
  //     // これは明らか
  //     y = 0;
  //   } else {
  //     // (X^2-D)が負の場合は、その絶対値に最も近いY^2の値が答え
  //     //
  //     上述の通り、総当りでは間に合わないので二分木探索を活用し、得られたイテレータと、
  //     // その一個前のイテレータの内、与えられた式を最小化する方を採用する
  //     // 1. lower_boundした結果が(X^2-D)と等しければそのまま採用
  //     // 2.
  //     lower_boundした結果が(X^2-D)と等しくない場合は、一個前の要素の方がより近い値の可能性がある
  //     auto tmp =
  //         (lower_bound(square_vec.begin(), square_vec.end(), abs(x - D)));
  //     y = (abs(x + *tmp - D) < abs(x + *(tmp - 1) - D)) ? *tmp : *(tmp - 1);
  //   }
  //   min = std::min(min, abs(x + y - D));
  // }

  // 方針3: しゃくとり法
  // →設問の条件より中心(0,0)、半径√Dの円に最も近い格子点を求める事に等しい
  //  よって、第一象限の円弧の近くの格子点を探索し、最も円弧との距離が近い点を探す
  y = 0;
  ll x(2e6);
  // Note: 第一象限の円弧なので、
  // 左上から右下 or その逆の方向に探索していく必要がある
  for (ll y = 0; y < 2e6; ++y) {
    // int y = x;
    while (x >= 0 && (y * y + x * x > D)) {
      /* 実際に y を 1 進める */
      // ex: sum += a[y];
      --x;
    }
    /* break した状態で y は条件を満たす最大なので、何かする */
    // ex: res += (y - x);

    // 格子点なので、一応周辺の4頂点全てを調べておく
    // →少なくともy+1も見ないと一部のケースで失敗する
    min = std::min(min, abs(y * y + x * x - D));
    min = std::min(min, abs(y * y + (x + 1) * (x + 1) - D));
    min = std::min(min, abs((y + 1) * (y + 1) + x * x - D));
    min = std::min(min, abs((y + 1) * (y + 1) + (x + 1) * (x + 1) - D));
  }
  dump(x);
  dump(y);
  cout << min << endl;
}
