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

// nCk、組み合わせを求める関数
void comb(vector<vector<ll> >& v) {
  for (ll i = 0; i < v.size(); i++) {
    v[i][0] = 1;
    v[i][i] = 1;
  }
  for (ll k = 1; k < v.size(); k++) {
    for (ll j = 1; j < k; j++) {
      v[k][j] = (v[k - 1][j - 1] + v[k - 1][j]);
    }
  }
}

int main() {
  // set precision (10 digit)
  cout << setprecision(10);

  ll N(0), tmp(0);
  cin >> N;
  // <棒の長さ、その長さの棒の数>のmap
  map<ll, ll> stick_map;

  for (ll i = 0; i < N; i++) {
    cin >> tmp;
    stick_map[tmp] += 1;
  }
  dump(stick_map);
  ll tri_cnt(0);
  for (const auto& [length, cnt] : stick_map) {
    if (cnt < 3) continue;
    ll n = cnt;
    ll k = 3;
    vector<vector<ll> > v(n + 1, vector<ll>(n + 1, 0));
    // nCkを求める
    // 今回はn=3決め打ちだが、一応今後も考えて組み合わせを求める関数を拾ってきて使っている
    comb(v);
    dump(v);
    tri_cnt += v[n][k];
  }
  cout << tri_cnt << endl;
}
