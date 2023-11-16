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
  ll A(0), B(0);
  cin >> A >> B;

  // ユークリッドの互除法で最大公約数を求める(計算量はO(log(A+B)))
  // 1. 大きい方の数字を、(大きい方の数字を小さい方の数字で割った余り)で更新する
  // 2. 片方の数字が0になるまで、1.を繰り返す
  // 3. 片方の数字が0になった時のもう一方の数字が答え
  ll gcd = std::max(A, B);
  ll min = std::min(A, B);
  while (gcd > 0 && min > 0) {
    gcd = gcd % min;
    // 1.の結果大小関係が変わった場合は、swapする必要がある
    if (gcd < min) std::swap(gcd, min);
    dump(gcd);
    dump(min);
  }

  // 整数A、Bと最大公約数、最小公約数には以下の関係がある
  // A * B = 最大公約数 * 最小公約数
  auto LLM = (A * B) / gcd;
  cout << ll(LLM) << endl;
}
