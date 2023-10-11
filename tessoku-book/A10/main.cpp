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

// 計算量→N + N + N + Dで最大400000回程度
int main() {
  // set precision (10 digit)
  cout << setprecision(10);
  int N(0), A(0);
  cin >> N;
  vector<int> people_room(N, 0);
  for (int i = 0; i < N; i++) {
    cin >> A;
    people_room[i] = A;
  }
  // この設問の最大のポイントは、
  // max(除外する区間以前の最大人数、除外する区間以降の最大人数)
  // を取ることで、ある範囲の区間を除いた上での、最大値を求められること
  // よって以下2種類の累積maxの配列を求めておけば、質問ごとにO(1)で回答できる

  // 先頭からの累積maxを求める
  int max = -1;
  vector<int> accum_max(N, 0), reverse_accum_max(N, 0);
  for (int i = 0; i < N; i++) {
    max = std::max(max, people_room[i]);
    accum_max[i] = max;
  }
  // 末尾からの累積maxを求める
  max = -1;
  for (int i = N - 1; i >= 0; i--) {
    max = std::max(max, people_room[i]);
    reverse_accum_max[i] = max;
  }

  int D(0), L(0), R(0);
  cin >> D;
  for (int i = 0; i < D; i++) {
    cin >> L >> R;
    // 区間[L,R]を除いた時にできる左右の有効な区間のそれぞれの最大値の中で大きい方を出力する
    cout << std::max(accum_max[L - 2], reverse_accum_max[R]) << endl;
  }
}
