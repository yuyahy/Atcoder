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

  // エラトステネスのふるいで素数を列挙する(計算量はO(loglogN)で、ほぼO(N))
  // 1. 整数2、3、...、Nを書く
  // 2. 2に丸をつけ、それ以外の2の倍数を消す
  // 3. 3に丸をつけ、それ以外の3の倍数を消す
  // 4. 以下同様に、残っている最小の数に丸をつけ、その倍数を消す操作を繰り返し、
  //    最後まで消されなかった整数が素数である
  vector<bool> is_prime(N + 1, true);
  is_prime[0] = false;
  is_prime[1] = false;
  // 現在丸をつけている数字と、一操作前に丸をつけていた数字
  ll start_idx(2), pre_idx(0);

  // 丸をつける数字が更新されなくなったら列挙完了
  while (start_idx != pre_idx) {
    // ある整数の倍数を消す操作
    for (ll i = start_idx + 1; i <= N; i++) {
      if (is_prime[i] && (i % start_idx == 0)) is_prime[i] = false;
    }
    // 消して残った結果から次に丸をつける数字を探す
    // ※全ての合成数の約数は[2、√X]の範囲なので、√Xまで調べれば十分
    pre_idx = start_idx;
    auto sqrt_num = static_cast<int>(sqrt(N));
    for (ll i = start_idx + 1; i <= sqrt_num; i++) {
      if (is_prime[i]) {
        start_idx = i;
        break;
      }
    }
  }
  for (ll i = 0; i <= N; i++) {
    if (is_prime[i]) cout << i << endl;
  }
}
