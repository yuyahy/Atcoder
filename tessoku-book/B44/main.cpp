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

  // keyに対する格納要素の配列のmap
  map<int, vector<int>> matrix;
  // 行番号に対する上記mapの対応keyのmap
  map<int, int> key_map;

  int N(0), Q(0), tmp(0);
  cin >> N;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> tmp;
      matrix[i + 1].push_back(tmp);
    }
  }
  for (int i = 1; i <= N; i++) key_map[i] = i;
  dump(matrix);
  dump(key_map);
  cin >> Q;
  int query(0), x(0), y(0);
  for (int i = 0; i < Q; i++) {
    cin >> query >> x >> y;
    if (query == 1) {
      std::swap(key_map[x], key_map[y]);
    } else {
      cout << matrix[key_map[x]].at(y - 1) << endl;
    }
  }
}
