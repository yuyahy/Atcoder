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

  int N(0), X(0), Y(0);
  cin >> N >> X >> Y;
  vector<int> A(N, 0);
  int nMax(-1);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
    nMax = std::max(nMax, A[i]);
  }

  dump(A);
  dump(nMax);
  // まずGrundy数を求めておく
  // 石の数がiの時のGrundy数
  vector<int> grundy(nMax + 1, 0);
  for (int i = 0; i <= nMax; i++) {
    // YよりXの方が小さい事は保証されている
    if (i < X) {
      grundy[i] = 0;
    } else {
      int grundy1(100000000), grundy2(100000000);
      if (i - X >= 0) grundy1 = grundy[i - X];
      if (i - Y >= 0) grundy2 = grundy[i - Y];
      if (grundy1 == grundy2) {
        // 0未満の数値にはできないので、0かで場合分け
        if (grundy1 > 0) {
          grundy[i] = grundy1 - 1;
        } else {
          grundy[i] = grundy1 + 1;
        }
      } else {
        auto min = std::min(grundy1, grundy2);
        auto max = std::max(grundy1, grundy2);
        if (min == 0) {
          // 最小値が0かつ、最小値と最大値が連続していなければ、1
          // 最小値が0かつ、最小値と最大値が連続していれば、2
          if (max - min > 1) {
            grundy[i] = 1;
          } else {
            grundy[i] = 2;
          }
        } else {
          // 最小値が1以上の場合は、非負の最小の整数は0に決まる
          grundy[i] = 0;
        }
      }
    }
  }

  // 各山のGrundy数を求め、XORを取る
  int gru(grundy[A[0]]);
  for (int i = 1; i < N; i++) {
    gru ^= grundy[A[i]];
  }

  auto result = gru ? "First" : "Second";
  cout << result << endl;
}
