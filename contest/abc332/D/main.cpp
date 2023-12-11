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

  // Aの行iを構成する数字と、同じ数字を持つ行がBにないと絶対に作れない
  // 同様にAの列iを構成する数字と、同じ数字を持つ列がBにないと絶対に作れない

  // Bの対応インデックスの4近傍を調べればOKかも→隣り合った行と列しか入れ替えられないので
  //
  bool bCanConvert(true);
  int cost(0);

  // TODO: 行と列ごとに何行 or 列移動するかをチェックしていく
  for (int i = 0; i < H; i++) {
    // 左右 or 上下の場合は1手で同じ形にできる
    // 斜めの場合は2手で同じインデックスにできる

    // 行ごとに何行ずらす必要があるかをチェックする
    std::set<ll> col_A(A[i].begin(), A[i].end());
    auto sameCol_B(B[i].begin(), B[i].end());
    auto nextCol_B(B[i + 1].begin(), B[i + 1].end());
    if (col_A == sameCol_B) {
      int aa;
    } else if (col_A == nextCol_B) {
      cost++;
      swap(A[i], A[i + 1]);
    } else {
      bCanConvert = false;
      break;
    }
  }
}

for (int i = 0; i < W; i++) {
  // 左右 or 上下の場合は1手で同じ形にできる
  // 斜めの場合は2手で同じインデックスにできる
  std::set<ll> row_A;
  for (int j = 0; j < H; j++) {
    row_A.insert(A[j][i]);
  }
  // 列ごとに何列ずらす必要があるかをチェックする
  auto sameCol_B(B[i].begin(), B[i].end());
  auto nextCol_B(B[i + 1].begin(), B[i + 1].end());
  if (col_A == sameCol_B) {
    int aa;
  } else if (col_A == nextCol_B) {
    cost++;
  } else {
    bCanConvert = false;
    break;
  }
}

//   bool bColSame(true);
//   for (int i = 0; i < H; i++) {
//     bool bFind(false);
//     std::set<ll> col_A(A[i].begin(), A[i].end());
//     // for (int j = 0; j < W; j++) {
//     // }
//     dump(col_A);
//     for (int j = 0; j < H; j++) {
//       std::set<ll> col_B(B[i].begin(), B[i].end());
//       if (col_A == col_B) {
//         bFind = true;
//         break;
//       }
//     }
//     bColSame &= bFind;
//   }
//   bool bRowSame(true);
//   for (int i = 0; i < W; i++) {
//     bool bFind(false);
//     std::set<ll> row_A;
//     for (int j = 0; j < H; j++) {
//       row_A.insert(A[j][i]);
//     }
//     dump(row_A);
//     for (int k = 0; k < W; k++) {
//       std::set<ll> row_B;
//       for (int l = 0; l < H; l++) {
//         row_B.insert(A[l][k]);
//       }
//       if (row_A == row_B) {
//         bFind = true;
//         break;
//       }
//     }
//     bRowSame &= bFind;
//   }
//   dump(bColSame);
//   dump(bRowSame);
}
