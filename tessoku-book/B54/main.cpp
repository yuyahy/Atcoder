// デバッグ用関数の設定
#ifdef DEFINED_ONLY_IN_LOCAL
#include </workspaces/atcoder/cpp-dump/dump.hpp>
#define dump(...) CPP_DUMP(__VA_ARGS__)
#else
#define dump(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT(...)
#endif
#define REP(i, n) for (int i = 0; (i) < (int)(n); ++(i))
#define REP3(i, m, n) for (int i = (m); (i) < (int)(n); ++(i))
#define REP_R(i, n) for (int i = (int)(n)-1; (i) >= 0; --(i))
#define REP3R(i, m, n) for (int i = (int)(n)-1; (i) >= (int)(m); --(i))

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

int main() {
  // set precision (10 digit)
  cout << setprecision(10);

  int N(0);
  cin >> N;

  // <Ai, Aiと等しい値が出現するインデックスの配列>
  map<ll, vector<ll>> number_encounts;
  ll tmp(0);
  REP(i, N) {
    cin >> tmp;
    number_encounts[tmp].push_back(i);
  }
  ll sum(0);
  dump(number_encounts);
  // Note: 今回の設問では、どの数字が何個出現したかだけ分かればよいので、
  //        <Ai, Aiと等しい要素の出現回数> Mapとし、
  //        1. sum += Map[A[i]]
  //        2. Map[A[i]] += 1
  //        を繰り返しても解ける。こちらの方がシンプルで良さそう
  for (const auto& [Ai, array] : number_encounts) {
    ll count = array.size();
    // dump(count);
    // vector<vector<ll>> v(count + 1, vector<ll>(count + 1, 0));
    // comb(v);
    // sum += v[count][2];
    // Note: 折角なので、ユーティル関数を使ってみたが、REとWAが発生
    //        使い方が悪いのかもしれないが、long
    //        long&要素数が10万程度だと厳しい？
    sum += count * (count - 1) / 2;
  }
  cout << sum << endl;
}
