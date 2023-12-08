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

  ll N(0);
  cin >> N;
  vector<pair<ll, ll>> cards(N, {0, 0});
  for (int i = 0; i < N; i++) {
    auto tmp0(0), tmp1(0);
    cin >> tmp0 >> tmp1;
    cards[i] = {tmp0, tmp1};
  }

  // Note: 本設問は、何に対して全探索するかを考える事がポイント(解説AC)。
  // →(表の総和の絶対値)+(裏の総和の絶対値)を最大化する方法は以下の4パターンに整理できる
  // ・(表の総和) + (裏の総和)を最大化する→A+B>0を満たすカードのみ取る
  // ・(表の総和) - (裏の総和)を最大化する→A-B>0を満たすカードのみ取る
  // ・-(表の総和) + (裏の総和)を最大化する→-A+B>0を満たすカードのみ取る
  // ・-(表の総和) - (裏の総和)を最大化する→-A-B>0を満たすカードのみ取る
  // ※絶対値なので、表と裏それぞれで+-の2パターンずつ存在し、合計4パターン
  //
  // 与えられたパラメータ(e.g. カード)に着目するのではなく、
  // ゴールである「(表の総和の絶対値)+(裏の総和の絶対値)を最大化する方法」は
  // どんなパターンに分類できるか？という発想が必要になる

  dump(cards);
  ll max(0);
  // 上記の4パターンを全探索し、最大値を求める
  for (int i = 0; i < 4; i++) {
    ll tmp(0);
    auto coef_A = (i == 0 || i == 1) ? 1 : -1;
    auto coef_B = (i == 1 || i == 3) ? 1 : -1;
    for (const auto& [A, B] : cards) {
      if (coef_A * A + (coef_B * B) > 0) {
        tmp += coef_A * A + (coef_B * B);
      }
    }
    max = std::max(max, tmp);
  }
  cout << max << endl;
}
