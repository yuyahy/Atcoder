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
  ll Q(0);
  cin >> Q;

  set<ll> numbers;
  ll query(0), x(0);
  REP(i, Q) {
    cin >> query >> x;
    if (query == 1) {
      // カードを集合に追加
      numbers.insert(x);
    } else if (query == 2) {
      // カードを集合から除去
      numbers.erase(x);
    } else {
      // 集合の中からx以上の最小の物を答える、なければ-1
      auto itr = numbers.lower_bound(x);
      // Note: 本設問では不要だが、itrのインクリメントとデクリメントで、
      //       あるイテレータより1個大きい/小さい値にアクセスできる
      //       問題によってはこれが約に立つこともある(setは内部でソートされている)
      if (itr == numbers.end()) {
        cout << -1 << endl;
      } else {
        cout << *itr << endl;
      }
    }
  }
}
