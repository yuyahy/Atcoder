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

  int N(0);
  cin >> N;
  vector<int> W(N, 0), X(N, 0);
  for (int i = 0; i < N; i++) {
    cin >> W[i] >> X[i];
  }
  ll max = 0;
  bool bMyAnswer(false);
  if (bMyAnswer) {
    for (int i = 0; i < 24; i++) {
      ll attendence = 0;
      for (int j = 0; j < N; j++) {
        int local_time = 0;
        // Note: 以下は自分の提出時の実装
        // →解答例にある様に、24の余りを利用すると場合分けせずに済む
        // if (X[j] + i <= 23) {
        //   local_time = X[j] + i;
        // } else {
        //   local_time = X[j] + i - 24;
        // }
        local_time = (X[j] + i) % 24;
        if (local_time >= 9 && local_time + 1 <= 18) {
          attendence += W[j];
        }
      }
      max = std::max(max, attendence);
    }
  } else {
    // いもす法
    // Note: こちら試してみたが、うまくいかなかったので一旦放置する
    // →おそらく時差で日をまたぐパターンの考慮が上手くできていない？
    vector<ll> attendence(24, 0);
    for (int i = 0; i < N; i++) {
      auto begin_time = (9 - X[i]) >= 0 ? (9 - X[i]) : 0;
      auto end_time = (18 - X[i]) >= 0 ? (18 - X[i]) : 23;
      if (begin_time > end_time) std::swap(begin_time, end_time);
      attendence[begin_time] += W[i];
      attendence[end_time] -= W[i];
    }
    dump(attendence);
    // 累積和
    auto accum_attendence = attendence;
    for (int i = 0; i < N; i++) {
      if (i != 0) {
        accum_attendence[i] += accum_attendence[i - 1];
      }
      max = std::max(max, accum_attendence[i]);
    }
    dump(accum_attendence);
  }

  cout << max << endl;
}
