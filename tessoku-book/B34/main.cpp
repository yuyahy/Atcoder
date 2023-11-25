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

  vector<ll> A(N, 0);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }
  dump(A);
  ll grundy(0);

  // 石がi個のGrundy数は以下の様に決まる
  // →石がi-2個、i-3個の時のGrundy数を除外した、最小の非負整数
  // よってGrundy数には以下の様な規則性がある
  // ・i % 5で割った余りが、0 or 1 or 5→0
  // ・i % 5で割った余りが、2 or 3     →1
  // ・i % 5で割った余りが、4          →2
  for (int i = 0; i < N; i++) {
    auto mod = A[i] % 5;
    dump(mod);
    auto gru(-1);
    switch (mod) {
      case 0:
      case 1:
        gru = 0;
        break;
      case 2:
      case 3:
        gru = 1;
        break;
      case 4:
        gru = 2;
        break;
      default:
        assert(0);
        break;
    }
    if (i == 0) {
      grundy = gru;
    } else {
      grundy ^= gru;
    }
  }
  auto result = grundy ? "First" : "Second";
  cout << result << endl;
}
