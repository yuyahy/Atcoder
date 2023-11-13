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

bool asc_desc(pair<ll, ll>& left, pair<ll, ll>& right) {
  // Note: 縦の長さが等しい場合は、横の長さが「大きい」物を前の方のインデックス
  // に格納しておく必要があるので、比較関数を用意
  // →これをやらないと縦の長さが等しい物が全て入れ子にできると、誤判定するため
  if (left.first == right.first) {
    return right.second < left.second;
  } else {
    return left.first < right.first;
  }
}

int main() {
  // set precision (10 digit)
  cout << setprecision(10);
  ll N(0);
  cin >> N;

  vector<ll> X, Y;
  vector<pair<ll, ll>> Box(N, {0, 0});
  for (int i = 0; i < N; i++) {
    cin >> Box[i].first >> Box[i].second;
  }
  dump(Box);
  // 二分木探索のためにソート(上記の通り比較関数はカスタム)
  std::sort(Box.begin(), Box.end(), asc_desc);
  dump(Box);

  // Note: 本問題のポイントは、あらかじめX or Yを上記のようにソートしておけば、
  //       後はソートしていないもう一方の情報に対して最長増加部分列問題を解くことで
  //       目的の値が求められること
  // ※長さNの数列[A1、A2..、An]が入力されるとき、そのうちいくつかの値を順番を変えずに取り出したときに、
  //  これが増加列となる中で最大の長さのものを求める

  // ※以下はA24の回答をそのまま使用
  // 最後の要素がAiである部分列のうち、最長の物の長さ
  vector<ll> DP(N + 1, 0);
  // 各長さxの部分列をなす物のうち、末端の要素の最小値を管理する配列
  // これを導入することでDPテーブルの更新がO(logN)で実現できる
  vector<ll> length_tail_min(N + 1, 0);
  // 現在どこまで上記の配列で記録されているのかをインデックスで保存しておく
  // →ひょっとしたらlength_tail_minは空の配列として定義し、必要に応じて
  //  push_back()などで要素を追加していく形でも問題ないかも
  ll LEN(0);
  // インデックス合わせのためにダミー要素を追加
  Y.push_back(0);
  for (auto [x, y] : Box) {
    Y.push_back(y);
  }
  dump(Y);

  // 初期状態
  DP[1] = 1;
  length_tail_min[1] = Y[1];
  LEN = 1;

  for (int i = 2; i <= N; i++) {
    // DP[i] = length_tail_min[pos] < Aiを満たすposの最大値 + 1
    // std::lower_bound()で得られるのは、length_tail_min[pos] >= Ai
    // となる最小のposなので、(std::lower_bound() -1)が、
    // length_tail_min[pos] < Aiを満たすposの最大値となる理解
    auto itr = std::lower_bound(length_tail_min.begin(),
                                length_tail_min.begin() + LEN + 1, Y[i]);
    auto pos = std::distance(length_tail_min.begin(), itr);
    DP[i] = pos;
    length_tail_min[DP[i]] = Y[i];

    dump(pos);
    dump(length_tail_min);
    dump(DP);
    dump(Y[i]);
    // DPの結果がそれまでに最長であれば、
    // LENを更新する
    LEN = std::max(LEN, DP[i]);
  }
  dump(DP);
  cout << LEN << endl;
}
