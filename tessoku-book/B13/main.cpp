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
  int N(0), K(0);
  cin >> N >> K;
  vector<int> prices(N, 0);
  for (int i = 0; i < N; i++) {
    cin >> prices[i];
  }
  int right(0), cnt(0);
  for (int left = 0; left < N; left++) {
    auto remain_K = K;
    right = left;
    // 連続する番号の品物を買ってもK円に収まる場合は、rightを増やしていく
    // Note:
    // 左辺に等号をつけると、N=rightの時に更に、rightをインクリメントしてしまう
    while (right < N && remain_K - prices[right] >= 0) {
      // Note: rightをインクリメントする前に買える残高を更新しておく
      remain_K -= prices[right];
      right++;
    }
    // 今回のleftの間にrightが移動した量を求める
    cnt += right - left;
  }
  cout << cnt << endl;
}
