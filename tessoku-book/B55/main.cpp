// デバッグ用関数の設定
#ifdef DEFINED_ONLY_IN_LOCAL
#include </workspaces/atcoder/cpp-dump/dump.hpp>
#define dump(...) CPP_DUMP(__VA_ARGS__)
#else
#define dump(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT(...)
#endif
#define REP(i, n) for (int i = 0; (i) < (int)(n); ++(i))
#define REP3(i, m, n) for (int i = (m); (i) < (int)(n); ++(i))
#define REP_R(i, n) for (int i = (int)(n)-1; (i) >= 0; --(i))
#define REP3R(i, m, n) for (int i = (int)(n)-1; (i) >= (int)(m); --(i))
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

  ll x(0), Q(0), query(0);
  cin >> Q;
  set<ll> numbers;
  REP(i, Q) {
    cin >> query >> x;
    if (query == 1) {
      // xを集合に追加
      numbers.insert(x);
    } else if (query == 2 && numbers.size() == 0) {
      // 集合内の要素が0個の場合
      cout << -1 << endl;
    } else {
      // xと集合にある数字の差の絶対値の最小値を出力
      //   if (numbers.size() > 1) {
      //     auto itr1 = numbers.lower_bound(x);
      //     if (itr1 != numbers.end()) {
      //       // x以上の最小値が見つかった場合
      //       // x以上の最小値と、それより一個小さい要素を取得し、
      //       // xとの差の絶対値がより小さい方を出力する
      //       auto itr2 = prev(itr1, 1);
      //       cout << min(abs(x - (*itr1)), abs(x - (*(itr2)))) << endl;
      //     } else {
      //       // xが集合の最大値より大きい場合
      //       // 集合の最大値を使用
      //       auto max = *rbegin(numbers);
      //       cout << abs(x - max) << endl;
      //     }
      //   } else {
      //     // 集合内の要素が一個しかない場合
      //     auto itr = numbers.begin();
      //     cout << abs(x - (*(itr))) << endl;
      //   }

      // Note:
      // 上の様な実装だと場合分けが増えてミスしがちなので、min、maxを上手く活用して減らす
      // x以上の最小値を求める
      // x以下の最大値を求める
      ll min(0), max(0);
      auto itr1 = numbers.lower_bound(x);
      if (itr1 == numbers.end()) {
        // xが集合の最大値より大きい場合
        min = *rbegin(numbers);
        max = *rbegin(numbers);
      } else {
        min = *itr1;
        // Note: ここを以下の様にすると一部ケースでWA
        //  max = numbers.size() == 1 ? *itr1 : *(prev(itr1, 1));
        // 要素数が1個のときは、itr1をそのまま使うのでOKだと考えていたが、おそらく考慮が漏れている
        // ケースが存在すると思われるがそれが何かわからない。。。
        max = itr1 == numbers.begin() ? *itr1 : *(prev(itr1, 1));
      }
      cout << std::min(abs(x - min), abs(x - max)) << endl;
    }
  }
}
