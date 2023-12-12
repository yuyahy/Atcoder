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

  ll H(0), W(0);
  cin >> H >> W;
  vector<vector<ll>> A(H, vector<ll>(W, 0));
  vector<vector<ll>> B(H, vector<ll>(W, 0));

  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      cin >> A[i][j];
    }
  }

  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      cin >> B[i][j];
    }
  }

  dump(A);
  dump(B);

  // ポイント1
  // 現在の並びを以下の方法で表現する
  // ・初期状態でi列目にあった列が今何列目に存在するか
  // ・初期状態でi行目にあった行が今何行目に存在するか
  // これは本問題の制約より、最大でも5!×5!=14400通りしか存在しないため使える

  // ポイント2
  // 一般に、数列[1, 2, ...N]を隣接する2項を入れ替えて、ある順列A=[A1, A2,
  // ...An]に 並び替えるための最小操作回数は順列Aの転倒数に等しい
  // ※転倒数→配列の左から順番に、「自分より左にいるのに自分より大きい数」の個数を足していった時の総和

  // 1.縦横の各順列のパターンについて以下を行う
  // 2-1.グリッドBに等しくなければcontinue
  // 2-2.グリッドBに等しければ、初期状態AからBに変形するための最小操作回数を求める
  // 3.最小回数が求まっていれば出力、一個もグリッドBに等しくなければ-1を出力

  vector<ll> P(H, 0);
  vector<ll> Q(W, 0);
  for (int i = 0; i < H; i++) {
    P[i] = i;
  }
  for (int i = 0; i < W; i++) {
    Q[i] = i;
  }

  dump(P);
  dump(Q);

  int min(1e8);
  do {
    do {
      bool bSameGrid(true);
      // 並び替えた順列がグリッドBと完全一致しているかチェック
      for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
          if (A[P[i]][Q[j]] != B[i][j]) {
            bSameGrid = false;
            break;
          }
        }
      }
      if (!bSameGrid) continue;
      // 変形したグリッドAとグリッドBが等しい場合は、A→Bに変形するための最小操作回数を求める
      // これは縦と横の順列の転倒数の和に等しい
      int inv_num_P(0), inv_num_Q(0);
      // 転倒数を計算するためのラムダ式
      // ※転倒数→配列の左から順番に、「自分より左にいるのに自分より大きい数」の個数を足していった時の総和
      auto calc_inv_num = [](const int size, const auto& array) {
        auto result(0);
        for (int i = 0; i < size - 1; i++) {
          for (int j = i + 1; j < size; j++) {
            if (array[i] > array[j]) result++;
          }
        }
        return result;
      };
      inv_num_P = calc_inv_num(H, P);
      inv_num_Q = calc_inv_num(W, Q);
      min = std::min(min, inv_num_P + inv_num_Q);
      // Note:next_permutationするためには、初期状態を昇順でソートしておく必要あり
    } while (std::next_permutation(Q.begin(), Q.end()));
  } while (std::next_permutation(P.begin(), P.end()));

  auto result = min == (int)1e8 ? -1 : min;
  cout << result << endl;
}
