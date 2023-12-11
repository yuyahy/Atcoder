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
void comb(vector<vector<ll> >& v) {
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

  int K(0), G(0), M(0), G_water(0), M_water(0);
  cin >> K >> G >> M;
  for (int i = 0; i < K; i++) {
    if (G_water == G) {
      G_water = 0;
    } else if (M_water == 0) {
      M_water = M;
    } else {
      if (G - G_water <= M_water) {
        M_water -= G - G_water;
        G_water = G;
      } else {
        // 足りない場合
        G_water += M_water;
        M_water = 0;
      }
    }
  }
  cout << G_water << " " << M_water << endl;
}
