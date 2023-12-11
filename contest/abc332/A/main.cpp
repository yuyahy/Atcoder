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

  int N(0), S(0), K(0);
  cin >> N >> S >> K;
  vector<pair<int, int>> items(N, {0, 0});
  auto sum(0);
  for (int i = 0; i < N; i++) {
    auto tmp1(0), tmp2(0);
    cin >> tmp1 >> tmp2;
    sum += tmp1 * tmp2;
  }
  if (sum < S) sum += K;
  cout << sum << endl;
}
