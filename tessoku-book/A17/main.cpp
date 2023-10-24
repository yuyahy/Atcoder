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
  vector<int> A(N + 1, 0), B(N + 1, 0), DP(N + 1, 0);
  for (int i = 2; i <= N; i++) {
    cin >> A[i];
  }
  for (int i = 3; i <= N; i++) {
    cin >> B[i];
  }
  // 動的計画法
  DP[1] = 0;
  DP[2] = A[2];
  vector<vector<int>> Root;
  Root.push_back({0});
  Root.push_back({1});
  Root.push_back({1, 2});
  // Note: この問題のポイントは、動的計画法を用いて
  // 最短時間を求めるループと、それを逆順に辿って最短経路を復元するところ

  // 最初の最短経路を求めるループで、以下の配列によって、
  // 自身に至る最短ルートを記録していく方針だとTLEが解消できなかった
  // vector<int> another_Root(N, 0);
  // // N番目の部屋に最速でたどり着く場合の一個前の部屋を記録する
  // another_Root[0] = 0;
  // another_Root[1] = 1;

  for (int i = 3; i <= N; i++) {
    // 部屋1に向かう方法は1通りしかない
    // if (i == 1) {
    //   DP[i] = A[i - 1];
    //   continue;
    // }
    // 部屋2...Nに向かうには、
    // 1つ前の部屋から行く方法と、2つ前の部屋から行く方法の2通りあるので、
    // 移動時間が少ない方を選択する
    // auto taking_time = DP[i - 1] + A[i - 1] < DP[i - 2] + B[i - 2]
    //                        ? DP[i - 1] + A[i - 1]
    //                        : DP[i - 2] + B[i - 2];
    // Note: 自分は3項演算子を使っていたが、std::minのほうが簡潔にかける
    // auto taking_time = std::min(DP[i - 1] + A[i - 1], DP[i - 2] + B[i -
    // 2]);
    auto taking_time(0);
    if (DP[i - 1] + A[i] <= DP[i - 2] + B[i]) {
      // 1個前の部屋から来るのが速いパターン
      taking_time = DP[i - 1] + A[i];
    } else {
      // 2個前の部屋から来るのが速いパターン
      taking_time = DP[i - 2] + B[i];
    }
    DP[i] = taking_time;
  }

  vector<int> result;
  // 逆順に辿って最後の部屋までの最短ルートを復元
  auto idx = N;
  while (true) {
    result.push_back(idx);
    if (idx == 1) break;
    if (DP[idx - 1] + A[idx] == DP[idx]) {
      idx = idx - 1;
    } else {
      idx = idx - 2;
    }
  }
  cout << int(result.size()) << endl;
  for (int i = int(result.size()) - 1; i >= 0; i--) {
    if (i == 0) {
      cout << result[i] << endl;
    } else {
      cout << result[i] << " ";
    }
  }
}
