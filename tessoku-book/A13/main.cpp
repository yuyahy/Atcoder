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
  // Note: 答えが最大50億になるテストケースがあるため、long longで処理
  // set precision (10 digit)
  cout << setprecision(10);
  ll N(0), K(0);
  cin >> N >> K;
  vector<ll> a_numbers(N, 0);
  for (ll i = 0; i < N; i++) {
    cin >> a_numbers[i];
  }
  ll cnt(0);
  bool bMyBinarySearchAnswer(false);
  if (bMyBinarySearchAnswer) {
    for (auto it = a_numbers.begin(); it != a_numbers.end(); ++it) {
      auto now = *it;
      ll search_value = K + now;
      // [処理するインデックス+1,
      // ギリギリ差がK以下に収まるインデックス]を二分探索で求め、個数を算出する
      auto position = upper_bound(it + 1, a_numbers.end(), search_value);
      if (it == a_numbers.end() - 1) continue;
      cnt += distance(it, position) - 1;
    }
  } else {
    // 解答にあったしゃくとり法
    int right = 1;
    for (int left = 0; left < N; ++left) {
      // int right = left;
      while (right < N && (a_numbers[right] - a_numbers[left] <= K)) {
        /* 実際に right を 1 進める */
        // ex: sum += a[right];
        ++right;
      }
      /* break した状態で right は条件を満たす最大なので、何かする */
      // ex: res += (right - left);
      cnt += (right - 1 - left);
      /* left をインクリメントする準備 */
      // ex: if (right == left) ++right;
      // ex: else sum -= a[left];
      if (right == left) {
        ++right;
      }
    }
  }
  cout << cnt << endl;
}
