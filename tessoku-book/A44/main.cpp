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

  ll N(0), Q(0);
  cin >> N >> Q;
  map<ll, ll> A;
  for (int i = 1; i < N + 1; i++) {
    A[i] = i;
  }
  dump(A);

  // Note: 本問題のポイントは、実際にソート動作を行わずに
  // 　　　 状態を管理するためにはどうしたら良いかという所。
  //       →実際にソートするとその度にO(N)かかってしまうため
  //       ソート状態のフラグを別途用意し、それを必要に応じて反転、
  //       キーを求める時に考慮してやればOK
  bool bReverse_Index(false);
  for (int i = 0; i < Q; i++) {
    ll query(0), x(0), y(0);
    cin >> query;
    dump(query);
    dump(x);
    dump(y);

    if (query == 1) {
      cin >> x >> y;
      auto key = bReverse_Index ? N - x + 1 : x;
      A[key] = y;
    } else if (query == 2) {
      bReverse_Index = !bReverse_Index;
    } else {
      cin >> x;
      auto key = bReverse_Index ? N - x + 1 : x;
      cout << A[key] << endl;
    }
  }
}
