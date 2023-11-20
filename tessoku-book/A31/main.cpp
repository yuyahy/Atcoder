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
  ll N(0);
  cin >> N;

  constexpr int div1(3);
  constexpr int div2(5);

  // [1, N]の内、3で割り切れる数字の個数
  ll div1_cnt = N / div1;
  // [1, N]の内、5で割り切れる数字の個数
  ll div2_cnt = N / div2;
  // [1, N]の内、3と5の最小公倍数(=15)で割り切れる数字の個数
  ll div3_cnt = N / std::lcm(div1, div2);

  // Note: ダブりを考慮し、最小公倍数で割り切れる個数を引く
  cout << (div1_cnt + div2_cnt - div3_cnt) << endl;
}
