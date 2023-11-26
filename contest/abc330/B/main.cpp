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

  ll N(0), L(0), R(0);
  cin >> N >> L >> R;
  vector<ll> A(N, 0);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }
  dump(A);
  vector<ll> result(N, 0);
  for (int i = 0; i < N; i++) {
    ll res(0);
    // Yが範囲内のケース
    if (A[i] >= L && A[i] <= R) {
      res = A[i];
    } else {
      // Yが範囲外のケース
      if (L - A[i] >= 0) {
        res = abs(L - A[i]) + A[i];
      } else {
        res = -abs(R - A[i]) + A[i];
      }
    }
    result[i] = res;
  }
  dump(result);
  for (int i = 0; i < N; i++) {
    if (i == N - 1) {
      cout << result[i] << endl;
    } else {
      cout << result[i] << " ";
    }
  }
}
