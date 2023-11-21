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
  constexpr int div3(7);

  // [1, N]の内、3で割り切れる数字の個数
  ll div1_cnt = N / div1;
  // [1, N]の内、5で割り切れる数字の個数
  ll div2_cnt = N / div2;
  // [1, N]の内、7で割り切れる数字の個数
  ll div3_cnt = N / div3;
  // [1, N]の内、3、5で割り切れる数字の個数
  ll div4_cnt = N / std::lcm(div1, div2);
  // [1, N]の内、5、7で割り切れる数字の個数
  ll div5_cnt = N / std::lcm(div2, div3);
  // [1, N]の内、7、3で割り切れる数字の個数
  ll div6_cnt = N / std::lcm(div3, div1);
  // [1, N]の内、3と5と7の最小公倍数で割り切れる数字の個数
  ll div7_cnt = N / std::lcm(std::lcm(div1, div2), div3);

  // Note: 3集合の包除原理
  cout << (div1_cnt + div2_cnt + div3_cnt - div4_cnt - div5_cnt - div6_cnt +
           div7_cnt)
       << endl;
}
