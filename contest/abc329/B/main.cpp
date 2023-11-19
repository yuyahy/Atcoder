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
  vector<int> A(N, 0);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }
  std::sort(A.begin(), A.end(), std::greater<int>{});
  dump(A);
  auto max = A[0];
  for (int i = 1; i < N; i++) {
    if (A[i] != max) {
      cout << A[i] << endl;
      break;
    }
  }
}
