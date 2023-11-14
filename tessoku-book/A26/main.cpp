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

bool IsPrimeNumber(int num) {
  // エラトステネスのふるいでも求められるが、そちらはB26で実装する
  // Note: 2は偶数だが、素数でもあるので注意
  if (num == 2) return true;
  // 偶数かチェック
  if (num % 2 == 0) return false;
  // 2...N-1まで調べる必要はなく、√Nまで調べれば充分
  bool bPrime(true);
  int sqrt_num = static_cast<int>(sqrt(num));
  for (int i = 3; i <= sqrt_num; i++) {
    if (num % i == 0) {
      bPrime = false;
      break;
    }
  }
  return bPrime;
}

int main() {
  // set precision (10 digit)
  cout << setprecision(10);

  int Q(0), X(0);
  cin >> Q;
  for (int i = 0; i < Q; i++) {
    cin >> X;
    auto result = IsPrimeNumber(X) ? "Yes" : "No";
    cout << result << endl;
  }
}
