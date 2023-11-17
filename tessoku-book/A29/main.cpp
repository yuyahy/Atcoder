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

  ll a(0), b(0);
  cin >> a >> b;
  // Note: modintのpowを使うと特に何もしなくても解ける
  // N回回すと間に合わないので、計算量を落とす工夫が必要
  // TODO: 見直し
  ll ans(1), a_tmp(a);
  while (b) {
    if (b % 2) {
      ans *= a % 1000000007;
      ans %= 1000000007;
    }
    a *= (a % 1000000007);
    a %= 1000000007;
    b = b >> 1;
  }
  dump(a);
  dump(b);
  dump(ans);

  cout << ans << endl;

  //   for (int i = 1; i < b; i++) {
  //     a_tmp *= (multi % 1000000007);
  //     a_tmp %= 1000000007;
  //   }
}
