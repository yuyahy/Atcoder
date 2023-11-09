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
  int N(0);
  cin >> N;
  vector<int> A(N, 0), B(N, 0), DP(N, 10000000);
  for (int i = 1; i < N; i++) {
    cin >> A[i];
  }
  for (int i = 2; i < N; i++) {
    cin >> B[i];
  }
  dump(A);
  dump(B);
  bool bAnother_answer(true);
  DP[0] = 0;
  if (bAnother_answer) {
    // 動的計画法(配る式)
    for (int i = 0; i <= N - 3; i++) {
      DP[i + 1] = std::min(DP[i + 1], DP[i] + A[i + 1]);
      DP[i + 2] = std::min(DP[i + 2], DP[i] + B[i + 2]);
    }
    // もっと綺麗な実装があるかもしれないが、ケースBの方が移動量が多く、
    // 入力数が小さいため、最後の1ケースのケースBでの移動はループの外でベット行う
    DP[N - 1] = std::min(DP[N - 1], DP[N - 2] + A[N - 1]);
    dump(DP);
  } else {
    // 動的計画法(貰う式)
    for (int i = 1; i < N; i++) {
      // 部屋1に向かう方法は1通りしかない
      if (i == 1) {
        DP[i] = A[i - 1];
        continue;
      }
      // 部屋2...Nに向かうには、
      // 1つ前の部屋から行く方法と、2つ前の部屋から行く方法の2通りあるので、
      // 移動時間が少ない方を選択する
      // auto taking_time = DP[i - 1] + A[i - 1] < DP[i - 2] + B[i - 2]
      //                        ? DP[i - 1] + A[i - 1]
      //                        : DP[i - 2] + B[i - 2];
      // Note: 自分は3項演算子を使っていたが、std::minのほうが簡潔にかける
      auto taking_time = std::min(DP[i - 1] + A[i - 1], DP[i - 2] + B[i - 2]);
      DP[i] = taking_time;
    }
  }
  cout << DP[N - 1] << endl;
}
