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

// nCk、組み合わせを求める関数
//
// usage:
// vector<vector<ll> > v(n + 1, vector<ll>(n + 1, 0));
// comb(v);
// v[n][k]が求めるnCkの値
void comb(vector<vector<ll>>& v) {
  for (ll i = 0; i < (ll)v.size(); i++) {
    v[i][0] = 1;
    v[i][i] = 1;
  }
  for (ll k = 1; k < (ll)v.size(); k++) {
    for (ll j = 1; j < k; j++) {
      v[k][j] = (v[k - 1][j - 1] + v[k - 1][j]);
    }
  }
}

// mint
using mint = static_modint<1000000007>;
// ll int
ll INF = numeric_limits<ll>::max() / 2;

int main() {
  // set precision (10 digit)
  cout << setprecision(10);
  int N(0);
  cin >> N;
  constexpr int divide = 100;
  // <Aiを100で割った余り、{Aiのインデックスの配列}>
  vector<vector<ll>> mods(divide);
  ll tmp(0);
  for (int i = 0; i < N; i++) {
    cin >> tmp;
    mods[tmp % divide].push_back(i);
  }

  // ※解答例を見ても、x<yが満たされているのかが分からなかったが
  // ([90,10,...]の様に大→小の順のケースはない？)、
  //  念のため以下の実装はx<yが満たされる様な方針で実装した。
  //  パッと見最悪の計算量がいまいち分からないが、
  // 100 * ([1, 10^9]の範囲の数値を100で割った時の余りが等しい物の個数の最大値)
  // * ([1,10^9]の範囲の数値で、100-{100で割った時の余りが等しい物の個数の最大値})
  // だと思われる
  // →対称性があると思うので、分散してN^2になることはないのだと考えられる

  dump(mods);
  ll res(0);
  for (int i = 0; i < divide; i++) {
    // ※0の時もケアする
    auto remain_100 = i > 0 ? 100 - i : i;
    for (const auto& my : mods[i]) {
      for (const auto& elem : mods[remain_100]) {
        // x<yのケースのみカウント
        if (elem > my) res++;
      }
    }
  }
  cout << res << endl;
}
