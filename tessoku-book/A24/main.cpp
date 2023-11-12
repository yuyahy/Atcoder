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

  vector<ll> A(N + 1, -1);
  for (int i = 1; i <= N; i++) {
    cin >> A[i];
  }
  dump(A);

  // 最後の要素がAiである部分列のうち、最長の物の長さ
  vector<ll> DP(N + 1, 0);
  // 各長さxの部分列をなす物のうち、末端の要素の最小値を管理する配列
  // これを導入することでDPテーブルの更新がO(logN)で実現できる
  vector<ll> length_tail_min(N + 1, 0);
  // 現在どこまで上記の配列で記録されているのかをインデックスで保存しておく
  // →ひょっとしたらlength_tail_minは空の配列として定義し、必要に応じて
  //  push_back()などで要素を追加していく形でも問題ないかも
  ll LEN(0);

  // 初期状態
  DP[1] = 1;
  length_tail_min[1] = A[1];
  LEN = 1;

  for (int i = 2; i <= N; i++) {
    // DP[i] = length_tail_min[pos] < Aiを満たすposの最大値 + 1
    // std::lower_bound()で得られるのは、length_tail_min[pos] >= Ai
    // となる最小のposなので、(std::lower_bound() -1)が、
    // length_tail_min[pos] < Aiを満たすposの最大値となる理解
    auto itr = std::lower_bound(length_tail_min.begin(),
                                length_tail_min.begin() + LEN + 1, A[i]);
    auto pos = std::distance(length_tail_min.begin(), itr);
    DP[i] = pos;
    length_tail_min[DP[i]] = A[i];

    dump(pos);
    dump(length_tail_min);
    dump(DP);
    dump(A[i]);
    // DPの結果がそれまでに最長であれば、
    // LENを更新する
    LEN = std::max(LEN, DP[i]);
  }
  dump(DP);
  cout << LEN << endl;
}
