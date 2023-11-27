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
  ll N(0), M(0), B(0);
  cin >> N >> M >> B;
  vector<ll> A(N, 0), C(M, 0);
  for (ll i = 0; i < N; i++) {
    cin >> A[i];
  }
  for (ll i = 0; i < M; i++) {
    cin >> C[i];
  }

  ll sum_Bus = std::reduce(std::begin(C), std::end(C));
  dump(sum_Bus);
  ll sum_Station = std::reduce(std::begin(A), std::end(A));

  // Note: long longで計算しないとテストケース以外エラーになる
  ll nSumTime(0);
  nSumTime += (sum_Station * M) + (B * N * M) + (sum_Bus * N);
  cout << nSumTime << endl;
}
