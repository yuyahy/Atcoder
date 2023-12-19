// TODO: マクロや共通関数は別ファイルに定義し、埋め込む様にする
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

  string S1(""), S2(""), T1(""), T2("");
  string S(""), T("");
  cin >> S;
  cin >> T;
  dump(S);
  dump(T);
  map<char, int> points;

  points['A'] = 0;
  points['B'] = 1;
  points['C'] = 2;
  points['D'] = 2;
  points['E'] = 1;

  auto near = [](char x, char y) {
    if (x > y) swap(x, y);
    return y - x == 1 or y - x == 4;
  };

  auto distance = [&](const string STR) {
    auto p1 = points[STR[0]];

    if (STR[0] == 'A') {
      points['A'] = 0;
      points['B'] = 1;
      points['C'] = 2;
      points['D'] = 2;
      points['E'] = 1;
    }
    if (STR[0] == 'B') {
      points['A'] = 1;
      points['B'] = 0;
      points['C'] = 1;
      points['D'] = 2;
      points['E'] = 2;
    }
    if (STR[0] == 'C') {
      points['A'] = 2;
      points['B'] = 1;
      points['C'] = 0;
      points['D'] = 1;
      points['E'] = 2;
    }
    if (STR[0] == 'D') {
      points['A'] = 2;
      points['B'] = 2;
      points['C'] = 1;
      points['D'] = 0;
      points['E'] = 1;
    }
    if (STR[0] == 'E') {
      points['A'] = 1;
      points['B'] = 2;
      points['C'] = 2;
      points['D'] = 1;
      points['E'] = 0;
    }
    auto p2 = points[STR[1]];
    return p2;
  };

  auto dist_S = distance(S);
  auto dist_T = distance(T);

  auto result = dist_S == dist_T ? "Yes" : "No";
  cout << result << endl;
}
