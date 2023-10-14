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

  int N(0), Q(0), X(0);
  cin >> N;
  vector<int> numbers(N, 0);
  int tmp = 0;
  for (int i = 0; i < N; i++) {
    cin >> tmp;
    numbers[i] = tmp;
  }

  // 二分探索のためにソート(昇順)
  sort(numbers.begin(), numbers.end());

  cin >> Q;
  for (int i = 0; i < Q; i++) {
    cin >> X;
    auto position =
        lower_bound(numbers.begin(), numbers.end(), X);  // X を二分探索
    auto idx_lower = distance(numbers.begin(), position);
    cout << idx_lower << endl;
  }
}
